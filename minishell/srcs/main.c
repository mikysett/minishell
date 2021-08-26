#include "minishell.h"

int	main(void)
// int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	*minishell;

	minishell = init_minishell_mem();
	while (1)
	{
		prog_state(PROG_OK);
		line = readline("minishell$ ");
		if (line && *line)
		{
			add_history(line);
			minishell = parser(line, minishell);
			if (prog_state(TAKE_STATE) == PROG_OK)
			{
				// TODO execute the commands
				// WORK IN PROGRESS execute the commands

				// minishell->exit_code = executor(minishell,
				// 	*minishell->instructions,
				// 	EXIT_SUCCESS);
			}
		}
		if (line)
			free(line);
	}
	// rl_clear_history(); // Compatibility issues with mac os
	return (minishell->exit_code);
}
