#include "minishell.h"

void	del_token(void *token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	if (token)
	{
		free(token->str);
		free(token);
	}
}

void	del_instruction(void *instruction_void)
{
	t_instruction	*instruction;

	instruction = (t_instruction *)instruction_void;
	if (instruction)
	{
		if (instruction->type == INSTR_CMD)
		{
			free(instruction->cmd->name);
			free(instruction->cmd->full_path);
			ft_free_str_arr(instruction->cmd->args);
			free(instruction->cmd);
		}
		free(instruction);
	}
}

void	del_redirect(void *redirect_void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)redirect_void;
	if (redirect)
	{
		if (redirect->file_name)
			free(redirect->file_name);
		free(redirect);
	}
}

void	del_env_var(void *env_var_void)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)env_var_void;
	if (env_var)
	{
		if (env_var->key)
			free(env_var->key);
		if (env_var->value)
			free(env_var->value);
		free(env_var);
	}
}
