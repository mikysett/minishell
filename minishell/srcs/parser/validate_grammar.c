#include <minishell.h>

static void	check_grammar_conditions(t_grammar_vars *grammar);
static void	advance_node(t_grammar_vars *grammar);
static void	initializes_grammar_vars(t_grammar_vars *grammar, t_list *curr_node);

void	validate_grammar(t_list *curr_node)
{
	t_grammar_vars	grammar;

	initializes_grammar_vars(&grammar, curr_node);
	while (grammar.curr && prog_state(TAKE_STATE) == PROG_OK)
		check_grammar_conditions(&grammar);
	if (grammar.paren_count > 0)
		prog_state(PARSER_ERROR);
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

static void	check_grammar_conditions(t_grammar_vars *grammar)
{
	if (is_redir_op(get_token(grammar->curr))
		&& (!grammar->next || (get_token(grammar->next)->type != WORD)))
			prog_state(PARSER_ERROR);
	else if (is_logic_op(get_token(grammar->curr))
			|| is_pipe_op(get_token(grammar->curr)))
	{
		if ((!grammar->prev
				|| (get_token(grammar->prev)->type != WORD
					&& ft_strncmp(get_token(grammar->prev)->str, ")", 2) != 0))
			|| !grammar->next)
			prog_state(PARSER_ERROR);
	}
	else if (ft_strncmp(get_token(grammar->curr)->str, "(", 2) == 0)
	{
		if (!grammar->next || ft_strncmp(get_token(grammar->next)->str, ")", 2) == 0)
			prog_state(PARSER_ERROR);
		grammar->paren_count++;
	}
	else if (ft_strncmp(get_token(grammar->curr)->str, ")", 2) == 0)
		if (--grammar->paren_count < 0)
			prog_state(PARSER_ERROR);
	if (prog_state(TAKE_STATE) == PROG_OK)
		advance_node(grammar);
}
