#include "minishell.h"

int	unset_builtin(char **argv)
{
	const int			args_nb = args_count(argv);
	const t_minishell	*ms = get_minishell(NULL);
	bool				vars_changed;
	int					exit_code;
	int					i;

	vars_changed = false;
	exit_code = EXIT_SUCCESS;
	i = 1;
	while (i < args_nb)
	{
		if (!is_valid_identifier(argv[i]))
		{
			exit_code = EXIT_FAILURE;
			print_identifier_error(ms->prog_name, "unset", argv[i]);
		}
		else if (unset_env_var(ms->env_vars, argv[i]))
			vars_changed = true;
		i++;
	}
	if (vars_changed)
		save_envp((t_minishell *)ms);
	return (exit_code);
}
