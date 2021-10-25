#include "minishell.h"

static bool	is_logical_op_instruction(t_list *curr_node);

static void				parse_tokens(t_list *curr_node, int cmd_id, int cmd_group);
static t_list			*parse_command(t_list *tokens, t_cmd *cmd, int cmd_id, int cmd_group);
static t_list			*parse_pipe(t_list *curr_node, int cmd_id);
static t_list			*parse_redir(t_list *curr_node, int cmd_id);
static t_list			*parse_logical_op(t_list *curr_node);
static void				create_redir(t_token *token, char *file_name, int redir_type, int cmd_id);

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
		{
			DEBUG(printf("parse error!\n"));
			return (minishell);
			// this needs to return the failing token!
		}
		perform_expansions(minishell->tokens);
		parse_tokens(*minishell->tokens, 0, 0);
		DEBUG(print_tokens(minishell->tokens);)
		DEBUG(print_instructions(minishell->instructions);)
		DEBUG(print_redirections(minishell->redirect);)
	}
	return (minishell);
}

t_token	*get_token(t_list *curr_node)
{
	if (curr_node)
		return ((t_token *)curr_node->content);
	return (NULL);
}

/* always assumes every function call is the first token
 * TODO ensure comparing of ( ) with their types! */
static void	parse_tokens(t_list *curr_node, int cmd_id, int cmd_group)
{
	static t_cmd 	*new_command = NULL;
	t_token			*curr_token;

	if (!curr_node)
		return ;
	curr_token = get_token(curr_node);
	if (is_logical_op_instruction(curr_node))
		parse_tokens(parse_logical_op(curr_node), cmd_id, cmd_group);
	else if (curr_token->type == OPERATOR && ft_strncmp(curr_token->str, "(", 2) == 0)
		parse_tokens(curr_node->next, cmd_id, cmd_group + 1);
	else if (curr_token->type == OPERATOR && ft_strncmp(curr_token->str, ")", 2) == 0)
		parse_tokens(curr_node->next, cmd_id, cmd_group - 1);
	else if (is_pipe_op(curr_token))
		parse_tokens(parse_pipe(curr_node, cmd_id - 1), cmd_id, cmd_group);
	else
	{
		new_command = init_empty_cmd(cmd_id, cmd_group);
		curr_node = parse_redir(curr_node, cmd_id);
		if (curr_node)
		{
			curr_token = get_token(curr_node);
			if (curr_token->type == WORD)
			{
				curr_node = parse_command(curr_node, new_command, cmd_id, cmd_group);
				curr_node = parse_redir(curr_node, cmd_id);
			}
			parse_tokens(curr_node, cmd_id + 1, cmd_group);
		}
	}
}

static bool	is_logical_op_instruction(t_list *curr_node)
{
	t_token	*token;

	if (curr_node)
	{
		token = (t_token *)(curr_node->content);
		if (token->type == OPERATOR &&
			(ft_strncmp(token->str, "&&", 3) == 0
				|| ft_strncmp(token->str, "||", 3) == 0))
			return (true);
	}
	return (false);
}

/* TODO needs more tools to ensure there is not any silly stuff like && &&, or && ||
 *		nor that any logical op is without preceding content ("&& cat filein2" should fail) */
static t_list	*parse_logical_op(t_list *curr_node)
{
	t_token			*token;
	t_instr_type	instr_type;

	instr_type = INSTR_CMD;
	if (curr_node)
	{
		token = (t_token *)(curr_node->content);
		if (token->type == OPERATOR)
		{
			if (ft_strncmp(token->str, "&&", 3) == 0)
				instr_type = INSTR_AND;
			else if (ft_strncmp(token->str, "||", 3) == 0)
				instr_type = INSTR_OR;
			if (instr_type != INSTR_CMD)
			{
				init_instruction(get_minishell(NULL), instr_type);
				return (curr_node->next);
			}
		}
		return (curr_node);
	}
	return (NULL);
}

static t_list	*parse_command(t_list *tokens, t_cmd *cmd, int cmd_id, int cmd_group)
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

static t_list	*parse_pipe(t_list *curr_node, int cmd_id)
{
	const t_token	*token = (t_token *)curr_node->content;

	create_redir((t_token *)token, NULL, REDIR_PIPE_OUT, cmd_id);
	create_redir((t_token *)token, NULL, REDIR_PIPE_IN, cmd_id + 1);
	return (curr_node->next);
}

/* the function checks for consecutive redirections */
/* argument next_node is useless now and can be removed */
static t_list	*parse_redir(t_list *curr_node, int cmd_id)
{
	t_token		*token;

	while (curr_node)
	{
		token = (t_token *)(curr_node->content);
		if (is_redir_op(token))
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

static	void create_redir(t_token *token, char *file_name, int redir_type, int cmd_id)
{
	t_redirect	*redir;

	redir = init_redirection(get_minishell(NULL), get_redir_type(token));
	redir->type = redir_type;
	if (file_name)
		redir->file_name = strdup_or_exit(file_name);
	else
		redir->file_name = NULL;
	redir->cmd_id = cmd_id;
}
