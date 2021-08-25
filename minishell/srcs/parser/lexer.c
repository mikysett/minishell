#include "minishell.h"

t_list	**lexer(char *line, t_list **tokens)
{
	char	*token_start;
	char	*token_end;
	t_token	*curr_token;

	token_start = next_token(line, NO_QUOTING);
	while (*token_start)
	{
		curr_token = init_token(token_start);
		if (curr_token->quote_type != NO_QUOTING)
			token_start++;
		token_end = get_token_end(token_start, curr_token);
		curr_token->str = ft_strndup(token_start, token_end - token_start);
		if (!curr_token->str)
			ft_error_exit(MEMORY_FAIL);
		save_token(tokens, curr_token);
		token_start = next_token(token_end, curr_token->quote_type);
	}
	return (tokens);
}

t_token	*init_token(char *token_start)
{
	t_token	*curr_token;

	curr_token = calloc_or_exit(1, sizeof(t_token));
	curr_token->quote_type = get_quote_type(*token_start);
	curr_token->type = get_token_type(token_start);
	return (curr_token);
}

t_quote_type	get_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTES);
	else if (c == '"')
		return (DOUBLE_QUOTES);
	else
		return (NO_QUOTING);
}
