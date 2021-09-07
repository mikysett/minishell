#include "minishell.h"

int	exit_builtin(char **argv)
{
	const int			args_nb = args_count(argv);
	int					exit_code;
	const t_minishell	*ms = get_minishell(NULL);

	if (args_nb > 1)
	{
		ft_putstr_fd("env: incorrect usage\n", STDERR_FILENO);
		exit_code = BUILTIN_INCORRECT_USAGE;
	}
	else
		exit_code = ms->exit_code;
	free_minishell((t_minishell *)ms);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}