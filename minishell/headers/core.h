#ifndef CORE_H
# define CORE_H

// CORE_UTIL

t_minishell		*get_minishell(t_minishell *minishell);
t_prog_state	prog_state(t_prog_state set_prog_state);
void			ft_error_exit(t_err_code err);
void			print_err(t_err_code err);

// MEMORY_UTIL

t_minishell	*init_minishell_mem(void);
void		*calloc_or_exit(size_t count, size_t size);
void		free_minishell(t_minishell *ms);
void		free_tokens(t_minishell *ms);
void		del_token(void *token_void);

#endif
