/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:07 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:17 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*next_group_pos(t_list *curr);
static int		exec_instr(t_cmd *cmd, t_std_io *std_io, t_list **redirect);
static int		exec_cmd(t_cmd *cmd);

t_list	*executor(t_minishell *ms, t_list *curr)
{
	t_instruction	*instr;

	if (!curr)
		return (NULL);
	instr = (t_instruction *)curr->content;
	if (instr->type == INSTR_GRP_START || instr->type == INSTR_GRP_END)
		return (executor(ms, curr->next));
	else if (instr->type == INSTR_OR)
	{
		if (ms->exit_code == EXIT_SUCCESS)
			return (executor(ms, next_group_pos(curr)));
		else
			return (executor(ms, curr->next));
	}
	else if (instr->type == INSTR_AND)
	{
		if (ms->exit_code != EXIT_SUCCESS)
			return (executor(ms, next_group_pos(curr)));
		else
			return (executor(ms, curr->next));
	}
	else
	{
		while (curr && instr->type == INSTR_CMD)
		{
			get_minishell(NULL)->exit_code = exec_instr(instr->cmd,
				&ms->streams, ms->redirect);
			curr = curr->next;
			if (curr)
				instr = (t_instruction *)curr->content;
		}
		return (executor(ms, curr));
	}
}

static t_list	*next_group_pos(t_list *curr)
{
	while (curr && ((t_instruction *)curr->content)->type != INSTR_GRP_END)
		curr = curr->next;
	return (curr);
}

static int	exec_instr(t_cmd *cmd, t_std_io *std_io, t_list **redirect)
{
	if (setup_redirect(std_io, redirect, cmd->id))
		return (exec_cmd(cmd));
	else
		return (EXIT_FAILURE);
}

static int	exec_cmd(t_cmd *cmd)
{
	if (cmd->is_empty_cmd)
		return (EXIT_SUCCESS);
	else if (!ft_strncmp("echo", cmd->name, 5))
		return (echo_builtin(cmd->args));
	else if (!ft_strncmp("cd", cmd->name, 3))
		return (cd_builtin(cmd->args));
	else if (!ft_strncmp("pwd", cmd->name, 4))
		return (pwd_builtin(cmd->args));
	else if (!ft_strncmp("export", cmd->name, 7))
		return (export_builtin(cmd->args));
	else if (!ft_strncmp("unset", cmd->name, 6))
		return (unset_builtin(cmd->args));
	else if (!ft_strncmp("env", cmd->name, 4))
		return (env_builtin(cmd->args));
	else if (!ft_strncmp("exit", cmd->name, 5))
		return (exit_builtin(cmd->args));
	else
		return (exec_std_cmd(cmd));
}
