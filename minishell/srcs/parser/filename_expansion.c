#include "minishell.h"

static bool		has_filename_expansion(char *str);
static t_list	*insert_new_tokens(t_list **tokens, t_list *prev, t_list *curr);
static t_list	**expand_filenames(t_list **new_tokens, char *str);
static DIR		*open_current_dir(const char *curr_dir_str);

void	filename_expansion(t_list **tokens)
{
	t_list	*curr;
	t_list	*prev;

	prev = NULL;
	curr = *tokens;
	while (curr)
	{
		if (has_filename_expansion(((t_token *)curr->content)->str))
			curr = insert_new_tokens(tokens, prev, curr);
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

static t_list	*insert_new_tokens(t_list **tokens, t_list *prev, t_list *curr)
{
	t_list	**new_tokens;
	t_list	*new_curr;

	new_curr = curr;
	new_tokens = calloc_or_exit(1, sizeof(t_list *));
	new_tokens = expand_filenames(new_tokens, ((t_token *)curr->content)->str);
	if (new_tokens)
	{
		if (*new_tokens)
		{
			if (!prev)
				*tokens = *new_tokens;
			else
				prev->next = *new_tokens;
			new_curr = ft_lstlast(*new_tokens);
			new_curr->next = curr->next;
			ft_lstdelone(curr, del_token);
			curr = new_curr;
		}
		free(new_tokens);
	}
	return (new_curr);
}

static t_list	**expand_filenames(t_list **new_tokens, char *str)
{
	DIR				*curr_dir;
	struct dirent	*curr_dir_entry;
	const char		*curr_dir_str = getcwd(NULL, 0);

	curr_dir = open_current_dir(curr_dir_str);
	if (curr_dir_str)
		free((void *)curr_dir_str);
	errno = 0;
	curr_dir_entry = readdir(curr_dir);
	while (curr_dir_entry)
	{
		save_expansion_if_match(new_tokens, curr_dir_entry->d_name, str);
		curr_dir_entry = readdir(curr_dir);
	}
	closedir(curr_dir);
	if (errno != 0)
		perror(get_minishell(NULL)->prog_name);
	return (new_tokens);
}

static DIR	*open_current_dir(const char *curr_dir_str)
{
	const DIR	*curr_dir = opendir(curr_dir_str);

	if (!curr_dir)
	{
		perror(get_minishell(NULL)->prog_name);
		return (NULL);
	}
	return ((DIR *)curr_dir);
}
