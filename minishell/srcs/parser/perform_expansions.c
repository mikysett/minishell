#include "minishell.h"

void	perform_expansions(t_list **tokens)
{
	filename_expansion(tokens);
	quote_removal(*tokens);
}