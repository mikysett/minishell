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
	gets_commands(tokens, cmd_list, 1);
}

static int		is_redir_op(char *str)
{
	return (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0 
			|| ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0 
			|| ft_strncmp(str, "|", 1) == 0)
}

static int		is_logic_op(char *str)
{
	return (ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, "&&", 2) == 0)
}

static int		is_paren_op(char *str)
{
	return (ft_strncmp(str, "(", 1) == 0 || ft_strncmp(str, ")", 1) == 0)
}

static void		insert_redir(t_token *token, int cmd_id)
{
	t_minishell ms;

	ms = get_minishell(NULL);
}

static void		insert_cmd(t_token *token, int cmd_id)
{
	t_minishell ms;

	ms = get_minishell(NULL);
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
static void gets_command(t_list **tokens, t_list **cmd_list, int closed)
{
	t_instruction *inst;

	// how to account for cmd_id? 
	curr_token = handle_redir(curr_token, cmd_id);
	if (is_logic_op(curr_token))
		;
	else if (curr_token->type == WORD)
		curr_token = set_cmd(curr_token, cmd_id);
	else if (ft_strncmp(curr_token->str, "(", 2) == 0);
		curr_token = gets_commands(curr_token->next, true);
	curr_token = handle_redir(curr_token, cmd_id);
}
