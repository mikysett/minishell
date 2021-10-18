#include "minishell.h"

static t_list			*parse_tokens(t_list *curr_node, int cmd_id, int cmd_group);
static t_list			*parse_command(t_list *tokens, int cmd_id, int cmd_group);
static t_list			*parse_parens(t_list *curr_node, int cmd_id, int cmd_group);
static t_list			*parse_redir(t_list *curr_node, t_list *next_node, int cmd_id);
static t_list			*parse_logical_op(t_list *curr_node, int cmd_id);
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
		perform_expansions(minishell->tokens);
		parse_tokens(*minishell->tokens, 0, 0);
		DEBUG(print_tokens(minishell->tokens);)
		DEBUG(print_instructions(minishell->instructions);)
		DEBUG(print_redirections(minishell->redirect);)
		if (prog_state(TAKE_STATE) != PROG_OK)
			printf("parse error!\n");
	}
	return (minishell);
}

t_token	*get_token(t_list *curr_node)
{
	return ((t_token *)curr_node->content);
}

/* always assumes every function call is the first token
 * TODO ensure comparing of ( ) with their types! */
static t_list *parse_tokens(t_list *curr_node, int cmd_id, int cmd_group)
{
	if (!curr_node)
		return (NULL);
	curr_node = parse_redir(curr_node, curr_node->next, cmd_id);
	if (prog_state(TAKE_STATE) != PROG_OK || !curr_node)
		return (NULL);
	if (get_token(curr_node)->type == WORD)
		curr_node = parse_command(curr_node, cmd_id, cmd_group);
	else if (is_logic_op(get_token(curr_node)))
		curr_node = parse_logical_op(curr_node, cmd_id);
	else if (ft_strncmp(get_token(curr_node)->str, "(", 2) == 0)
	{
		curr_node = parse_tokens(curr_node->next, cmd_id, ++cmd_group);
		cmd_id = (ft_lstsize(*get_minishell(NULL)->instructions) - 1);
	}
	else if (ft_strncmp(get_token(curr_node)->str, ")", 2) == 0)
		return (parse_tokens(curr_node->next, cmd_id, cmd_group - 1));
	if (curr_node)
		curr_node = parse_redir(curr_node, curr_node->next, cmd_id);
	if (prog_state(TAKE_STATE) != PROG_OK || !curr_node)
		return (NULL);
	return (parse_tokens(curr_node, cmd_id + 1, cmd_group));
}

static t_list *parse_parens(t_list *curr_node, int cmd_id, int cmd_group)
{
	t_token			*next_token;

	if (curr_node->next)
	{
		next_token = (t_token *)curr_node->next;
		if (ft_strncmp(next_token->str, "|", 2) == 0
			|| ft_strncmp(next_token->str, ")", 2) == 0)
		{
			prog_state(PARSER_ERROR);
			return (NULL);
		}
	}
	else
	{
		prog_state(PARSER_ERROR);
		return (NULL);
	}
	return (parse_tokens(curr_node->next, cmd_id + 1, 0));
}

/* TODO needs more tools to ensure there is not any silly stuff like && &&, or && ||
 *		nor that any logical op is without preceding content ("&& cat filein2" should fail) */
static t_list	*parse_logical_op(t_list *curr_node, int cmd_id)
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

static t_list	*parse_command(t_list *tokens, int cmd_id, int cmd_group)
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
static t_list	*parse_redir(t_list *curr_node, t_list *next_node, int cmd_id)
{
	t_token		*token;

	if (curr_node)
	{
		token = (t_token *)(curr_node->content);
		if (is_redir_op(token))
		{
			if (!next_node
				|| (((t_token *)next_node->content)->type != WORD
					&& ft_strncmp(token->str, "|", 2) != 0))
			{
				prog_state(PARSER_ERROR);
				return (NULL);
			}
			create_redir(token, ((t_token *)next_node->content)->str,
				get_redir_type(token), cmd_id);
			if (next_node->next && is_redir_op((t_token *)next_node->content))
				return (parse_redir(next_node->next, curr_node->next, cmd_id));
			return (next_node->next);
		}
		if (is_pipe_op(token))
		{
			create_redir(token, NULL, REDIR_PIPE_OUT, cmd_id);
			create_redir(token, NULL, REDIR_PIPE_IN, cmd_id + 1);
			return (parse_redir(curr_node->next, next_node->next, cmd_id + 1));
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
