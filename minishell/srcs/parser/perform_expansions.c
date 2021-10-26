/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:20 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perform_expansions(t_list **tokens)
{
	parameter_expansion(tokens);
	filename_expansion(tokens);
	quote_removal(*tokens);
}
