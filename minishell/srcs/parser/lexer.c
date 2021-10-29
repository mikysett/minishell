/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:19 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token			*init_token(char *token_start);
static t_token_type		get_token_type(char *token_start);
static t_operator_type	get_operator_type(t_token *token);
static void				save_token(t_list **tokens, t_token *curr_token);

t_list	**lexer(char *line, t_list **tokens)
{
	char			*token_start;
	char			*token_end;
	t_token			*curr_token;

	token_start = next_non_space(line);
	while (*token_start)
	{
		curr_token = init_token(token_start);
		token_end = get_token_end(token_start, curr_token);
		curr_token->str = ft_strndup(token_start, token_end - token_start);
		curr_token->op_type = get_operator_type(curr_token);
		if (!curr_token->str)
			ft_error_exit(MEMORY_FAIL);
		save_token(tokens, curr_token);
		token_start = next_non_space(token_end);
	}
	return (tokens);
}

static t_token	*init_token(char *token_start)
{
	t_token	*curr_token;

	curr_token = calloc_or_exit(1, sizeof(t_token));
	curr_token->type = get_token_type(token_start);
	return (curr_token);
}

static t_token_type	get_token_type(char *token_start)
{
	if (is_operator(token_start))
		return (OPERATOR);
	else
		return (WORD);
}

static t_operator_type	get_operator_type(t_token *token)
{
	if (token->type != OPERATOR)
		return (OP_NONE);
	if (ft_strncmp(token->str, "(", 2) == 0)
		return (OP_PARENS_OPEN);
	else if (ft_strncmp(token->str, ")", 2) == 0)
		return (OP_PARENS_CLOSE);
	else if (ft_strncmp(token->str, "|", 2) == 0)
		return (OP_PIPE);
	else if (ft_strncmp(token->str, "&&", 3) == 0
		|| ft_strncmp(token->str, "||", 3) == 0)
		return (OP_LOGIC);
	else
		return (OP_REDIR);
}

static void	save_token(t_list **tokens, t_token *curr_token)
{
	t_list	*new_lst_el;

	new_lst_el = ft_lstnew(curr_token);
	if (!new_lst_el)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(tokens, new_lst_el);
}
