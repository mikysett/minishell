#ifndef EXECUTOR_H
# define EXECUTOR_H


// EXECUTOR
int	executor(t_minishell *ms, t_list *curr, int cmd_exit_code);
int	exec_cmd(t_cmd *cmd, t_std_io *std_io, t_list **redirect);
int	exec_builtin(t_cmd *cmd);
int	exec_std_cmd(t_cmd *cmd);
char	*set_cmd_path(char *cmd_name, char **paths);

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
