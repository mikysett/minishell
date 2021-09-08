#include "minishell.h"

static int	exec_instr(t_cmd *cmd, t_std_io *std_io, t_list **redirect);
static int	exec_cmd(t_cmd *cmd);

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
			cmd_exit_code = exec_instr(instr->cmd, std_io, ms->redirect);
		else if (instr->type == INSTR_OR && cmd_exit_code == EXIT_SUCCESS)
			return (cmd_exit_code);
		else if (instr->type == INSTR_AND && cmd_exit_code != EXIT_SUCCESS)
			return (cmd_exit_code);
		curr = curr->next;
	}
	return (cmd_exit_code);
}

static int	exec_instr(t_cmd *cmd, t_std_io *std_io, t_list **redirect)
{
	if (setup_redirect(std_io, redirect, cmd->id))
		return (exec_cmd(cmd));
	else
		return (EXIT_FAILURE);
}

static int	exec_cmd(t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->name, 5))
		return (echo_builtin(cmd->args));
	else if (!ft_strncmp("cd", cmd->name, 3))
		return (cd_builtin(cmd->args));
	else if (!ft_strncmp("pwd", cmd->name, 4))
		return (pwd_builtin(cmd->args));
	else if (!ft_strncmp("export", cmd->name, 7))
		return (export_builtin(cmd->args));
	else if (!ft_strncmp("unset", cmd->name, 6))
		return (unset_builtin(cmd->args));
	else if (!ft_strncmp("env", cmd->name, 4))
		return (env_builtin(cmd->args));
	else if (!ft_strncmp("exit", cmd->name, 5))
		return (exit_builtin(cmd->args));
	else
		return (exec_std_cmd(cmd));
}
