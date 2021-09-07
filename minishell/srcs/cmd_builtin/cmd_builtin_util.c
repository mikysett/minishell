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

bool	is_valid_identifier(char *str)
{
	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (false);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

void	print_identifier_error(char *prog_name, char *builtin_name,
	char *invalid_identifier)
{
	ft_putstr_fd(prog_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(builtin_name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(invalid_identifier, STDERR_FILENO);
	ft_putstr_fd("' not a valid identifier\n", STDERR_FILENO);
}
