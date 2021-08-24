#include "minishell.h"

static	void print_quote_type(t_quote_type q_type);

void	print_tokens(t_list **tokens)
{
	t_list	*curr;
	t_token	*token;

	curr = *tokens;
	printf("--> TOKENS\n");
	while (curr)
	{
		token = (t_token *)curr->content;
		printf("<");
		print_quote_type(token->quote_type);
		printf("%s", token->str);
		print_quote_type(token->quote_type);
		printf("> ");
		curr = curr->next;
	}
	printf("\n");
}

static	void print_quote_type(t_quote_type q_type)
{
	if (q_type == SINGLE_QUOTES)
		printf("'");
	else if (q_type == DOUBLE_QUOTES)
		printf("\"");
}