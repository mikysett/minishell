#include "minishell.h"

/* all of this can be worked with enum! */

int		is_pipe_op(t_token *token)
{
	return (token->type == OPERATOR && ft_strncmp(token->str, "|", 2) == 0);
}

int		is_redir_op(t_token *token)
{
	char *str;

	if (token->type == OPERATOR)
	{
		str = token->str;
		return (token->type == OPERATOR &&
			(ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str, ">", 2) == 0
			|| ft_strncmp(str, "<<", 3) == 0 || ft_strncmp(str, ">>", 3) == 0));
	}
	return (0);
}

int		is_logic_op(t_token *token)
{
	char *str;

	str = token->str;
	return (token->type == OPERATOR &&
			(ft_strncmp(str, "||", 3) == 0 || ft_strncmp(str, "&&", 3) == 0));
}

int		is_paren_op(t_token *token)
{
	char *str;

	str = token->str;
	return (token->type == OPERATOR &&
			(ft_strncmp(str, "(", 1) == 0 || ft_strncmp(str, ")", 1) == 0));
}

int		get_redir_type(t_token *token)
{
	if (ft_strncmp(token->str, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token->str, ">", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(token->str, "<<" , 3) == 0)
		return (REDIR_HERE_DOC);
	else if (ft_strncmp(token->str, ">>" , 3) == 0)
		return (REDIR_OUT_APPEND);
	/* provoke parse error if not a redir? */
	return (-1);
}

/* gets a node object, and retrieves the amount of words
 * in that command */
int		take_length_of_command(t_list *node)
{
	int i;
	t_token *token;

	i = 0;
	if (!node)
		return (0);
	while (node)
	{
		token = (t_token *)node->content;
		if (token->type == WORD)
			i++;
		node = node->next;
	}
	return (i);
}

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

/* initiates an instruction outside of the main
 * handling functions; this ensures allocation is retrievable
 * in case of failure at the handler function */
t_cmd		*init_instruction(t_minishell *ms, t_instr_type type)
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
		(instr->cmd)->name = strdup_or_exit("");
	}
	else
		instr->cmd = NULL;
	instr->type = type;
	return (instr->cmd);
}
