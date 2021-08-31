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
	gets_commands(tokens, cmd_list);
}

/* returns a t_list of commands.
 * always assumes every function call is the first token */
static void gets_command(t_list **tokens, t_list **cmd_list)
{
	t_cmd *cmd;
	int i;

	*command = calloc_or_exit(1, sizeof(t_cmd))
	i = -1;
	while (tokens && tokens[++i])
	{
		if (i == 0 && tokens[i]->type == WORD)
			command->name = tokens[i]->str;
		else
		{
			if (tokens[i]->str == 'C' &&) // and is valid operator
			{
				gets_command(&tokens[i], cmd_list);
				while (tokens[i] !=  // closing operator
					// advance i;
	}
}
