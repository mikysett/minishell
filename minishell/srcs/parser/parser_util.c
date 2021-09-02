#include "minishell.h"

int		is_redir_op(char *str)
{
	return (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0
			|| ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0
			|| ft_strncmp(str, "|", 1) == 0);
}

int		is_logic_op(char *str)
{
	return (ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, "&&", 2) == 0);
}

int		is_paren_op(char *str)
{
	return (ft_strncmp(str, "(", 1) == 0 || ft_strncmp(str, ")", 1) == 0);
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
