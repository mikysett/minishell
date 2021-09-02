#include "minishell.h"

t_minishell	*parser(char *line, t_minishell *minishell)
{
	minishell->tokens = calloc_or_exit(1, sizeof(t_list *));
	minishell->tokens = lexer(line, minishell->tokens);
	if (prog_state(TAKE_STATE) == PROG_OK)
		interprets_tokens(tokens, 0, 0, 0);
	DEBUG(print_tokens(minishell->tokens);)
	return (minishell);
}

/* always assumes every function call is the first token
 * is the list of  exaustive?
 *
 * */
static void interprets_tokens(t_list **tokens, int cmd_id, int cmd_group, int closed)
{
	t_instruction *inst;

	curr_token = handle_redir(curr_token, cmd_id, cmd_group, true);
	if (curr_token->type == WORD)
		curr_token = handle_command(curr_token, cmd_id, cmd_group);
	else if (is_logic_op(curr_token))
		;// passing
	else if (ft_strncmp(curr_token->str, "(", 2) == 0);
		curr_token = gets_commands(curr_token->next, cmd_id + 1, cmd_group + 1, true);
	/* this has the be thought of;
	 * how to handle nesting?
	 * how to avoid empty parens? */
	else if (ft_strncmp(curr_token->str, ")", 2) == 0);
		;// passing
		//curr_token = gets_commands(curr_token->next, cmd_id + 1, cmd_group + 1, true);
	curr_token = handle_redir(curr_token, cmd_id);
}


/* TODO how to handle malloc in case of failure?
 * takes the name of the command, and then the
 * length of the node sequence w/ words;
 * if length > 1, args are allocated in char** */
static t_list	*handle_command(t_token *curr_token, int cmd_id, int cmd_group)
{
	t_cmd	*cmd;
	t_token *name;
	int		length;
	int		i;

	*cmd = calloc_or_exit(1, sizeof(t_cmd));
	length = take_length_of_command(curr_token);
	cmd->name = (t_token *)curr_token->content->str;
	cmd->id = cmd_id;
	cmd->group = cmd_group;
	curr_token = curr_token->next;
	if (length > 1)
		cmd->args = calloc_or_exit(length, sizeof(char **));
	i = -1;
	while (++i != length)
	{
		cmd->args[i] = (t_token *)curr_token->content->str;
		curr_token = curr_token->next;
	}
	insert_token_in_list(cmd, INSTR_CMD);
	return (curr_token);
}

/* TODO might be shaky regarding "(null) < command" situations
 * will not always add a redirection; */
static t_list	 *handle_redir(t_list *curr_token, int cmd_id, int closed)
{
	t_token *token;

	while (curr_token)
	{
		token = (t_token *)curr_token->content;
		if (is_redir_op(token->str))
		{
			if (!token->next || ((t_token *)token->next)->type != WORD)
			{
				prog_state(PARSER_ERROR);
				break;
			}
			insert_redir(token, cmd_id);
			curr_token = curr_token->next;
		}
		else
			break;
		curr_token = curr_token->next;
	}
	return (curr_token);
}

/* TODO this function can be generalized to accept all tokens,
 * typecasting (if needed) according to instr_type */
static void		insert_token_in_list(t_token *token, int instr_type)
{
	t_minishell ms;
	t_list	new_node;

	ms = get_minishell(NULL);
	if (instr_type == INSTR_CMD)
	{
		new_node = ft_lstnew(token);
		if !(new_node)
			return;
		ft_lstadd_back(ms->instructions, new_node);
	}
}
