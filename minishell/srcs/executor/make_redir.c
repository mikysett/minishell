#include "minishell.h"

static bool	set_here_doc(t_std_io *std_io, char *limiter);
static bool	set_redir_in(t_std_io *std_io, char *file_name);
static bool	set_redir_out(t_std_io *std_io, char *file_name, t_redir_type type);
static bool	set_redir_pipe(t_std_io *std_io, t_redir_type type);

bool	make_redir(t_std_io *std_io, t_redirect *redir)
{
	if (redir->type == REDIR_HERE_DOC)
		return (set_here_doc(std_io, redir->file_name));
	else if (redir->type == REDIR_IN)
		return (set_redir_in(std_io, redir->file_name));
	else if (redir->type == REDIR_OUT || redir->type == REDIR_OUT_APPEND)
		return (set_redir_out(std_io, redir->file_name, redir->type));
	else if (redir->type == REDIR_PIPE_IN || redir->type == REDIR_PIPE_OUT)
		return (set_redir_pipe(std_io, redir->type));
	else
	{
		DEBUG(fprintf(stderr, "Error: make redir");)
		return (false);
	}
}

static bool	set_here_doc(t_std_io *std_io, char *limiter)
{
	const int	limiter_len = ft_strlen(limiter) + 1;
	char		*line;
	int			here_doc_pipe[2];

	save_std_in(get_minishell(NULL));
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
	if (close(here_doc_pipe[PIPE_WRITE]) == -1
		|| ft_set_dup2(here_doc_pipe[PIPE_READ], STDIN_FILENO) == false)
	{
		perror(get_minishell(NULL)->prog_name);
		return (false);
	}
	set_curr_in(std_io, here_doc_pipe[PIPE_READ]);
	return (true);
}

static bool	set_redir_in(t_std_io *std_io, char *file_name)
{
	int	file_fd;

	save_std_in(get_minishell(NULL));
	file_fd = ft_init_file_fd(file_name, O_RDONLY, 0);
	if (file_fd == -1)
		return (false);
	set_curr_in(std_io, file_fd);
	if (ft_set_dup2(file_fd, STDIN_FILENO) == false)
		return (false);
	DEBUG(fprintf(stderr, "%s< redir_in (fd %d to %d)%s\n",
		CLR_BLUE, file_fd, STDIN_FILENO, CLR_WHITE);)
	return (true);
}

static bool	set_redir_out(t_std_io *std_io, char *file_name, t_redir_type type)
{
	int	file_fd;

	save_std_out(get_minishell(NULL));
	if (type == REDIR_OUT)
		file_fd = ft_init_file_fd(file_name,
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		file_fd = ft_init_file_fd(file_name,
			O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (file_fd == -1)
		return (false);
	set_curr_out(std_io, file_fd);
	if (ft_set_dup2(file_fd, STDOUT_FILENO) == false)
		return (false);
	DEBUG(fprintf(stderr, "%s> redir_out (fd %d to %d)%s\n",
		CLR_BLUE, file_fd, STDOUT_FILENO, CLR_WHITE);)
	return (true);
}

static bool	set_redir_pipe(t_std_io *std_io, t_redir_type type)
{
	static int	cmd_pipe[2];

	if (type == REDIR_PIPE_OUT)
	{
		save_std_out(get_minishell(NULL));
		if (ft_init_pipe_fd(cmd_pipe) == false)
			return (false);
		set_curr_out(std_io, cmd_pipe[PIPE_WRITE]);
		DEBUG(fprintf(stderr, "%spipe fd - read: %2d   write: %2d%s\n",
			CLR_GREEN, cmd_pipe[0], cmd_pipe[1], CLR_WHITE);)
		if (ft_set_dup2(cmd_pipe[PIPE_WRITE], STDOUT_FILENO) == false)
			return (false);
		DEBUG(fprintf(stderr, "%s> redir_pipe WRITE in STDOUT%s\n", CLR_BLUE, CLR_WHITE);)
	}
	else
	{
		save_std_in(get_minishell(NULL));
		set_curr_in(std_io, cmd_pipe[PIPE_READ]);
		DEBUG(fprintf(stderr, "%spipe fd - read: %2d   write: %2d%s\n",
			CLR_GREEN, cmd_pipe[0], cmd_pipe[1], CLR_WHITE);)
		if (ft_set_dup2(cmd_pipe[PIPE_READ], STDIN_FILENO) == false)
			return (false);
		DEBUG(fprintf(stderr, "%s< redir_pipe READ in STDIN%s\n", CLR_BLUE, CLR_WHITE);)
	}
	return (true);
}
