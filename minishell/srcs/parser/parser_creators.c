#include "minishell.h"

/* initiates a redirection outside of the main
 * handling functions; this ensures allocation is retrievable
 * in case of failure at the handler function */
t_redirect	*init_redirection(t_minishell *ms, t_redir_type type)
{
	t_redirect		*redir;
	t_list			*new_redir;

	redir = calloc_or_exit(1, sizeof(t_redirect));
	new_redir = ft_lstnew(redir);
	if (!new_redir)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(ms->redirect, new_redir);
	redir->type = type;
	return (redir);
}

void	create_redir(t_token *token, char *file_name,
		int redir_type, int cmd_id)
{
	t_redirect	*redir;

	redir = init_redirection(get_minishell(NULL), get_redir_type(token));
	redir->type = redir_type;
	if (file_name)
		redir->file_name = strdup_or_exit(file_name);
	else
		redir->file_name = NULL;
	redir->cmd_id = cmd_id;
}

t_cmd	*init_empty_cmd(int cmd_id, int cmd_group)
{
	t_cmd	*new_cmd;

	new_cmd = init_instruction(get_minishell(NULL), INSTR_CMD);
	new_cmd->id = cmd_id;
	new_cmd->group = cmd_group;
	return (new_cmd);
}

/* initiates an instruction outside of the main
 * handling functions; this ensures allocation is retrievable
 * in case of failure at the handler function */
t_cmd	*init_instruction(t_minishell *ms, t_instr_type type)
{
	t_instruction	*instr;
	t_list			*new_instr;

	instr = calloc_or_exit(1, sizeof(t_instruction));
	new_instr = ft_lstnew(instr);
	if (!new_instr)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(ms->instructions, new_instr);
	if (type == INSTR_CMD)
	{
		instr->cmd = calloc_or_exit(1, sizeof(t_cmd));
		instr->cmd->is_empty_cmd = true;
	}
	else
		instr->cmd = NULL;
	instr->type = type;
	return (instr->cmd);
}
