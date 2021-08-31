#include "minishell.h"

char	**get_envp(void)
{
	t_minishell	*ms;

	ms = get_minishell(NULL);
	return (ms->envp);
}