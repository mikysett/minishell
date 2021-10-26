#include "minishell.h"

static bool	setup_heredoc_redir(t_std_io *std_io, t_list *curr, int id,
				t_has_redirs *has_redirs);
static bool	setup_pipe_redir(t_std_io *std_io, t_list *curr, int id,
				t_has_redirs *has_redirs);
static bool	setup_other_redir(t_std_io *std_io, t_list *curr, int id,
				t_has_redirs *has_redirs);

bool	setup_redirect(t_std_io *std_io, t_list **redirect, int id)
{
	t_has_redirs	has_redirs;

	has_redirs.in = false;
	has_redirs.out = false;
	if (!setup_heredoc_redir(std_io, *redirect, id, &has_redirs))
		return (false);
	if (!setup_pipe_redir(std_io, *redirect, id, &has_redirs))
		return (false);
	if (!setup_other_redir(std_io, *redirect, id, &has_redirs))
		return (false);
	restore_std_io(has_redirs.out, has_redirs.in);
	return (true);
}

static bool	setup_heredoc_redir(t_std_io *std_io, t_list *curr, int id,
	t_has_redirs *has_redirs)
{
	t_redirect		*curr_redir;

	while (curr)
	{
		curr_redir = (t_redirect *)curr->content;
		if (curr_redir->cmd_id == id
			&& curr_redir->type == REDIR_HERE_DOC)
		{
			has_redirs->in = true;
			if (!make_redir(std_io, curr_redir))
				return (false);
		}
		else if (curr_redir->cmd_id > id)
			break ;
		curr = curr->next;
	}
	return (true);
}

static bool	setup_pipe_redir(t_std_io *std_io, t_list *curr, int id,
	t_has_redirs *has_redirs)
{
	t_redirect		*curr_redir;

	while (curr)
	{
		curr_redir = (t_redirect *)curr->content;
		if (curr_redir->cmd_id == id
			&& (curr_redir->type == REDIR_PIPE_IN
				|| curr_redir->type == REDIR_PIPE_OUT))
		{
			if (curr_redir->type == REDIR_PIPE_IN)
				has_redirs->in = true;
			else
				has_redirs->out = true;
			if (!make_redir(std_io, curr_redir))
				return (false);
		}
		else if (curr_redir->cmd_id > id)
			break ;
		curr = curr->next;
	}
	return (true);
}

static bool	setup_other_redir(t_std_io *std_io, t_list *curr, int id,
	t_has_redirs *has_redirs)
{
	t_redirect		*curr_redir;

	while (curr)
	{
		curr_redir = (t_redirect *)curr->content;
		if (curr_redir->cmd_id == id
			&& (curr_redir->type == REDIR_IN
				|| curr_redir->type == REDIR_OUT
				|| curr_redir->type == REDIR_OUT_APPEND))
		{
			if (curr_redir->type == REDIR_IN)
				has_redirs->in = true;
			else
				has_redirs->out = true;
			if (!make_redir(std_io, curr_redir))
				return (false);
		}
		else if (curr_redir->cmd_id > id)
			break ;
		curr = curr->next;
	}
	return (true);
}
