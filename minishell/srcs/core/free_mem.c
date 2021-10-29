/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:07 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:16 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_minishell *ms)
{
	if (ms)
	{
		ms->tokens = free_lst(ms->tokens, del_token);
		ms->instructions = free_lst(ms->instructions, del_instruction);
		ms->redirect = free_lst(ms->redirect, del_redirect);
		ms->env_vars = free_lst(ms->env_vars, del_env_var);
		free_env_and_paths(ms);
		free(ms->prog_name);
		free(ms);
	}
}

void	*free_lst(t_list **lst, void (*del)(void *))
{
	if (lst)
	{
		ft_lstclear(lst, del);
		free(lst);
	}
	return (NULL);
}

void	free_env_and_paths(t_minishell *ms)
{
	ft_free_str_arr(ms->envp);
	ms->envp = NULL;
	ft_free_str_arr(ms->paths);
	ms->paths = NULL;
}
