#include "minishell.h"

t_quote_type	get_quote_type(char c)
{
	if (c == '\'')
		return (SINGLE_QUOTES);
	else if (c == '"')
		return (DOUBLE_QUOTES);
	else
		return (NO_QUOTING);
}

bool	update_quote_type(t_quote_type curr, t_quote_type *prev)
{
	if (*prev == NO_QUOTING && curr != NO_QUOTING)
	{
		*prev = curr;
		return (true);
	}
	else if (*prev != NO_QUOTING && *prev == curr)
	{
		*prev = NO_QUOTING;
		return (true);
	}
	return (false);
}
