#include "minishell.h"

t_minishell	parser(char *line)
{
	t_minishell minishell;

	minishell.tokens = lexer(line);

	return (minishell);
}