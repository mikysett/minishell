#include <stdio.h>
#include <stdbool.h>
#include <minishell.h>

void	advance_node(t_grammar_vars *grammar)
{
	grammar->prev = grammar->curr;
	grammar->curr = grammar->curr->next;
	if (grammar->curr)
		grammar->next = grammar->curr->next;
	else
		grammar->next = NULL;
}

void	initializes_grammar_vars(t_grammar_vars *grammar, t_list *curr_node)
{
	grammar->curr = curr_node;
	grammar->prev = NULL;
	if (curr_node->next)
		grammar->next = curr_node->next;
	else
		grammar->next = NULL;
}

void	validate_grammar(t_list *curr_node)
{
	t_grammar_vars	grammar;
	int	paren_count;

	paren_count = 0;
	initializes_grammar_vars(&grammar, curr_node);
	while (grammar.curr && prog_state(TAKE_STATE) == PROG_OK)
	{
		// ✅ redirections NEED a word after!
		if (get_token(grammar.curr)->op_type == OP_REDIR
			&& (!grammar.next || (get_token(grammar.next)->type != WORD)))
				prog_state(PARSER_ERROR);
				/* unexpected token is current_token */

		// logic and pipe need close parens or word on the left,
		// and cannot have logic or pipe operators on the right!
		else if (get_token(grammar.curr)->op_type == OP_LOGIC
				|| get_token(grammar.curr)->op_type == OP_PIPE)
		{
			// grammar.prev must be word or closing paren
			// 🟣 grammar.next is needed to avoid multiline commands
			if ((!grammar.prev
					|| (get_token(grammar.prev)->type != WORD
						&& ft_strncmp(get_token(grammar.prev)->str, ")", 2) != 0))
				|| !grammar.next)
				prog_state(PARSER_ERROR);
		}
		else if (ft_strncmp(get_token(grammar.curr)->str, "(", 2) == 0)
		{
			// 🟣 grammar.next is needed to avoid multiline commands
			if (!grammar.next || ft_strncmp(get_token(grammar.next)->str, ")", 2) == 0)
				prog_state(PARSER_ERROR);
			paren_count++;
		}
		else if (ft_strncmp(get_token(grammar.curr)->str, ")", 2) == 0)
			if (--paren_count < 0)
				prog_state(PARSER_ERROR);
				/* unexpected token is current_token */
		if (prog_state(TAKE_STATE) == PROG_OK)
			advance_node(&grammar);
	}
	if (paren_count > 0)
		prog_state(PARSER_ERROR);
		/* unexpected token is current_token */
}
