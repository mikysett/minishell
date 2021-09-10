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
	print_err(ms->prog_name, err);
	if (ms)
		free_minishell(ms);
	exit(EXIT_FAILURE);
}

char	*strdup_or_exit(char *str)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (!str)
		ft_error_exit(MEMORY_FAIL);
	return (new_str);
}

void	print_err(char *prog_name, t_err_code err)
{
	if (err == ERR_NO_PRINT)
		return ;
	ft_putstr_fd(prog_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err == MEMORY_FAIL)
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	else if (err == WRONG_QUOTING)
		ft_putstr_fd("Wrong quoting\n", STDERR_FILENO);
	else
		ft_putstr_fd("An error occurred\n", STDERR_FILENO);
}
