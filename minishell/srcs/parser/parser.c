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

/* returns a t_list of commands.
 * always assumes every function call is the first token */
gets_commands(t_list **tokens, int cmd_id, int closed)
{
	t_instruction *inst;

	curr_token = handle_redir(curr_token, cmd_id);
	if (is_logic_op(curr_token))
		curr_token = in;
	else if (curr_token->type == WORD)
		curr_token = set_cmd(curr_token, cmd_id);
	else if (ft_strncmp(curr_token->str, "(", 2) == 0);
		curr_token = gets_commands(curr_token->next, cmd_id + 1, true);
	curr_token = handle_redir(curr_token, cmd_id);
}

static void		insert_instruction(t_token *token, int cmd_id, int instr_type)
{
	t_minishell ms;

	ms = get_minishell(NULL);
	if (instr_type == INSTR_CMD)
	{

	}
}

