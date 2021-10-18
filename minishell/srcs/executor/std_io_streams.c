#include "minishell.h"

void	save_std_in(t_minishell *ms)
{
	if (ms->streams.stdin_saved == false)
	{
		ms->streams.stdin_fd = ft_set_dup(STDIN_FILENO);
		DEBUG(fprintf(stderr, "!!!! - SAVE stdin, fd: %d\n", ms->streams.stdin_fd);)
		if (ms->streams.stdin_fd == -1)
		{
			DEBUG(fprintf(stderr, "save std err\n");)
		}
		ms->streams.stdin_saved = true;
	}
}

void	save_std_out(t_minishell *ms)
{
	if (ms->streams.stdout_saved == false)
	{
		ms->streams.stdout_fd = ft_set_dup(STDOUT_FILENO);
		DEBUG(fprintf(stderr, "!!!! - SAVE stdout, fd: %d\n", ms->streams.stdout_fd);)
		if (ms->streams.stdin_fd == -1)
		{
			DEBUG(fprintf(stderr, "save std err\n");)
		}
		ms->streams.stdout_saved = true;
	}
}

void	set_curr_in(t_std_io *std_io, int in_fd)
{
	DEBUG(fprintf(stderr, "set_curr_in: stdio, in fd: %d\n", in_fd);)
	if (std_io->curr_in != STDIN_FILENO)
	{
		DEBUG(fprintf(stderr, "<< curr_in closing %d\n", std_io->curr_in);)
		close(std_io->curr_in);
	}
	std_io->curr_in = in_fd;
}

void	set_curr_out(t_std_io *std_io, int out_fd)
{
	DEBUG(fprintf(stderr, "set_curr_out: stdio, out fd: %d\n", out_fd);)
	if (std_io->curr_out != STDOUT_FILENO)
	{
		DEBUG(fprintf(stderr, "<< curr_out closing %d\n", std_io->curr_out);)
		close(std_io->curr_out);
	}
	std_io->curr_out = out_fd;
}
