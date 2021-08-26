#include "minishell.h"

int	executor(t_minishell *ms, t_list *curr, int cmd_exit_code)
{
	t_instruction	*instr;
	const int		curr_group = ((t_instruction *)curr->content)->cmd->group;

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
	return (cmd_exit_code);
}

int	exec_cmd(t_cmd *cmd, t_list **redirect)
{
	if (setup_redirect(redirect, cmd->id, cmd->group))
	{
		if (cmd->is_builtin)
			return (exec_builtin(cmd));
		else
			return (exec_std_cmd(cmd));
	}
	else
		return (EXIT_FAILURE);
}

int	exec_builtin(t_cmd *cmd)
{
	return (EXIT_SUCCESS);
}

int	exec_std_cmd(t_cmd *cmd)
{
	return (EXIT_SUCCESS);
}
