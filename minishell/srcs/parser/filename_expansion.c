#include "minishell.h"

static bool		has_filename_expansion(char *str);
static t_list	**expand_filenames(char *str);
static int		save_filename_exp(t_list **new_tokens, struct dirent *dir_entry,
	char *token_str);
static char		*last_consecutive_asterisk(char *str);
static int		get_str_to_match_len(char *str);
static char		*pos_last_match(char *d_name, char *str_to_match, int match_len);
static void		add_new_word_token(t_list **new_tokens, char *token_str);

void	filename_expansion(t_list **tokens)
{
	t_list	*buf;
	t_list	*curr;
	t_list	*prev;
	t_token	*curr_token;
	t_list	**new_tokens;

	prev = NULL;
	curr = *tokens;
	while (curr)
	{
		curr_token = (t_token *)curr->content;
		if (has_filename_expansion(curr_token->str))
		{
			new_tokens = expand_filenames(curr_token->str);
			if (new_tokens)
			{
				if (*new_tokens)
				{
					if (!prev)
						*tokens = *new_tokens;
					else
						prev->next = *new_tokens;
					buf = ft_lstlast(*new_tokens);
					buf->next = curr->next;
					ft_lstdelone(curr, del_token);
					curr = buf;
				}
				free(new_tokens);
			}
		}
		prev = curr;
		curr = curr->next;
	}
}

static bool	has_filename_expansion(char *str)
{
	t_quote_type	prev_qt_type;

	prev_qt_type = NO_QUOTING;
	while (*str)
	{
		if (!update_quote_type(get_quote_type(*str), &prev_qt_type))
			if (prev_qt_type == NO_QUOTING && *str == '*')
				return (true);
		str++;
	}
	return (false);
}

static t_list	**expand_filenames(char *str)
{
	t_list		**new_tokens;
	const char	*curr_dir_str = getcwd(NULL, 0);
	DIR			*curr_dir;

	curr_dir = opendir(curr_dir_str);
	if (curr_dir_str)
		free((void *)curr_dir_str);
	if (!curr_dir)
	{
		perror(get_minishell(NULL)->prog_name);
		return (NULL);
	}
	errno = 0;		// Necessary to check readdir error result
	new_tokens = calloc_or_exit(1, sizeof(t_list *));
	while (save_filename_exp(new_tokens, readdir(curr_dir), str) != -1)
		continue ;
	closedir(curr_dir);
	if (errno != 0)
		perror(get_minishell(NULL)->prog_name);
	return (new_tokens);
}

static int	save_filename_exp(t_list **new_tokens, struct dirent *dir_entry,
	char *token_str)
{
	char	*d_name;
	int		str_to_match_len;

	if (!dir_entry)
		return (-1);
	d_name = dir_entry->d_name;
	while (*token_str != '*')
	{
		if (*d_name != *token_str)
			return (0);
		token_str++;
		d_name++;
	}
	while (*d_name)
	{
		token_str = last_consecutive_asterisk(token_str);
		if (!*token_str || !*(token_str + 1))
			break ;
		str_to_match_len = get_str_to_match_len(token_str + 1);
		d_name = pos_last_match(d_name, token_str + 1, str_to_match_len);
		if (!d_name)
			return (0);
		token_str += 1 + str_to_match_len;
	}
	if (!*d_name || (*token_str == '*' && !*(token_str + 1)))
	{
		DEBUG(printf("%sMATCHED          : %s\n%s", CLR_GREEN, dir_entry->d_name, CLR_WHITE);)
		add_new_word_token(new_tokens, dir_entry->d_name);
	}
	return (0);
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
	DEBUG (
		printf("  %sd_name:%-14s | str_to_match: %-8.*s | match_len: %d | nb_pos: %d\n%s",
			CLR_YELLOW, d_name, match_len, str_to_match, match_len, nb_possible_matchs, CLR_WHITE);
	)
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
