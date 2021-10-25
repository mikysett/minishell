#include "minishell.h"

t_token	*get_token(t_list *curr_node)
{
	if (curr_node)
		return ((t_token *)curr_node->content);
	return (NULL);
}

int	get_redir_type(t_token *token)
{
	if (ft_strncmp(token->str, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token->str, ">", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(token->str, "<<", 3) == 0)
		return (REDIR_HERE_DOC);
	else if (ft_strncmp(token->str, ">>", 3) == 0)
		return (REDIR_OUT_APPEND);
	return (-1);
}

/* gets a node object, and retrieves the amount of words
 * in that command */
int	take_length_of_command(t_list *node)
{
	int		i;
	t_token	*token;

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
