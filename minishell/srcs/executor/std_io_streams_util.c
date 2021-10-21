#include "minishell.h"

static void	restore_std_in(t_minishell *ms);
static void	restore_std_out(t_minishell *ms);

void	restore_std_io(bool has_redir_out, bool has_redir_in)
{
	t_minishell	*ms;

	ms = get_minishell(NULL);
	if (has_redir_in == false)
		restore_std_in(ms);
	if (has_redir_out == false)
		restore_std_out(ms);
}

// TODO error handling missing for dup and dup2 (but this should never happen)
static void	restore_std_in(t_minishell *ms)
{
	if (ms->streams.stdin_saved == true)
	{
		DEBUG(fprintf(stderr, "%s< RESTORE stdin%s\n", CLR_BLUE, CLR_WHITE);)
		ft_set_dup2(ms->streams.stdin_fd, STDIN_FILENO);
		set_curr_in(&ms->streams, ms->streams.stdin_fd);
		ms->streams.stdin_saved = false;
	}
}

static void	restore_std_out(t_minishell *ms)
{
	if (ms->streams.stdout_saved == true)
	{
		DEBUG(fprintf(stderr, "%s> RESTORE stdout%s\n", CLR_BLUE, CLR_WHITE);)
		ft_set_dup2(ms->streams.stdout_fd, STDOUT_FILENO);
		set_curr_out(&ms->streams, ms->streams.stdout_fd);
		ms->streams.stdout_saved = false;
	}
}