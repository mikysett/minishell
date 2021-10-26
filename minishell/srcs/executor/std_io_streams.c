/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_io_streams.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:07 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:18 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_std_in(t_minishell *ms)
{
	if (ms->streams.stdin_saved == false)
	{
		ms->streams.stdin_fd = ft_set_dup(STDIN_FILENO);
		ms->streams.stdin_saved = true;
	}
}

void	save_std_out(t_minishell *ms)
{
	if (ms->streams.stdout_saved == false)
	{
		ms->streams.stdout_fd = ft_set_dup(STDOUT_FILENO);
		DEBUG(fprintf(stderr, "%s> SAVE stdout, fd: %d%s\n",
			CLR_BLUE, ms->streams.stdout_fd, CLR_WHITE);)
		if (ms->streams.stdin_fd == -1)
		{
			DEBUG(fprintf(stderr, "save std err\n");)
		}
		ms->streams.stdout_saved = true;
	}
}

void	set_curr_in(t_std_io *std_io, int in_fd)
{
	DEBUG(fprintf(stderr, "%sset_curr_in: stdio, in fd: %d%s\n",
		CLR_BLUE, in_fd, CLR_WHITE);)
	if (std_io->curr_in != STDIN_FILENO)
	{
		DEBUG(fprintf(stderr, "%s<< curr_in closing %d%s\n",
			CLR_BLUE, std_io->curr_in, CLR_WHITE);)
		close(std_io->curr_in);
	}
	std_io->curr_in = in_fd;
}

void	set_curr_out(t_std_io *std_io, int out_fd)
{
	DEBUG(fprintf(stderr, "%sset_curr_out: stdio, out fd: %d%s\n",
		CLR_BLUE, out_fd, CLR_WHITE);)
	if (std_io->curr_out != STDOUT_FILENO)
	{
		DEBUG(fprintf(stderr, "%s<< curr_out closing %d%s\n",
			CLR_BLUE, std_io->curr_out, CLR_WHITE);)
		close(std_io->curr_out);
	}
	std_io->curr_out = out_fd;
}
