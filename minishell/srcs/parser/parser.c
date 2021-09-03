#include "minishell.h"

static t_list			*interprets_tokens(t_list **tokens, int cmd_id, int cmd_group, int closed);
static t_list			*handle_command(t_list **tokens, int cmd_id, int cmd_group);
static t_list			*look_for_redir(t_list **tokens, int cmd_id, int closed);
static void				insert_token_in_list(void *instruction, int instr_type);
static t_redirect		*handle_redir(t_list *curr_token, int cmd_id, int before);

t_minishell	*parser(char *line, t_minishell *minishell)
{
	minishell->tokens = calloc_or_exit(1, sizeof(t_list *));
	minishell->instructions = calloc_or_exit(1, sizeof(t_list *));
	minishell->tokens = lexer(line, minishell->tokens);
	if (prog_state(TAKE_STATE) == PROG_OK)
		interprets_tokens(minishell->tokens, 0, 0, 0);
	DEBUG(print_tokens(minishell->tokens);)
	return (minishell);
}

/* always assumes every function call is the first token
 * is the list of  exaustive?
 *
 * */
static t_list *interprets_tokens(t_list *curr, int cmd_id, int cmd_group, int closed)
{
	t_token *curr_token;
	const t_list	*start_pos = curr;
	curr_token = (t_token *)curr->content;

	curr = look_for_redir(curr_token, cmd_id);
	curr_token = (t_token *)curr->content;
	if (prog_state(TAKE_STATE) != PROG_OK)
		return (NULL);
	// Legal case: < test-1 | wc !!
	if (curr != start_pos && curr_token->type == OPERATOR)
	{
		prog_state(PARSER_ERROR);
		return (NULL);
	}

	if (curr_token->type == WORD)
		curr_token = handle_command(curr, cmd_id, cmd_group);
	else if (is_logic_op(curr_token->str))
		;// passing
	else if (ft_strncmp(curr_token->str, "(", 2) == 0)
		curr_token = interprets_tokens(&(*curr)->next, cmd_id + 1, cmd_group + 1, true);
	/* this has the be thought of;
		 * how to handle nesting?
		 * how to avoid empty parens? */
	else if (ft_strncmp(curr_token->str, ")", 2) == 0)
		;// passing
		//curr_token = gets_commands(curr_token->next, cmd_id + 1, cmd_group + 1, true);
	curr = look_for_redir(curr_token, cmd_id);
	curr_token = (t_token *)curr->content;
	if (prog_state(TAKE_STATE) != PROG_OK)
		return (NULL);
	// check if pipe
}


/* TODO how to handle malloc in case of failure?
 * takes the name of the command, and then the
 * length of the node sequence w/ words;
 * if length > 1, args are allocated in char** */

t_cmd	*init_instruction(t_minishell *ms)
{
	t_instruction	*instr;
	t_list			*new_instr;

	instr = calloc_or_exit(1, sizeof(t_instruction));
	new_instr = ft_lstnew(instr);
	if (!new_instr)
		ft_error_exit(MEMORY_FAIL);
	ft_lstadd_back(ms->instructions, new_instr);
	instr->cmd = calloc_or_exit(1, sizeof(t_cmd));
}

static t_list	*handle_command(t_list **tokens, int cmd_id, int cmd_group)
{
	t_cmd	*cmd;
	int		length;
	int		i;

	init_instruction(get_minishell(NULL));

	cmd = calloc_or_exit(1, sizeof(t_cmd));
	length = take_length_of_command(*tokens);
	cmd->id = cmd_id;
	cmd->group = cmd_group;
	cmd->name = ((t_token *)(*tokens)->content)->str;
	*tokens = (*tokens)->next;
	if (length > 1)
		cmd->args = calloc_or_exit(length, sizeof(char **));
	i = -1;
	while (++i != length - 1)
	{
		cmd->args[i] = ((t_token *)(*tokens)->content)->str;
		*tokens = (*tokens)->next;
	}
	insert_token_in_list(cmd, INSTR_CMD);
	return (*tokens);
}

/* TODO might be shaky regarding "(null) < command" situations
 * the function checks for consecutive redirections, whenever appliable? */
static t_list	 *look_for_redir(t_list *curr_token, int cmd_id, int before)
{
	t_token		*token;
	t_redirect	*redir;

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
			handle_redir(curr_token, cmd_id, before);
			curr_token = curr_token->next;
		}
		else
			break;
		curr_token = curr_token->next;
	}
	return (curr_token);
}

static t_redirect	 *handle_redir(t_list *curr_token, int cmd_id, int before)
{
	t_redirect *redir;

	if (ft_strncmp(token->str == "|", 1) == 0)
	{
		/* there was nothing preceding pipe! */
		if (before)
		{
			prog_state(PARSER_ERROR);
			return (NULL);
		}
		*redir = calloc_or_exit(1, sizeof(t_redirect));
		/* every pipe originates two redir instructions, in and out */
	}
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
