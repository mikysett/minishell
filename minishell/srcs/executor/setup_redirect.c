#include "minishell.h"

bool	setup_redirect(t_list **redirect, int id)
{
	t_list		*curr;
	t_redirect	*curr_redir;
	bool		has_redir_in;
	bool		has_redir_out;

	has_redir_in = false;
	has_redir_out = false;
	curr = *redirect;
	while (curr)
	{
		curr_redir = (t_redirect *)curr->content;
		if (curr_redir->cmd_id == id)
		{
			if (has_redir_in == false && is_redir_in(curr_redir->type))
				has_redir_in = true;
			else if (has_redir_out == false)
				has_redir_out = true;
			if (!make_redir(curr_redir))
				return (false);
		}
		curr = curr->next;
	}
	restore_std_io(has_redir_out, has_redir_in);
	return (true);
}

bool	is_redir_in(t_redir_type type)
{
	if (type == REDIR_HERE_DOC || type == REDIR_IN || type == REDIR_PIPE_IN)
		return (true);
	return (false);
}

bool	ft_set_dup2(int dup_from_fd, int dup_to_fd)
{
	if (dup2(dup_from_fd, dup_to_fd) == -1)
	{
		perror("minishell");
		return (false);
	}
	return (true);
}

bool	ft_init_pipe_fd(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell");
		return (false);
	}
	return (true);
}

int	ft_init_file_fd(char *file, int oflag, int chmod)
{
	int	file_fd;

	if (chmod)
		file_fd = open(file, oflag, chmod);
	else
		file_fd = open(file, oflag);
	if (file_fd == -1)
		perror(file);
	return (file_fd);
}
