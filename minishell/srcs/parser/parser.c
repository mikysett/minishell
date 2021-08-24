#include "minishell.h"

t_minishell	*parser(char *line)
{
	t_minishell *minishell;

	minishell = calloc_or_exit(1, sizeof(t_minishell));
	get_minishell(minishell);
	minishell->tokens = lexer(line);
	print_tokens(minishell->tokens);
	return (minishell);
}