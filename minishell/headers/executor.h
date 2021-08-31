#ifndef EXECUTOR_H
# define EXECUTOR_H


// EXECUTOR
int	executor(t_minishell *ms, t_list *curr, int cmd_exit_code);
int	exec_cmd(t_cmd *cmd, t_list **redirect);
int	exec_builtin(t_cmd *cmd);
int	exec_std_cmd(t_cmd *cmd);
char	*set_cmd_path(char *cmd_name, char **paths);

// SETUP_REDIRECT
bool	setup_redirect(t_list **redirect, int id);
bool	ft_set_dup2(int dup_from_fd, int dup_to_fd);
bool	ft_init_pipe_fd(int pipe_fd[2]);
int		ft_init_file_fd(char *file, int oflag, int chmod);

// SETUP_REDIRECT_UTIL
bool	make_redir(t_redirect *redir);

#endif
