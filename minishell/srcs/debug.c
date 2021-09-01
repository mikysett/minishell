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
		if (token->type == OPERATOR)
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

void	print_instructions(t_list **instr)
{
	t_list			*curr;
	t_instruction	*instruction;
	int				i = 0;
	int				j = 0;
	static char		instr_str[3][100] = {
			"COMMAND",
			"OR",
			"AND"
		};

	curr = *instr;
	printf("--> INSTRUCTIONS <--\n");
	while (curr)
	{
		instruction = (t_instruction *)curr->content;
		printf("    %2d: %s\n", i, instr_str[instruction->type]);
		if (instruction->type == INSTR_CMD)
			printf("\tid: %2d %-15s",
				instruction->cmd->id,
				instruction->cmd->name);
		j = 0;
		if (instruction->cmd->args)
		{
			while (instruction->cmd->args[j])
			{
				printf("%s ", instruction->cmd->args[j]);
				j++;
			}
		}
		printf("\n");
		curr = curr->next;
	}
	printf("\n");
}

void	print_redirections(t_list **redir)
{
	t_list			*curr;
	t_redirect		*curr_redir;
	static char		redir_str[6][100] = {
			"PIPE IN",
			"PIPE OUT",
			"REDIR IN",
			"HERE DOC",
			"REDIR OUT",
			"REDIR OUT APPEND"
		};

	curr = *redir;
	printf("--> REDIRECTIONS <--\n");
	while (curr)
	{
		curr_redir = (t_redirect *)curr->content;
		printf("\tcmd id: %2d %-15s %s",
			curr_redir->cmd_id,
			redir_str[curr_redir->type],
			curr_redir->file_name);
		printf("\n");
		curr = curr->next;
	}
	printf("\n");
}

void	create_fake_cmd(t_minishell *ms)
{
	t_redirect fake_redir1;
	t_redirect fake_redir2;
	t_redirect fake_redir3;
	t_redirect fake_redir4;

	t_instruction	fake_instr1;
	t_instruction	fake_instr2;

	t_cmd			fake_cmd1;
	t_cmd			fake_cmd2;

	ms->instructions = malloc(sizeof(t_instruction *));
	ms->redirect = malloc(sizeof(t_redirect *));
	*ms->instructions = NULL;
	*ms->redirect = NULL;

	fake_redir1.cmd_id = 0;
	fake_redir1.file_name = ft_strdup("filein1");
	fake_redir1.type = REDIR_IN;

	fake_redir2.cmd_id = 0;
	fake_redir2.type = REDIR_PIPE_OUT;

	fake_redir3.cmd_id = 1;
	fake_redir3.type = REDIR_PIPE_IN;

	*(ms->redirect) = ft_lstnew(&fake_redir1);
	ft_lstadd_back(ms->redirect, ft_lstnew(&fake_redir2));
	ft_lstadd_back(ms->redirect, ft_lstnew(&fake_redir3));

	fake_instr1.type = INSTR_CMD;
	fake_instr2.type = INSTR_CMD;
	*(ms->instructions) = ft_lstnew(&fake_instr1);
	ft_lstadd_back(ms->instructions, ft_lstnew(&fake_instr2));

	fake_cmd1.args = ft_split("cat", ' ');
	fake_cmd1.id = 0;
	fake_cmd1.is_builtin = false;
	fake_cmd1.name = ft_strdup("cat");

	fake_cmd2.args = ft_split("wc -l", ' ');
	fake_cmd2.id = 1;
	fake_cmd2.is_builtin = false;
	fake_cmd2.name = ft_strdup("wc");

	fake_instr1.cmd = &fake_cmd1;
	fake_instr2.cmd = &fake_cmd2;

	print_instructions(ms->instructions);
	print_redirections(ms->redirect);
	executor(ms, *ms->instructions, EXIT_SUCCESS);
}