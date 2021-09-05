#include "minishell.h"

char	*next_token(char *s, t_quote_type quote_type)
{
	if (quote_type != NO_QUOTING)
		s++;
	s = next_non_space(s);
	return (s);
}

char	*next_non_space(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else
			return (str);
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
