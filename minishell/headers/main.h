/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:16:47 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:16:48 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// INTERACTIVE_MODE
void	interactive_mode(t_minishell *ms);

// NON_INTERACTIVE_MODE
void	non_interactive_mode(t_minishell *ms, char *bash_file);
void	process_line(t_minishell *ms, char *line);

#endif
