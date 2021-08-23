#include "minishell.h"

t_list	**lexer(char *line)
{
	char	*token_start;
	char	*token_end;
	t_list	**tokens;

	token_start = next_non_space(line);
	tokens = calloc_or_exit(1, sizeof(t_list **));
	while (token_start)
	{
		token_end = get_token_end(token_start);

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

char	*get_token_end(char *str)
{
	while (*str
		&& *str != ' ' && *str != '\t'
		&& !is_operator(*str))
		str++;
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