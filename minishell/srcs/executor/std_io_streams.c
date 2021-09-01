#include "minishell.h"

void	save_std_in(t_minishell *ms)
{
	if (ms->streams.stdin_saved == false)
	{
		printf("!!!!\\\\SAVE stdin\n");
		ms->streams.stdin_fd = dup(STDIN_FILENO);
		ms->streams.stdin_saved = true;
	}
}

void	save_std_out(t_minishell *ms)
{
	if (ms->streams.stdout_saved == false)
	{
		printf("!!!!\\\\SAVE stdout\n");
		ms->streams.stdout_fd = dup(STDOUT_FILENO);
		ms->streams.stdout_saved = true;
	}
}

// TODO error handling missing for dup and dup2 (but this should never happen)

void	restore_std_in(t_minishell *ms)
{
	if (ms->streams.stdin_saved == true)
	{
		printf("!!!!\\\\RESTORE stdin\n");
		ft_set_dup2(ms->streams.stdin_fd, STDIN_FILENO);
		ms->streams.stdin_saved = false;
	}
}

void	restore_std_out(t_minishell *ms)
{
	if (ms->streams.stdout_saved == true)
	{
		printf("!!!!\\\\RESTORE stdout\n");
		ft_set_dup2(ms->streams.stdout_fd, STDOUT_FILENO);
		ms->streams.stdout_saved = false;
	}
}