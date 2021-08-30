#include "minishell.h"

static bool	set_here_doc(char *limiter);
static bool	set_redir_in(char *file_name);
static bool	set_redir_out(char *file_name, t_redir_type type);
static bool	set_redir_pipe(t_redir_type type);

bool	make_redir(t_redirect *redir)
{
	if (redir->type == REDIR_HERE_DOC)
		return (set_here_doc(redir->file_name));
	else if (redir->type == REDIR_IN)
		return (set_redir_in(redir->file_name));
	else if (redir->type == REDIR_OUT || redir->type == REDIR_OUT_APPEND)
		return (set_redir_out(redir->file_name, redir->type));
	else if (redir->type == REDIR_PIPE_IN || redir->type == REDIR_PIPE_OUT)
		return (set_redir_pipe(redir->type));
	else
		return (false);
}

static bool	set_here_doc(char *limiter)
{
	const int	limiter_len = ft_strlen(limiter) + 1;
	char		*line;
	int			here_doc_pipe[2];

	// TODO could be rethinked to use set_redir_pipe and exploiting
	// the same modus operandi
	if (ft_init_pipe_fd(here_doc_pipe) == false)
		return (false);
	line = readline("> ");
	while (ft_strncmp(limiter, line, limiter_len))
	{
		write(here_doc_pipe[PIPE_WRITE], line, ft_strlen(line));
		write(here_doc_pipe[PIPE_WRITE], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (close(STDIN_FILENO) == -1)
	{
		perror("minishell");
		return (false);
	}
	// TODO fix that part, probably becomes an infinite loop because the pipe is writing and reading
	// in the same place
	if (ft_set_dup2(here_doc_pipe[PIPE_READ], STDIN_FILENO) == false)
		return (false);
	return (true);
}

static bool	set_redir_in(char *file_name)
{
	int	file_fd;

	file_fd = ft_init_file_fd(file_name, O_RDONLY, 0);
	if (file_fd == -1)
		return (false);
	if (ft_set_dup2(file_fd, STDIN_FILENO) == false)
		return (false);
	return (true);
}

static bool	set_redir_out(char *file_name, t_redir_type type)
{
	int	file_fd;

	if (type == REDIR_OUT)
		file_fd = ft_init_file_fd(file_name,
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		file_fd = ft_init_file_fd(file_name,
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file_fd == -1)
		return (false);
	if (ft_set_dup2(file_fd, STDOUT_FILENO) == false)
		return (false);
	return (true);
}

static bool	set_redir_pipe(t_redir_type type)
{
	int			file_fd;
	static int	cmd_pipe[2];

	if (type == REDIR_PIPE_OUT)
	{
		if (ft_init_pipe_fd(cmd_pipe) == false)
			return (false);
		if (ft_set_dup2(cmd_pipe[PIPE_WRITE], STDOUT_FILENO) == false)
			return (false);
	}
	else
	{
		if (ft_set_dup2(cmd_pipe[PIPE_READ], STDIN_FILENO) == false)
			return (false);
	}
	return (true);
}
