#include <stdio.h>
#include <stdbool.h>

typedef struct s_grammar_vars {
	t_list  *curr;
	t_list	*prev;
	t_list	*next;
	int		paren_count;
}				t_grammar_vars;

void	advance_node(t_grammar_vars *grammar)
{
	grammar->prev = grammar->curr;
	grammar->curr = grammar->curr->next;

}

t_token	*get_token(t_list *curr_node)
{
	return ((t_token *)curr_node->content);
}

void	initializes_grammar_vars(t_grammar_vars *grammar, t_list *curr_node)
{
	grammar.word = true;
	grammar.pipe = false;
	grammar.redir = true;
	grammar.close_paren = false;

	grammar->curr = curr_node;
	grammar->prev = NULL;
	grammar->next = NULL;
}

/* > |
 * redirs require word after
 * there cannot be consecutive operators, unless it is a redir
 */



void	validate_grammar(t_list *curr_node)
{
	t_grammar_vars	grammar;

	initializes_grammar_vars(grammar, curr_node);
	while (curr_node && prog_state(TAKE_STATE) == PROG_OK)
	{
		/* no rules for words. traverse them normally. */
		if (get_token(curr_node)->type == OPERATOR)
		{
			// ✅ redirections NEED
			if (is_redir_op(get_token(curr_node)))
				/* unexpected token is current_token */
				if (!grammar->next || (get_token(grammar->next)->type != WORD))
					prog_state(PARSER_ERROR);

			else if (is_logical_op(get_token(grammar_curr)))
			{
				if (!grammar->prev)
					prog_state(PARSER_ERROR);
				/* unexpected token is current_token */
				if (is_logical_op(get_token(grammar->next)))
					prog_state(PARSER_ERROR);
			}
			else if (ft_strncmp(get_token(grammar->curr)->str, "|"))
			{
				if (!grammar->prev)
					prog_state(PARSER_ERROR);
				else if (grammar->next && (ft_strncmp(get_token(grammar->next)->str, "|"))
					prog_state(PARSER_ERROR);
			}
			else if (ft_strncmp(get_token(grammar->curr)->str, "("))
			{
				if (!grammar->next)
					prog_state(PARSER_ERROR);
				if (!grammar->prev)
					prog_state(PARSER_ERROR);
			}
			advance_node(grammar);
	}
}
