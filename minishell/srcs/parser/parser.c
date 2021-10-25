#include "minishell.h"

t_minishell	*parser(char *line, t_minishell *minishell)
{
	minishell->tokens = calloc_or_exit(1, sizeof(t_list *));
	minishell->instructions = calloc_or_exit(1, sizeof(t_list *));
	minishell->redirect = calloc_or_exit(1, sizeof(t_list *));
	minishell->tokens = lexer(line, minishell->tokens);
	if (*minishell->tokens && prog_state(TAKE_STATE) == PROG_OK)
	{
		validate_grammar(*minishell->tokens);
		if (prog_state(TAKE_STATE) != PROG_OK)
			return (minishell);
		perform_expansions(minishell->tokens);
		parse_tokens(*minishell->tokens, 0, 0);
	}
	return (minishell);
}

void	parse_tokens(t_list *curr_node, int cmd_id, int cmd_group)
{
	t_token			*curr_token;

	if (!curr_node)
		return ;
	curr_token = get_token(curr_node);
	if (curr_token->op_type == OP_LOGIC)
		parse_tokens(parse_logical_op(curr_node), cmd_id, cmd_group);
	else if (curr_token->op_type == OP_PARENS_OPEN)
		parse_tokens(curr_node->next, cmd_id, cmd_group + 1);
	else if (curr_token->op_type == OP_PARENS_CLOSE)
		parse_tokens(curr_node->next, cmd_id, cmd_group - 1);
	else if (curr_token->op_type == OP_PIPE)
		parse_tokens(parse_pipe(curr_node, cmd_id - 1), cmd_id, cmd_group);
	else
		create_command_and_redir(curr_node, cmd_id, cmd_group);
}
