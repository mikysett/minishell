#include "minishell.h"

static char	*get_token_operator_end(char *str);
static char	*get_token_word_end(char *str, t_quote_type quote_type);

t_token_type	get_token_type(char *token_start)
{
	if (is_operator(token_start))
		return (OPERATOR);
	else
		return (WORD);
}

char	*get_token_end(char *str, t_token *token)
{
	if (token->type == OPERATOR)
		return (get_token_operator_end(str));
	else
		return (get_token_word_end(str, token->quote_type));
}

static char	*get_token_operator_end(char *str)
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

static char	*get_token_word_end(char *str, t_quote_type quote_type)
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

void	save_token(t_list **tokens, t_token *curr_token)
{
	t_list	*new_lst_el;

	new_lst_el = ft_lstnew(curr_token);
	if (!new_lst_el)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(tokens, new_lst_el);
}
