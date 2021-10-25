#include "minishell.h"

bool	is_redir_in(t_redir_type type)
{
	if (type == REDIR_HERE_DOC || type == REDIR_IN)
		return (true);
	return (false);
}

int	ft_set_dup(int old_fd)
{
	int	new_fd;

	new_fd = dup(old_fd);
	if (new_fd == -1)
		perror(get_minishell(NULL)->prog_name);
	return (new_fd);
}

bool	ft_set_dup2(int dup_from_fd, int dup_to_fd)
{
	if (dup2(dup_from_fd, dup_to_fd) == -1)
	{
		perror(get_minishell(NULL)->prog_name);
		return (false);
	}
	return (true);
}

bool	ft_init_pipe_fd(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror(get_minishell(NULL)->prog_name);
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
	{
		ft_putstr_fd(get_minishell(NULL)->prog_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(file);
	}
	return (file_fd);
}
