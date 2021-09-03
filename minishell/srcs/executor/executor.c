#include "minishell.h"

int	executor(t_minishell *ms, t_list *curr, int cmd_exit_code)
{
	t_instruction	*instr;
	const int		curr_group = ((t_instruction *)curr->content)->cmd->group;
	t_std_io		*std_io;

	std_io = &ms->streams;
	while (curr)
	{
		instr = (t_instruction *)curr->content;
		if (instr->type == INSTR_CMD && instr->cmd->group != curr_group)
			return (executor(ms, curr, cmd_exit_code));
		else if (instr->type == INSTR_CMD)
			cmd_exit_code = exec_cmd(instr->cmd, std_io, ms->redirect);
		else if (instr->type == INSTR_OR && cmd_exit_code == EXIT_SUCCESS)
			return (cmd_exit_code);
		else if (instr->type == INSTR_AND && cmd_exit_code != EXIT_SUCCESS)
			return (cmd_exit_code);
		curr = curr->next;
	}
	return (cmd_exit_code);
}

int	exec_cmd(t_cmd *cmd, t_std_io *std_io, t_list **redirect)
{
	int	cmd_exit_code;

	if (setup_redirect(std_io, redirect, cmd->id))
	{
		DEBUG(fprintf(stderr, "executing a command\n");)
		if (cmd->is_builtin)
			cmd_exit_code = exec_builtin(cmd);
		else
			cmd_exit_code = exec_std_cmd(cmd);
		DEBUG(fprintf(stderr, "cmd executed (in exec_cmd)\n");)
	}
	else
		cmd_exit_code = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

int	exec_builtin(t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->name, 5))
		return (echo_builtin(cmd->args));
	else if (!ft_strncmp("cd", cmd->name, 3))
		return (cd_builtin(cmd->args));
	else if (!ft_strncmp("pwd", cmd->name, 4))
		return (pwd_builtin(cmd->args));
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
			exit(EXIT_FAILURE); // return 127 as special error? (check man)
		}
	}
	else if (wait(&wstatus) == -1)
	{
		perror(ms->prog_name);
		return (EXIT_FAILURE);
	}
	DEBUG(fprintf(stderr, "cmd executed\n");)
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

