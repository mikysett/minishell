/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:18 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:28:06 by msessa            #+#    #+#             */
/*   Updated: 2021/10/18 14:48:26 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_exit(int fd, char *buf[1024 + 1], char **line)
{
	free(buf[fd]);
	free(*line);
	buf[fd] = 0;
	*line = 0;
	return (-1);
}

size_t	ft_partial_len(char *buf)
{
	char	*o_buf;

	o_buf = buf;
	while (*buf && *buf != '\n')
		buf++;
	return (buf - o_buf);
}

size_t	ft_strlen(const char *s)
{
	const char	*i;

	i = s;
	while (*i)
		i++;
	return (i - s);
}
