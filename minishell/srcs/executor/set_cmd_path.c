#include "minishell.h"

static bool	is_std_cmd(char *cmd_name);
static char	*try_default_paths(char **paths, char *cmd_name);
static char	*try_custom_path(char *cmd_name);

char	*set_cmd_path(t_minishell *ms, t_cmd *cmd)
{
	char	*full_path;

	if (is_std_cmd(cmd->name))
		full_path = try_default_paths(ms->paths, cmd->name);
	else
		full_path = try_custom_path(cmd->name);
	if (!full_path)
	{
		ft_putstr_fd(ms->prog_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(cmd->name);
	}
	return (full_path);
}

static bool	is_std_cmd(char *cmd_name)
{
	while (*cmd_name)
	{
		if (*cmd_name == '/')
			return (false);
		cmd_name++;
	}
	return (true);
}

static char	*try_default_paths(char **paths, char *cmd_name)
{
	int			i;
	int			cmd_path_size;
	const int	cmd_name_len = ft_strlen(cmd_name);
	char		*full_path;

	i = 0;
	if (!paths)
		return (NULL);
	if (cmd_name_len == 0)
		return (strdup_or_exit(cmd_name));
	while (paths[i])
	{
		cmd_path_size = ft_strlen(paths[i]) + cmd_name_len + 2;
		full_path = ft_calloc(cmd_path_size, sizeof(char));
		if (!full_path)
			ft_error_exit(MEMORY_FAIL);
		ft_strlcat(full_path, paths[i], cmd_path_size);
		ft_strlcat(full_path, "/", cmd_path_size);
		ft_strlcat(full_path, cmd_name, cmd_path_size);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*try_custom_path(char *cmd_name)
{
	char	*full_path;

	full_path = strdup_or_exit(cmd_name);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	else
	{
		free(full_path);
		return (NULL);
	}
}
