#include "minishell.h"

char	**get_envp(void)
{
	t_minishell	*ms;

	ms = get_minishell(NULL);
	return (ms->envp);
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}