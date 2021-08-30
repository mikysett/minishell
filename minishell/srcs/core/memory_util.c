#include "minishell.h"

t_minishell	*init_minishell_mem(char **envp)
{
	t_minishell	*minishell;

	minishell = calloc_or_exit(1, sizeof(t_minishell));
	get_minishell(minishell);
	// TODO It will be better to create a deep copy instead of just passing the reference
	minishell->envp = envp;
	return (minishell);
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