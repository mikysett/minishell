#include "minishell.h"

static char		*last_consecutive_asterisk(char *str);
static int		get_str_to_match_len(char *str);
static char		*pos_last_match(char *d_name,
					char *str_to_match, int match_len);
static void		add_new_word_token(t_list **new_tokens, char *token_str);

void	save_expansion_if_match(t_list **new_tokens, char *d_name,
	char *token_str)
{
	const char	*original_d_name = d_name;
	int			str_to_match_len;

	while (*token_str != '*')
	{
		if (*d_name != *token_str)
			return ;
		token_str++;
		d_name++;
	}
	while (*token_str && *(token_str + 1))
	{
		token_str = last_consecutive_asterisk(token_str);
		str_to_match_len = get_str_to_match_len(token_str + 1);
		d_name = pos_last_match(d_name, token_str + 1, str_to_match_len);
		if (!d_name)
			return ;
		token_str += 1 + str_to_match_len;
	}
	add_new_word_token(new_tokens, (char *)original_d_name);
}

static char	*last_consecutive_asterisk(char *str)
{
	if (!*str)
		return (str);
	while (*str)
	{
		if (*(str + 1) != '*')
			break ;
		str++;
	}
	return (str);
}

static int	get_str_to_match_len(char *str)
{
	const char	*o_str = str;

	while (*str && *str != '*')
		str++;
	return (str - o_str);
}

static char	*pos_last_match(char *d_name, char *str_to_match, int match_len)
{
	char	*curr_match;
	int		nb_possible_matchs;

	nb_possible_matchs = ft_strlen(d_name) - match_len + 1;
	curr_match = NULL;
	while (nb_possible_matchs > 0)
	{
		if (!ft_strncmp(d_name, str_to_match, match_len))
			curr_match = d_name;
		nb_possible_matchs--;
		d_name++;
	}
	if (curr_match)
		return (curr_match + match_len);
	return (NULL);
}

static void	add_new_word_token(t_list **new_tokens, char *token_str)
{
	t_token	*new_token;
	t_list	*new_token_lst;

	new_token = calloc_or_exit(1, sizeof(t_token));
	new_token->type = WORD;
	new_token->str = strdup_or_exit(token_str);
	new_token_lst = ft_lstnew(new_token);
	if (!new_token_lst)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(new_tokens, new_token_lst);
}
