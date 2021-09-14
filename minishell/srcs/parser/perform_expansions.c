#include "minishell.h"

void	perform_expansions(t_list **tokens)
{
	filename_expansions(tokens);
	quote_removal(*tokens);
}