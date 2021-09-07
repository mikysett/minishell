#include "minishell.h"

static t_list			*interprets_tokens(t_list *curr_node, int cmd_id, int cmd_group);
static t_list			*handle_command(t_list *tokens, int cmd_id, int cmd_group);
static void				insert_token_in_list(void *instruction, int instr_type);
static t_list			*handle_redir(t_list *curr_node, t_list *next_node, int cmd_id);
static t_list			*handle_logical_op(t_list *curr_node, int cmd_id);

/* TODO could there be a while loop over here?
 * loop while prog_state is ok && there are still tokens left?
 * and how to ensure proper comman id when it goes into parens? */
t_minishell	*parser(char *line, t_minishell *minishell)
{
	minishell->tokens = calloc_or_exit(1, sizeof(t_list *));
	minishell->instructions = calloc_or_exit(1, sizeof(t_list *));
	minishell->tokens = lexer(line, minishell->tokens);
	if (prog_state(TAKE_STATE) == PROG_OK)
		interprets_tokens(*minishell->tokens, 0, 0);
	DEBUG(print_tokens(minishell->tokens);)
	return (minishell);
}

/* always assumes every function call is the first token
 * TODO ensure comparing of ( ) with their types!
 * Legal case: < test-1 | wc !! */
static t_list *interprets_tokens(t_list *curr_node, int cmd_id, int cmd_group)
{
	t_token			*curr_token;

	curr_node = handle_redir(curr_node, curr_node->next, cmd_id);
	if (prog_state(TAKE_STATE) != PROG_OK)
		return (NULL);
	if (curr_token->type == WORD)
		curr_node = handle_command(curr_node, cmd_id, cmd_group);
	/* fix is_logic_op to check type and str */
	else if (is_logic_op(curr_token))
		curr_node = handle_logical_op(curr_node, cmd_id);
	else if (ft_strncmp(curr_token->str, "(", 2) == 0)
		curr_node = interprets_tokens(curr_node->next, cmd_id + 1, cmd_group + 1);
	/* this has the be thought of;
		 * how to handle nesting?
		 * how to avoid empty parens? */
	else if (ft_strncmp(curr_token->str, ")", 2) == 0)
		;// passing
	curr_node = handle_redir(curr_node, curr_node->next, cmd_id);
	if (prog_state(TAKE_STATE) != PROG_OK)
		return (NULL);
}

/* this seems done, but needs more tools to ensure there is not any silly stuff like && &&, or && || */
static t_list	*handle_logical_op(t_list *curr_node, int cmd_id)
{
	t_token		*token;
	t_instruction logical_op;

	(void)cmd_id;
	token = (t_token *)(curr_node->content);
	if (ft_strncmp(token->str, "&&", 3) == 0)
		logical_op = init_instruction(get_minishell(NULL), INSTR_AND);
	else if (ft_strncmp(token->str, "||", 3) == 0)
		logical_op = init_instruction(get_minishell(NULL), INSTR_OR);
	else
	{
		prog_state(PARSER_ERROR);
		return (NULL);
	}
	return (curr_node->next);
}

static t_list	*handle_command(t_list *tokens, int cmd_id, int cmd_group)
{
	t_cmd	*cmd;
	int		length;
	int		i;

	cmd = init_instruction(get_minishell(NULL), INSTR_CMD);
	length = take_length_of_command(tokens);
	cmd->id = cmd_id;
	cmd->group = cmd_group;
	cmd->name = ((t_token *)tokens->content)->str;
	tokens = tokens->next;
	if (length > 1)
		cmd->args = calloc_or_exit(length, sizeof(char **));
	i = -1;
	while (++i != length - 1)
	{
		cmd->args[i] = ((t_token *)tokens->content)->str;
		tokens = tokens->next;
	}
	return (tokens);
}

/* the function checks for consecutive redirections */
static t_list	*handle_redir(t_list *curr_node, t_list *next_node, int cmd_id)
{
	t_token		*token;
	t_redirect	*redir;

	token = (t_token *)(curr_node->content);
	if (is_redir_op(token->str))
	{
		if (!(*next_token))
		{
			prog_state(PARSER_ERROR);
			return (NULL);
		}
		/* TODO this should have its own function */
		redir = init_instruction(get_minishell(NULL), 4);
		redir->type = get_redir_type(token);
		redir->file_name = ft_strdup(((t_token *)next_node->content)->str);
		redir->cmd_id = cmd_id;
		return (handle_redir(next_node->next, curr_node->next, cmd_id));
	}
	return (curr_node);
}

/* TODO this function can be generalized to accept all tokens,
 * typecasting (if needed) according to instr_type */
static void		insert_token_in_list(void *instruction, int instr_type)
{
	t_minishell *ms;
	t_list	*new_node;

	ms = get_minishell(NULL);
	if (instr_type == INSTR_CMD)
	{
		new_node = ft_lstnew(instruction);
		if (!(new_node))
			return;
		ft_lstadd_back(ms->instructions, new_node);
	}
}
