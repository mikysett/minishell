#include "minishell.h"

static char	*get_token_operator_end(char *str);
static char	*get_token_word_end(char *str);
static t_quote_type	get_quote_type(char c);
static void	set_quote_status(t_quote_type *prev_qt, t_quote_type new_qt,
	bool *open_quote);

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
		set_quote_status(&prev_qt, get_quote_type(*str), &open_quote);
		if (prev_qt == NO_QUOTING
			&& (*str == ' ' || *str == '\t' || is_operator(str)))
			return (str);
		str++;
	}
	if (!*str && open_quote == true)
	{
		print_err(WRONG_QUOTING);
		prog_state(PARSER_ERROR);
	}
	return (str);
}

static t_quote_type	get_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTES);
	else if (c == '"')
		return (DOUBLE_QUOTES);
	else
		return (NO_QUOTING);
}

static void	set_quote_status(t_quote_type *prev_qt, t_quote_type new_qt,
	bool *open_quote)
{
	if (*prev_qt == NO_QUOTING && new_qt != NO_QUOTING)
	{
		*prev_qt = new_qt;
		*open_quote = true;
	}
	else if (*prev_qt != NO_QUOTING && *prev_qt == new_qt)
	{
		*prev_qt = NO_QUOTING;
		*open_quote = false;
	}
}
