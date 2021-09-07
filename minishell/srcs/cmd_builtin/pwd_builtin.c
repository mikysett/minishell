#include "minishell.h"

int	pwd_builtin(char **argv)
{
	const int	args_nb = args_count(argv);
	char		*absolute_path;

	absolute_path = NULL;
	if (args_nb != 1)
	{
<<<<<<< HEAD
		ft_putstr_fd("pwd: too many arguments\n", STDOUT_FILENO);
=======
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
>>>>>>> master
		return (EXIT_FAILURE);
	}
	getcwd(absolute_path, 0);
	if (!absolute_path)
	{
		perror(argv[0]);
		return (EXIT_FAILURE);
	}
<<<<<<< HEAD
	write(STDIN_FILENO, absolute_path, ft_strlen(absolute_path));
=======
	write(STDOUT_FILENO, absolute_path, ft_strlen(absolute_path));
>>>>>>> master
	free(absolute_path);
	return (EXIT_SUCCESS);
}