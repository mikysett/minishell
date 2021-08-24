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
		printf("%s<%s", CLR_GRAY, CLR_WHITE);
		print_quote_type(token->quote_type);
		if (token->type == operator)
			printf("%s", CLR_PURPLE);
		printf("%s", token->str);
		print_quote_type(token->quote_type);
		printf("%s>%s ", CLR_GRAY, CLR_WHITE);
		curr = curr->next;
	}
	printf("\n");
}

static	void print_quote_type(t_quote_type q_type)
{
	if (q_type == SINGLE_QUOTES)
		printf("%s'%s", CLR_YELLOW, CLR_WHITE);
	else if (q_type == DOUBLE_QUOTES)
		printf("%s\"%s", CLR_GREEN, CLR_WHITE);
}