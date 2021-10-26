#ifndef EXECUTOR_H
# define EXECUTOR_H


// EXECUTOR
t_list	*executor(t_minishell *ms, t_list *curr);

// EXEC_STD_CMD
int		exec_std_cmd(t_cmd *cmd);

// SET_CMD_PATH
char	*set_cmd_path(t_minishell *ms, t_cmd *cmd);

// SETUP_REDIRECT
bool	setup_redirect(t_std_io *std_io, t_list **redirect, int id);

// MAKE_REDIR
bool	make_redir(t_std_io *std_io, t_redirect *redir);

// STD_IO_STREAMS
void	save_std_in(t_minishell *ms);
void	save_std_out(t_minishell *ms);
void	set_curr_in(t_std_io *std_io, int in_fd);
void	set_curr_out(t_std_io *std_io, int out_fd);

// STD_IO_STREAMS_UTIL
void	restore_std_io(bool has_redir_out, bool has_redir_in);

#endif
