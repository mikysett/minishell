#include <stdio.h>
#include <stdbool.h>

typedef struct s_grammar_vars {
	t_list  *curr;
	t_list	*prev;
	t_list	*next;
	int		word;
	int		pipe;
	int		redir;
	int		close_paren;
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
 *
 */

void	validate_grammar(t_list *curr_node)
{
	t_grammar_vars	grammar;

	initializes_grammar_vars(grammar, curr_node);
	while (curr_node && prog_state(TAKE_STATE) == PROG_OK)
	{
		/* no rules for words. traverse them normally. */
		if (get_token(curr_node)->type == WORD);
		if (get_token(curr_node)->type == OPERATOR)
		{
			if (is_redir_op(get_token(curr_node)))
				/* unexpected token is current_token */
				if (!grammar->next || (get_token(grammar->next)->type != WORD))
					prog_state(PARSER_ERROR);

		advance_node(grammar);

	}
}
