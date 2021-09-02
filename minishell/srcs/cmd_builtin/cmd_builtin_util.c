#include "minishell.h"

int	args_count(char **argv)
{
	int	args_nb;

	args_nb = 0;
	if (!argv)
		return (0);
	while (argv[args_nb])
		args_nb++;
	return (args_nb);
}