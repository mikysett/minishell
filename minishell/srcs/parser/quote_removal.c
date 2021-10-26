/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:21 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes_in_token_str(char *token_str);
static char	*update_token_str(char *old_str);

void	quote_removal(t_list *curr_token_lst)
{
	t_token	*curr_token;

	while (curr_token_lst)
	{
		curr_token = (t_token *)curr_token_lst->content;
		curr_token->str = remove_quotes_in_token_str(curr_token->str);
		curr_token_lst = curr_token_lst->next;
	}
}

static char	*remove_quotes_in_token_str(char *token_str)
{
	int				i;
	t_quote_type	prev_qt_type;
	int				offset;

	prev_qt_type = NO_QUOTING;
	offset = 0;
	i = 0;
	while (token_str[i])
	{
		if (update_quote_type(get_quote_type(token_str[i]), &prev_qt_type))
			offset++;
		else
			token_str[i - offset] = token_str[i];
		i++;
	}
	if (offset != 0)
	{
		token_str[i - offset] = '\0';
		return (update_token_str(token_str));
	}
	return (token_str);
}

static char	*update_token_str(char *old_str)
{
	char	*new_str;

	new_str = strdup_or_exit(old_str);
	free(old_str);
	return (new_str);
}
