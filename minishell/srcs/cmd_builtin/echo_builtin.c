#include "minishell.h"

int	echo_builtin(char **argv)
{
	const int	args_nb = args_count(argv);
	bool		print_newline;

	print_newline = true;
	if (args_nb > 2)
		if (!ft_strncmp("-n", argv[1], 3))
		{
			argv++;
			print_newline = false;
		}
	while (*(++argv))
		write(STDIN_FILENO, *argv, ft_strlen(*argv));
	if (print_newline)
		write(STDIN_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}