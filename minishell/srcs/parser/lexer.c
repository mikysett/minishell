#include "minishell.h"

t_list	**lexer(char *line)
{
	char	*token_start;
	char	*token_end;
	t_list	**tokens;
	t_token	*curr_token;

	token_start = next_non_space(line);
	tokens = calloc_or_exit(1, sizeof(t_list **));
	while (token_start)
	{
		curr_token = calloc_or_exit(1, sizeof(t_token));
		curr_token->quote_type = get_quote_type(*token_start);
		if (curr_token->quote_type != NO_QUOTING)
			token_start++;
		token_end = get_token_end(token_start, curr_token->quote_type);
		if (!token_end)
			ft_error_exit(WRONG_QUOTING);
		curr_token->str = ft_strndup(token_start, token_start - token_end);
		if (!curr_token->str)
			ft_error_exit(MEMORY_FAIL);
		if (!save_token(tokens, curr_token))
			ft_error_exit(MEMORY_FAIL);
	}
}

char	*next_non_space(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else
			break ;
	}
	return (str);
}

t_quote_type	get_quote_type(char token_start)
{
	if (token_start == '\'')
		return (SINGLE_QUOTES);
	else if (token_start == '"')
		return (DOUBLE_QUOTES);
	else
		return (NO_QUOTING);
}

char	*get_token_end(char *str, t_quote_type quote_type)
{
	if (quote_type == NO_QUOTING)
		while (*str
			&& *str != ' ' && *str != '\t'
			&& !is_operator(*str))
			str++;
	else if (quote_type == SINGLE_QUOTES)
		while (*str
			&& *str != '\'')
			str++;
	else if (quote_type == DOUBLE_QUOTES)
		while (*str
			&& *str != '"')
			str++;
	if (!*str && quote_type != NO_QUOTING)
		return (NULL);
	return (str);
}

bool	is_operator(char c)
{
	if (c == '|' || c == '&'
		|| c == '(' || c == ')'
		|| c == '<' || c == '>')
		return (true);
	return (false);
}

bool	save_token(t_list **tokens, t_token *curr_token)
{
	t_list	*new_lst_el;
}