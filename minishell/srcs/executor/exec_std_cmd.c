#include "minishell.h"

static int	exec_child(t_minishell *ms, t_cmd *cmd);
static int	exec_parent(pid_t child_pid);

int	exec_std_cmd(t_cmd *cmd)
{
	pid_t		child_pid;
	t_minishell	*ms;

	ms = get_minishell(NULL);
	cmd->full_path = set_cmd_path(ms, cmd);
	if (!cmd->full_path)
		return (EXIT_CMD_NOT_FOUND);
	child_pid = fork();
	if (child_pid == 0)
		return (exec_child(ms, cmd));
	else if (child_pid != -1)
		return (exec_parent(child_pid));
	else
	{
		perror(ms->prog_name);
		return (EXIT_FAILURE);
	}
}

static int	exec_child(t_minishell *ms, t_cmd *cmd)
{
	if (execve(cmd->full_path, cmd->args, ms->envp) == -1)
	{
		ft_putstr_fd(ms->prog_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(cmd->name);
		exit(EXIT_CMD_NOT_EXEC);
	}
	return (EXIT_CMD_NOT_EXEC);
}

static int	exec_parent(pid_t child_pid)
{
	int	cmd_exit_status;

	if (waitpid(child_pid, &cmd_exit_status, 0) == -1)
	{
		perror(get_minishell(NULL)->prog_name);
		return (EXIT_FAILURE);
	}
	if (WIFEXITED(cmd_exit_status))
		return (WEXITSTATUS(cmd_exit_status));
	// TODO this last exit code is not doublecheckded
	else
		return (EXIT_FAILURE);
}
