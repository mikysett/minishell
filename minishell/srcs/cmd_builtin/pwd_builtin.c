#include "minishell.h"

int	pwd_builtin(char **argv)
{
	char	*absolute_path;

	absolute_path = NULL;
	getcwd(absolute_path, 0);
	if (!absolute_path)
	{
		perror(argv[0]);
		return (EXIT_FAILURE);
	}
	write(STDOUT_FILENO, absolute_path, ft_strlen(absolute_path));
	free(absolute_path);
	return (EXIT_SUCCESS);
}