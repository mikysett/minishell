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
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(&envp[i][5], ':'));
		i++;
	}
	return (NULL);
}

void	*calloc_or_exit(size_t count, size_t size)
{
	void	*result;
	
	result = ft_calloc(count, size);
	if (!result)
		ft_error_exit(MEMORY_FAIL);
	return (result);
}

void	free_minishell(t_minishell *ms)
{
	if (ms)
	{
		free_tokens(ms);
		free(ms);
	}
}

void	free_tokens(t_minishell *ms)
{
	if (ms->tokens)
	{
		ft_lstclear(ms->tokens, del_token);
		free(ms->tokens);
		ms->tokens = NULL;
	}
}

void	del_token(void *token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	if (token)
	{
		free(token->str);
		free(token);
	}
}