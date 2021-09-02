#include "minishell.h"

t_minishell	*parser(char *line, t_minishell *minishell)
{
	minishell->tokens = calloc_or_exit(1, sizeof(t_list *));
	minishell->tokens = lexer(line, minishell->tokens);
	if (prog_state(TAKE_STATE) == PROG_OK)
	{
		// TODO proper parser
	}
	DEBUG(print_tokens(minishell->tokens);)
	return (minishell);
}

/* returns a t_list **of commands.
 * calls gets_commands once, and passes cmd_list by ref */
static t_list **interprets_tokens(t_list **tokens)
{
	t_list **cmd_list;
	cmd_list = calloc_or_exit(1, sizeof(t_list **));
	gets_commands(tokens, cmd_list, 0, 1);
}

/* returns a t_list of commands.
 * always assumes every function call is the first token */
gets_commands(t_list **tokens, int cmd_id, int cmd_group, int closed)
{
	t_instruction *inst;

	curr_token = handle_redir(curr_token, cmd_id, cmd_group, true);
	if (is_logic_op(curr_token))
		// passing;
	else if (curr_token->type == WORD)
		curr_token = handle_cmd(curr_token, cmd_id, cmd_group);
	else if (ft_strncmp(curr_token->str, "(", 2) == 0);
		curr_token = gets_commands(curr_token->next, cmd_id + 1, true);
	curr_token = handle_redir(curr_token, cmd_id);
}


/* TODO how to handle malloc in case of failure?
 * takes the name of the command, and then the
 * length of the node sequence w/ words;
 * if length > 1, args should be allocated in char** */
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

/* will not always add a redirection; */
static t_list	 *handle_redir(t_list *curr_token, int cmd_id)
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


static void		insert_token_in_list(t_token *token, int instr_type)
{
	t_minishell ms;

	ms = get_minishell(NULL);
	if (instr_type == INSTR_CMD)
	{

	}
}

/* gets a node object, and retrieves the amount of words
 * in that command */
static	int		take_length_of_command(t_list *node)
{
	int i;
	t_token *token;

	i = 0;
	if (!node)
		return (0);
	while (node)
	{
		token = (t_token *)node->content;
		if (token->type == WORD)
			i++;
		else
			break;
		node = node->next;
	}
	return (i);
}

