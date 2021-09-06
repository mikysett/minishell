#include "minishell.h"

t_minishell	*init_minishell(char *prog_name, char **envp)
{
	t_minishell	*minishell;

	minishell = calloc_or_exit(1, sizeof(t_minishell));
	get_minishell(minishell);
	minishell->prog_name = prog_name;
	minishell->env_vars = init_env_vars(envp);
	save_envp(minishell);
	minishell->paths = ft_set_paths(envp);
	minishell->streams.curr_in = STDIN_FILENO;
	minishell->streams.curr_out = STDOUT_FILENO;
	return (minishell);
}

char	**ft_set_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(&envp[i][5], ':');
			if (!paths)
				ft_error_exit(MEMORY_FAIL);
			return (paths);
		}
		i++;
	}
	paths = ft_split("", ' ');
	if (!paths)
		ft_error_exit(MEMORY_FAIL);
	return (paths);
}

void	*calloc_or_exit(size_t count, size_t size)
{
	void	*result;
	
	result = ft_calloc(count, size);
	if (!result)
		ft_error_exit(MEMORY_FAIL);
	return (result);
}

void	reset_minishell(t_minishell *ms)
{
	ms->tokens = free_lst(ms->tokens, del_token);
	ms->instructions = free_lst(ms->instructions, del_instruction);
	ms->redirect = free_lst(ms->redirect, del_redirect);
}