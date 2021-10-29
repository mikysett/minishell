/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:20 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*par_name_start(char *str);
static int	get_len_par_name(char *par_start);

void	parameter_expansion(t_list **tokens)
{
	t_list	*curr;
	char	*start_par_name;
	int		len_par_name;

	curr = *tokens;
	while (curr)
	{
		start_par_name = par_name_start(((t_token *)curr->content)->str);
		while (start_par_name)
		{
			len_par_name = get_len_par_name(start_par_name);
			expand_parameter(start_par_name, len_par_name, curr->content);
			start_par_name = par_name_start(((t_token *)curr->content)->str);
		}
		curr = curr->next;
	}
}

static char	*par_name_start(char *str)
{
	t_quote_type	prev_qt_type;
	char			next_c;

	prev_qt_type = NO_QUOTING;
	while (*str)
	{
		if (!update_quote_type(get_quote_type(*str), &prev_qt_type))
		{
			if (prev_qt_type != SINGLE_QUOTES && *str == '$')
			{
				next_c = *(str + 1);
				if (ft_isalpha(next_c) || next_c == '?' || next_c == '_')
					return (str);
			}
		}
		str++;
	}
	return (NULL);
}

static int	get_len_par_name(char *par_start)
{
	const char	*o_par_start = par_start;

	par_start++;
	if (*par_start == '?')
		return (2);
	if (!ft_isalpha(*par_start) && *par_start != '_')
		return (1);
	while (*par_start)
	{
		if (!ft_isalnum(*par_start) && *par_start != '_')
			break ;
		par_start++;
	}
	return (par_start - o_par_start);
}
