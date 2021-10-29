/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:21:42 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:22:09 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

// CORE_UTIL
t_minishell		*get_minishell(t_minishell *minishell);
t_prog_state	prog_state(t_prog_state set_prog_state);
char			*strdup_or_exit(char *str);
void			ft_error_exit(t_err_code err);
void			print_err(char *prog_name, t_err_code err);

// MEMORY_UTIL
t_minishell		*init_minishell(char **envp);
char			**ft_set_paths(char **envp);
void			*calloc_or_exit(size_t count, size_t size);
void			reset_minishell(t_minishell *ms);

// FREE_MEM
void			free_minishell(t_minishell *ms);
void			*free_lst(t_list **lst, void (*del)(void *));

// FREE_MEM_UTIL
void			del_token(void *token_void);
void			del_instruction(void *instruction_void);
void			del_redirect(void *redirect_void);
void			del_env_var(void *env_var_void);
void			free_env_and_paths(t_minishell *ms);

// REDIR_UTIL
int				ft_set_dup(int old_fd);
bool			ft_set_dup2(int dup_from_fd, int dup_to_fd);
bool			ft_init_pipe_fd(int pipe_fd[2]);
int				ft_init_file_fd(char *file, int oflag, int chmod);

#endif
