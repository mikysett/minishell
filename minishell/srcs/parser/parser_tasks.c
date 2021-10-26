/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tasks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:20 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_command_and_redir(t_list *curr_node, int cmd_id, int cmd_group)
{
	static t_cmd	*new_command = NULL;
	t_token			*curr_token;

	new_command = init_empty_cmd(cmd_id, cmd_group);
	curr_node = parse_redir(curr_node, cmd_id);
	if (curr_node)
	{
		curr_token = get_token(curr_node);
		if (curr_token->type == WORD)
		{
			curr_node = parse_command(curr_node, new_command,
					cmd_id, cmd_group);
			curr_node = parse_redir(curr_node, cmd_id);
		}
		parse_tokens(curr_node, cmd_id + 1, cmd_group);
	}
}

t_list	*parse_logical_op(t_list *curr_node)
{
	t_token			*token;
	t_instr_type	instr_type;

	if (curr_node)
	{
		token = (t_token *)(curr_node->content);
		if (token->op_type == OP_LOGIC)
		{
			if (ft_strncmp(token->str, "&&", 3) == 0)
				instr_type = INSTR_AND;
			else
				instr_type = INSTR_OR;
			init_instruction(get_minishell(NULL), instr_type);
			return (curr_node->next);
		}
		return (curr_node);
	}
	return (NULL);
}

t_list	*parse_command(t_list *tokens, t_cmd *cmd, int cmd_id, int cmd_group)
{
	int		length;
	int		i;

	length = take_length_of_command(tokens) + 1;
	cmd->id = cmd_id;
	cmd->group = cmd_group;
	cmd->name = strdup_or_exit(((t_token *)tokens->content)->str);
	cmd->is_empty_cmd = false;
	tokens = tokens->next;
	cmd->args = calloc_or_exit(length, sizeof(char **));
	i = 0;
	cmd->args[i++] = strdup_or_exit(cmd->name);
	while (i != length - 1
		&& (((t_token *)tokens->content)->type == WORD))
	{
		cmd->args[i++] = strdup_or_exit(((t_token *)tokens->content)->str);
		tokens = tokens->next;
	}
	return (tokens);
}

t_list	*parse_pipe(t_list *curr_node, int cmd_id)
{
	const t_token	*token = (t_token *)curr_node->content;

	create_redir((t_token *)token, NULL, REDIR_PIPE_OUT, cmd_id);
	create_redir((t_token *)token, NULL, REDIR_PIPE_IN, cmd_id + 1);
	return (curr_node->next);
}

/* the function checks for consecutive redirections */
/* argument next_node is useless now and can be removed */
t_list	*parse_redir(t_list *curr_node, int cmd_id)
{
	t_token		*token;

	while (curr_node)
	{
		token = (t_token *)(curr_node->content);
		if (token->op_type == OP_REDIR)
		{
			create_redir(token, ((t_token *)curr_node->next->content)->str,
				get_redir_type(token), cmd_id);
			curr_node = curr_node->next->next;
		}
		else
			break ;
	}
	return (curr_node);
}
