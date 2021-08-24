#include "minishell.h"

t_minishell	*get_minishell(t_minishell *minishell)
{
	static t_minishell	*ms = NULL;

	if (!ms && minishell)
		ms = minishell;
	return (ms);
}

t_prog_state	prog_state(t_prog_state set_prog_state)
{
	static t_prog_state	prog_state = PROG_OK;

	if (set_prog_state != TAKE_STATE)
		prog_state = set_prog_state;
	return (prog_state);
}

void	ft_error_exit(t_err_code err)
{
	t_minishell	*ms;

	ms = get_minishell(NULL);
	print_err(err);
	if (ms)
		free_minishell(ms);
	exit(EXIT_FAILURE);
}

void	print_err(t_err_code err)
{
	// TODO check if err_code is still necessary or if strerror(errno) is enough
	if (err == MEMORY_FAIL)
		printf("minishell: %s\n", strerror(errno));
	else if (err == WRONG_QUOTING)
		printf("minishell: Wrong quoting\n");
	else
		printf("minishell: An error occurred\n");
}