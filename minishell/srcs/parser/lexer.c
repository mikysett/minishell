#include "minishell.h"

t_list	**lexer(char *line, t_list **tokens)
{
	char	*token_start;
	char	*token_end;
	t_token	*curr_token;

	token_start = next_non_space(line);
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

t_quote_type	get_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTES);
	else if (c == '"')
		return (DOUBLE_QUOTES);
	else
		return (NO_QUOTING);
}

t_token_type	get_token_type(char *token_start)
{
	if (is_operator(token_start))
		return (operator);
	else
		return (word);
}

char	*get_token_end(char *str, t_token *token)
{
	if (token->type == operator)
		return (get_token_operator_end(str));
	else
		return (get_token_word_end(str, token->quote_type));
}

char	*get_token_operator_end(char *str)
{
	if (ft_strlen(str) >= 2
		&& ((*str == '&' && *(str + 1) == '&')
			|| (*str == '|' && *(str + 1) == '|')
			|| (*str == '<' && *(str + 1) == '<')
			|| (*str == '>' && *(str + 1) == '>')))
		return (str + 2);
	else
		return (str + 1);
}

char	*get_token_word_end(char *str, t_quote_type quote_type)
{
	if (quote_type == NO_QUOTING)
		while (*str
			&& *str != ' ' && *str != '\t'
			&& !is_operator(str))
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
	{
		print_err(WRONG_QUOTING);
		prog_state(PARSER_ERROR);
	}
	return (str);
}

bool	is_operator(char *str)
{
	if (*str == '|' || *str == '(' || *str == ')'
		|| *str == '<' || *str == '>')
		return (true);
	else if (ft_strlen(str) >= 2 && *str == '&' && *(str + 1) == '&')
		return (true);
	return (false);
}

void	save_token(t_list **tokens, t_token *curr_token)
{
	t_list	*new_lst_el;

	new_lst_el = ft_lstnew(curr_token);
	if (!new_lst_el)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(tokens, new_lst_el);
}

char	*next_token(char *s, t_quote_type quote_type)
{
	if (quote_type != NO_QUOTING)
		s++;
	s = next_non_space(s);
	return (s);
}
