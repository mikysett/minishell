#ifndef TYPES_H
# define TYPES_H

typedef enum e_token_type
{
	word,
	control_operator,		/* newline, ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’ */
	redirection_operator,	/* '<', '>', '<<', '>>',  */
	metacharacter			/* space, tab, newline, ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’ */
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			str;
}				t_token;

typedef struct s_cmd
{
	char	*name;
	char	**args;
	char	*in;
	char	*out;
}				t_cmd;

typedef struct s_minishell
{
	t_list	**cmds;
	t_list	**tokens;
}				t_minishell;

#endif
