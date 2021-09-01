#include "minishell.h"

int	executor(t_minishell *ms, t_list *curr, int cmd_exit_code)
{
	t_instruction	*instr;
	const int		curr_group = ((t_instruction *)curr->content)->cmd->group;

	// int	original_in = dup(STDIN_FILENO);
	while (curr)
	{
		instr = (t_instruction *)curr->content;
		if (instr->type == INSTR_CMD && instr->cmd->group != curr_group)
			return (executor(ms, curr, cmd_exit_code));
		else if (instr->type == INSTR_CMD)
			cmd_exit_code = exec_cmd(instr->cmd, ms->redirect);
		else if (instr->type == INSTR_OR && cmd_exit_code == EXIT_SUCCESS)
			return (cmd_exit_code);
		else if (instr->type == INSTR_AND && cmd_exit_code != EXIT_SUCCESS)
			return (cmd_exit_code);
		curr = curr->next;
	}
	// dup2(original_in, STDIN_FILENO);
	return (cmd_exit_code);
}

int	exec_cmd(t_cmd *cmd, t_list **redirect)
{
	int	cmd_exit_code;

	if (setup_redirect(redirect, cmd->id))
	{
		if (cmd->is_builtin)
			cmd_exit_code = exec_builtin(cmd);
		else
			cmd_exit_code = exec_std_cmd(cmd);
	}
	else
		cmd_exit_code = EXIT_FAILURE;
	restore_std_in(get_minishell(NULL));
	restore_std_out(get_minishell(NULL));
	return (EXIT_FAILURE);
}

int	exec_builtin(t_cmd *cmd)
{
	return (EXIT_SUCCESS);
}

int	exec_std_cmd(t_cmd *cmd)
{
	pid_t	child_pid;
	int		wstatus;
	t_minishell	*ms;

	ms = get_minishell(NULL);
	cmd->full_path = set_cmd_path(cmd->name, ms->paths);
	child_pid = fork();
	if (child_pid == -1)
	{
		perror(ms->prog_name);
		return (EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execve(cmd->full_path, cmd->args, ms->envp) == -1)
		{
			perror(cmd->name);
			return (EXIT_FAILURE); // return 127 as special error? (check man)
		}
	}
	else if (wait(&wstatus) == -1)
	{
		perror(ms->prog_name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*set_cmd_path(char *cmd_name, char **paths)
{
	int		i;
	int		cmd_path_size;
	int		cmd_name_len;
	char	*full_path;

	i = 0;
	cmd_name_len = ft_strlen(cmd_name);
	if (paths)
	{
		while (paths[i])
		{
			cmd_path_size = ft_strlen(paths[i]) + cmd_name_len + 2;
			full_path = ft_calloc(cmd_path_size, sizeof(char));
			if (!full_path)
				ft_error_exit(MEMORY_FAIL);
			ft_strlcat(full_path, paths[i], cmd_path_size);
			ft_strlcat(full_path, "/", cmd_path_size);
			ft_strlcat(full_path, cmd_name, cmd_path_size);
			if (access(full_path, F_OK | X_OK) == 0)
				return (full_path);
			free(full_path);
			full_path = 0;
			i++;
		}
	}
	return (ft_strdup(cmd_name));
}

