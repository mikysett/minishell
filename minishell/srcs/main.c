#include "minishell.h"

int	main(int argc, char **argv, char **envp)
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
			}
		}
		if (line)
			free(line);
	}
	// rl_clear_history(); // Compatibility issues with mac os
	return (0);
}
