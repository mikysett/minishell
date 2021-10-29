/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:07 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 15:05:32 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_number(char *str_nb);

int	exit_builtin(char **argv)
{
	const int	args_nb = args_count(argv);
	t_minishell	*ms;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ms = get_minishell(NULL);
	if (args_nb > 1)
	{
		if (!is_number(argv[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			ms->exit_code = EXIT_EXIT_ERROR;
		}
		else
		{
			ms->exit_code = ft_atoi(argv[1]) % 256;
			if (args_nb > 2)
			{
				ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
		}
	}
	free_minishell((t_minishell *)ms);
	exit(ms->exit_code);
}

static bool	is_number(char *str_nb)
{
	if (!str_nb || !*str_nb)
		return (false);
	while (*str_nb)
	{
		if (!ft_isdigit(*str_nb))
			return (false);
		str_nb++;
	}
	return (true);
}
