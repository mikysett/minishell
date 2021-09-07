#include "minishell.h"

static t_token	*init_token(char *token_start);
static t_token_type	get_token_type(char *token_start);
static void	save_token(t_list **tokens, t_token *curr_token);

t_list	**lexer(char *line, t_list **tokens)
{
	char			*token_start;
	char			*token_end;
	t_token			*curr_token;

	token_start = next_non_space(line);
	while (*token_start)
	{
		curr_token = init_token(token_start);
		token_end = get_token_end(token_start, curr_token);
		curr_token->str = ft_strndup(token_start, token_end - token_start);
		if (!curr_token->str)
			ft_error_exit(MEMORY_FAIL);
		save_token(tokens, curr_token);
		token_start = next_non_space(token_end);
	}
	return (tokens);
}

static t_token	*init_token(char *token_start)
{
	t_token	*curr_token;

	curr_token = calloc_or_exit(1, sizeof(t_token));
	curr_token->type = get_token_type(token_start);
	return (curr_token);
}

static t_token_type	get_token_type(char *token_start)
{
	if (is_operator(token_start))
		return (OPERATOR);
	else
		return (WORD);
}

static void	save_token(t_list **tokens, t_token *curr_token)
{
	t_list	*new_lst_el;

	new_lst_el = ft_lstnew(curr_token);
	if (!new_lst_el)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(tokens, new_lst_el);
}
