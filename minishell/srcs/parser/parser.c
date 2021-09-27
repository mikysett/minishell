#include "minishell.h"

static t_list			*interprets_tokens(t_list *curr_node, int cmd_id, int cmd_group);
static t_list			*handle_command(t_list *tokens, int cmd_id, int cmd_group);
static void				insert_token_in_list(void *instruction, int instr_type);
static t_list			*handle_redir(t_list *curr_node, t_list *next_node, int cmd_id);
static t_list			*handle_logical_op(t_list *curr_node, int cmd_id);
static void				create_redir(t_token *token, char *file_name, int redir_type, int cmd_id);

/* TODO could there be a while loop over here?
 * loop while prog_state is ok && there are still tokens left?
 * and how to ensure proper comman id when it goes into parens? */
t_minishell	*parser(char *line, t_minishell *minishell)
{
	t_list	*curr_node;
	int		cmd_id;

	minishell->tokens = calloc_or_exit(1, sizeof(t_list *));
	minishell->instructions = calloc_or_exit(1, sizeof(t_list *));
	minishell->redirect = calloc_or_exit(1, sizeof(t_list *));
	minishell->tokens = lexer(line, minishell->tokens);
	if (!*minishell->tokens)
		return (minishell);
	curr_node = *minishell->tokens;
	cmd_id = 0;
	if (prog_state(TAKE_STATE) == PROG_OK)
	{
		perform_expansions(minishell->tokens);
		while (curr_node)
			curr_node = interprets_tokens(curr_node, cmd_id++, 0);
		DEBUG(print_tokens(minishell->tokens);)
		DEBUG(print_instructions(minishell->instructions);)
		DEBUG(print_redirections(minishell->redirect);)
	}
	return (minishell);
}

/* always assumes every function call is the first token
 * TODO ensure comparing of ( ) with their types!
 * Legal case: < test-1 | wc !! */
static t_list *interprets_tokens(t_list *curr_node, int cmd_id, int cmd_group)
{
	t_token			*curr_token;

	curr_token = (t_token *)curr_node->content;
	curr_node = handle_redir(curr_node, curr_node->next, cmd_id);
	if (prog_state(TAKE_STATE) != PROG_OK)
		return (NULL);
	if (((t_token *)curr_node->content)->type == WORD)
		curr_node = handle_command(curr_node, cmd_id, cmd_group);
	else if (is_logic_op(curr_token))
		curr_node = handle_logical_op(curr_node, cmd_id);
	else if (ft_strncmp(curr_token->str, "(", 2) == 0)
		curr_node = interprets_tokens(curr_node->next, cmd_id + 1, cmd_group + 1);
	/* this has the be thought of;
		 * how to handle nesting?
		 * how to avoid empty parens? */
	else if (ft_strncmp(curr_token->str, ")", 2) == 0)
		;// passing
	if (curr_node)
		curr_node = handle_redir(curr_node, curr_node->next, cmd_id);
	if (prog_state(TAKE_STATE) != PROG_OK)
		return (NULL);
	return (curr_node);
}

/* this seems done, but needs more tools to ensure there is not any silly stuff like && &&, or && || */
static t_list	*handle_logical_op(t_list *curr_node, int cmd_id)
{
	t_token		*token;
	t_cmd 		*logical_op;

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
	length = take_length_of_command(tokens) + 1;
	cmd->id = cmd_id;
	cmd->group = cmd_group;
	cmd->name = strdup_or_exit(((t_token *)tokens->content)->str);
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

/* the function checks for consecutive redirections */

/* after a pipe, it is possible to have both a command or a redir.
*
* < filein2 | cat				👈 legal
* < |							❌ not good
* cat filein2 | > filein3       👈 super legal as well
* cat filein2 | >				❌ not good
* < filein2 | > filein3         👈 super legal as well
*/

static t_list	*handle_redir(t_list *curr_node, t_list *next_node, int cmd_id)
{
	t_token		*token;

	if (curr_node)
	{
		token = (t_token *)(curr_node->content);
		if (is_redir_op(token))
		{
			/* the conditions below should be a proper function.
			 * it should test whether the particular situation is legal,
			 * which will then allow for unrestricted running of if else clauses.
			 * there are more cases to test! ⚠️  */
			if (!next_node || ((t_token *)next_node->content)->type != WORD)
			{
				prog_state(PARSER_ERROR);
				return (NULL);
			}
			if (ft_strncmp(token->str, "|", 2) == 0)
			{
				create_redir(token, NULL, REDIR_PIPE_OUT, cmd_id);
				create_redir(token, NULL, REDIR_PIPE_IN, cmd_id + 1);
				return (handle_redir(curr_node->next, next_node->next, cmd_id + 1));
			}
				create_redir(token, ((t_token *)next_node->content)->str,
					get_redir_type(token), cmd_id);
			if (next_node->next && is_redir_op((t_token *)next_node->content))
				return (handle_redir(next_node->next, curr_node->next, cmd_id));
			return (next_node->next);
		}
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
