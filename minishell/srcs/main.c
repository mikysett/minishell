/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:19 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	int			exit_code;

	minishell = init_minishell(envp);
	if (argc == 1)
		interactive_mode(minishell);
	else
		non_interactive_mode(minishell, argv[1]);
	exit_code = minishell->exit_code;
	free_minishell(minishell);
	return (exit_code);
}
