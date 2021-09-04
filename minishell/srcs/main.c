#include "minishell.h"

static void	interactive_mode(t_minishell *minishell);
static void	non_interactive_mode(t_minishell *minishell, char *bash_file);

int	main(int argc, char **argv, char **envp)
// int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	minishell = init_minishell(argv[0], envp);
	print_env(minishell->envp);
	print_env_vars(*minishell->env_vars);
	if (argc == 1)
		interactive_mode(minishell);
	else
		non_interactive_mode(minishell, argv[1]);
	return (minishell->exit_code);
}

static void	interactive_mode(t_minishell *ms)
{
	char		*line;

	while (1)
	{
		prog_state(PROG_OK);
		line = readline("minishell$ ");
		// WORK IN PROGRESS execute the commands
		if (line && *line)
		{
			add_history(line);
			ms = parser(line, ms);
			if (prog_state(TAKE_STATE) == PROG_OK)
			{
				DEBUG(
					create_fake_cmd6(ms);
				)
				restore_std_io(false, false);
			}
		}
		if (line)
			free(line);
	}
	// rl_clear_history(); // Compatibility issues with mac os
}

static void	non_interactive_mode(t_minishell *ms, char *bash_file)
{
	int		bash_file_fd;
	char	*line;

	bash_file_fd = ft_init_file_fd(bash_file, O_RDONLY, 0);
	if (!bash_file_fd)
		return ;

	prog_state(PROG_OK);
	while (get_next_line(bash_file_fd, &line))
	{
		ms = parser(line, ms);
		if (prog_state(TAKE_STATE) == PROG_OK)
		{
			DEBUG(
				create_fake_cmd4(ms);
			)
			restore_std_io(false, false);
		}
		free(line);
	}
}
