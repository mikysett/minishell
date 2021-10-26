/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:07 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:15 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_print_newline(int argc, char **argv);

int	echo_builtin(char **argv)
{
	const int	args_nb = args_count(argv);
	const bool	print_newline = get_print_newline(args_nb, argv);
	bool		something_printed;
	int			i;

	if (print_newline == false)
		i = 1;
	else
		i = 0;
	something_printed = false;
	while (++i < args_nb)
	{
		if (something_printed)
			write(STDOUT_FILENO, " ", 1);
		else
			something_printed = true;
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
	}
	if (print_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

static bool	get_print_newline(int argc, char **argv)
{
	if (argc >= 2 && !ft_strncmp("-n", argv[1], 3))
		return (false);
	return (true);
}
