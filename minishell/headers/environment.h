#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

char	**get_envp(void);

// ENV_VARS
t_list	**init_env_vars(char **envp);

// ENVP
void	save_envp(t_minishell *ms);

// ENV_PRINT
void	print_env_vars(t_list *env_vars);
void	print_env(char **envp);

#endif
