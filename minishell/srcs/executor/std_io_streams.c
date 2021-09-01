#include "minishell.h"

void	restore_std_io(bool has_redir_out, bool has_redir_in)
{
	if (has_redir_in == false)
		restore_std_in(get_minishell(NULL));
	if (has_redir_out == false)
		restore_std_out(get_minishell(NULL));
}

void	save_std_in(t_minishell *ms)
{
	if (ms->streams.stdin_saved == false)
	{
		DEBUG(fprintf(stderr, "!!!! - SAVE stdin\n");)
		ms->streams.stdin_fd = dup(STDIN_FILENO);
		ms->streams.stdin_saved = true;
	}
}

void	save_std_out(t_minishell *ms)
{
	if (ms->streams.stdout_saved == false)
	{
		DEBUG(fprintf(stderr, "!!!! - SAVE stdout\n");)
		ms->streams.stdout_fd = dup(STDOUT_FILENO);
		ms->streams.stdout_saved = true;
	}
}

// TODO error handling missing for dup and dup2 (but this should never happen)

void	restore_std_in(t_minishell *ms)
{
	if (ms->streams.stdin_saved == true)
	{
		DEBUG(fprintf(stderr, "!!!! - RESTORE stdin\n");)
		ft_set_dup2(ms->streams.stdin_fd, STDIN_FILENO);
		ms->streams.stdin_saved = false;
	}
}

void	restore_std_out(t_minishell *ms)
{
	if (ms->streams.stdout_saved == true)
	{
		DEBUG(fprintf(stderr, "!!!! - RESTORE stdout\n");)
		ft_set_dup2(ms->streams.stdout_fd, STDOUT_FILENO);
		ms->streams.stdout_saved = false;
	}
}