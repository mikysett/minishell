#ifndef CORE_H
# define CORE_H

// CORE_UTIL
t_minishell		*get_minishell(t_minishell *minishell);
t_prog_state	prog_state(t_prog_state set_prog_state);
void			ft_error_exit(t_err_code err);
void			print_err(t_err_code err);

// MEMORY_UTIL
t_minishell	*init_minishell(char *prog_name, char **envp);
char		**ft_set_paths(char **envp);
void		*calloc_or_exit(size_t count, size_t size);
void		free_minishell(t_minishell *ms);
void		free_tokens(t_minishell *ms);
void		del_token(void *token_void);

// REDIR_UTIL
bool	is_redir_in(t_redir_type type);
bool	ft_set_dup2(int dup_from_fd, int dup_to_fd);
bool	ft_init_pipe_fd(int pipe_fd[2]);
int		ft_init_file_fd(char *file, int oflag, int chmod);

#endif
