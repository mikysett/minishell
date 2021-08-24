#include "minishell.h"

t_minishell	*get_minishell(t_minishell *minishell)
{
	static t_minishell	*ms = NULL;

	if (!ms && minishell)
		ms = minishell;
	return (ms);
}

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
	else if (err == WRONG_QUOTING)
		printf("minishell: Wrong quoting\n");
	else
		printf("minishell: An error occurred\n");
}