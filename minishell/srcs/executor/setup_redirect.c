#include "minishell.h"

bool	setup_redirect(t_std_io *std_io, t_list **redirect, int id)
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
			if (!make_redir(std_io, curr_redir))
				return (false);
		}
		curr = curr->next;
	}
	restore_std_io(has_redir_out, has_redir_in);
	return (true);
}

