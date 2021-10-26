/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:21:02 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:21:27 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

// ENV_ACCESSORS
t_env_var	*get_env_var(t_list *env_vars, const char *key);
char		*get_env_var_value(t_list *env_vars, const char *key);
bool		set_env_var(t_list **env_vars, t_list *new_var_lst);
bool		unset_env_var(t_list **env_vars, char *key);

// ENV_VARS
t_list		**init_env_vars(char **envp);
int			env_key_len(char *str);
t_list		*save_env_var(char *var_str, int key_len);

// ENVP
void		save_envp(t_minishell *ms);

// ENV_PRINT
void		print_env_vars(t_list *env_vars);
void		print_env(char **envp);

#endif
