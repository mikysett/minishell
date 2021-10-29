/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:07 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:15 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(char **argv)
{
	char	*absolute_path;

	absolute_path = getcwd(NULL, 0);
	if (!absolute_path)
	{
		ft_putstr_fd(get_minishell(NULL)->prog_name, STDERR_FILENO);
		perror(argv[0]);
		return (EXIT_FAILURE);
	}
	write(STDOUT_FILENO, absolute_path, ft_strlen(absolute_path));
	write(STDOUT_FILENO, "\n", 1);
	free(absolute_path);
	return (EXIT_SUCCESS);
}
