#ifndef EXECUTOR_H
# define EXECUTOR_H


// EXECUTOR
int	executor(t_minishell *ms, t_list *curr, int cmd_exit_code);
int	exec_cmd(t_cmd *cmd, t_list **redirect);

// SETUP_REDIRECT
int	setup_redirect(t_list **redirect, int id, int group);
int	exec_builtin(t_cmd *cmd);
int	exec_std_cmd(t_cmd *cmd);

#endif
