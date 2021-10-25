#include "minishell.h"

int	env_builtin(char **argv)
{
	const int	args_nb = args_count(argv);

	if (args_nb > 1)
	{
		ft_putstr_fd("env: incorrect usage\n", STDERR_FILENO);
		return (EXIT_INCORRECT_USAGE);
	}
	print_env(get_minishell(NULL)->envp);
	return (EXIT_SUCCESS);
}
