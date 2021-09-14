#include "minishell.h"

static char	*get_token_operator_end(char *str);
static char	*get_token_word_end(char *str);

char	*get_token_end(char *str, t_token *token)
{
	if (token->type == OPERATOR)
		return (get_token_operator_end(str));
	else
		return (get_token_word_end(str));
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

static char	*get_token_word_end(char *str)
{
	t_quote_type	prev_qt;
	bool			open_quote;

	prev_qt = NO_QUOTING;
	open_quote = false;
	while (*str)
	{
		if (update_quote_type(get_quote_type(*str), &prev_qt))
			open_quote = !open_quote;
		if (prev_qt == NO_QUOTING
			&& (*str == ' ' || *str == '\t' || is_operator(str)))
			return (str);
		str++;
	}
	if (!*str && open_quote == true)
	{
		print_err(get_minishell(NULL)->prog_name, WRONG_QUOTING);
		prog_state(PARSER_ERROR);
	}
	return (str);
}
