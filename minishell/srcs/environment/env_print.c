/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:07 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:17 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_var	*next_var_to_print(t_list *curr_var);
static void			print_sgl_var(t_env_var *var);
static void			reset_var_is_printed(t_list *env_vars);

void	print_env_vars(t_list *env_vars)
{
	t_env_var	*var_to_print;
	const int	vars_nb = ft_lstsize(env_vars);
	int			i;

	i = 0;
	while (i < vars_nb)
	{
		var_to_print = next_var_to_print(env_vars);
		if (var_to_print)
		{
			print_sgl_var(var_to_print);
			var_to_print->is_printed = true;
			i++;
		}
	}
	reset_var_is_printed(env_vars);
}

static t_env_var	*next_var_to_print(t_list *curr_var)
{
	t_env_var	*var_to_print;
	t_env_var	*var;

	var_to_print = NULL;
	while (curr_var)
	{
		var = (t_env_var *)curr_var->content;
		if (var->is_printed == false
			&& (!var_to_print || strcmp(var->key, var_to_print->key) < 0))
			var_to_print = var;
		curr_var = curr_var->next;
	}
	return (var_to_print);
}

static void	print_sgl_var(t_env_var *var)
{
	if (!var)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var->key, STDOUT_FILENO);
	if (var->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	reset_var_is_printed(t_list *env_vars)
{
	while (env_vars)
	{
		((t_env_var *)(env_vars->content))->is_printed = false;
		env_vars = env_vars->next;
	}
}

void	print_env(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
