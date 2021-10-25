#include <minishell.h>

static void	advance_node(t_grammar_vars *grammar);
static void	initializes_grammar_vars(t_grammar_vars *grammar,
				t_list *curr_node);
static bool	check_token(t_grammar_vars *grammar);
static void	print_faulty_token(t_grammar_vars *grammar);

void	validate_grammar(t_list *curr_node)
{
	t_grammar_vars	grammar;

	initializes_grammar_vars(&grammar, curr_node);
	while (grammar.curr)
	{
		if (!check_token(&grammar)
			|| (!grammar.next && grammar.paren_count > 0))
		{
			print_faulty_token(&grammar);
			prog_state(PARSER_ERROR);
			break ;
		}
		advance_node(&grammar);
	}
}

static void	print_faulty_token(t_grammar_vars *grammar)
{
	char	*token;

	token = ((t_token *)grammar->curr->content)->str;
	write(1, &ERROR_MESSAGE, ft_strlen(ERROR_MESSAGE));
	write(1, token, ft_strlen(token));
	write(1, "\'\n", 2);
}

static void	advance_node(t_grammar_vars *grammar)
{
	grammar->prev = grammar->curr;
	grammar->curr = grammar->curr->next;
	if (grammar->curr)
		grammar->next = grammar->curr->next;
	else
		grammar->next = NULL;
}

static void	initializes_grammar_vars(t_grammar_vars *grammar, t_list *curr_node)
{
	grammar->paren_count = 0;
	grammar->curr = curr_node;
	grammar->prev = NULL;
	if (curr_node->next)
		grammar->next = curr_node->next;
	else
		grammar->next = NULL;
}

static bool	check_token(t_grammar_vars *grammar)
{
	if (get_token(grammar->curr)->op_type == OP_REDIR
		&& (!grammar->next || (get_token(grammar->next)->type != WORD)))
		return (false);
	else if (get_token(grammar->curr)->op_type == OP_LOGIC
		|| get_token(grammar->curr)->op_type == OP_PIPE)
	{
		if (!grammar->prev || !grammar->next
			|| (get_token(grammar->prev)->type != WORD
				&& get_token(grammar->prev)->op_type != OP_PARENS_CLOSE))
			return (false);
	}
	else if (get_token(grammar->curr)->op_type == OP_PARENS_OPEN)
		grammar->paren_count++;
	else if (get_token(grammar->curr)->op_type == OP_PARENS_CLOSE)
		if (--grammar->paren_count < 0
			|| get_token(grammar->prev)->op_type == OP_PARENS_OPEN)
			return (false);
	return (true);
}
