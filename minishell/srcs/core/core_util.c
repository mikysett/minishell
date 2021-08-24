#include "minishell.h"

void	ft_error_exit(t_err_code err)
{
	ft_print_err(err);
	// TODO free memory
	exit(EXIT_FAILURE);
}

void	ft_print_err(t_err_code err)
{
	// TODO check if err_code is still necessary or if strerror(errno) is enough
	if (err == MEMORY_FAIL)
		printf("minishell: %s\n", strerror(errno));
	if (err == WRONG_QUOTING)
		printf("minishell: Wrong quoting\n");
}