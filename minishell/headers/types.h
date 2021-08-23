#ifndef TYPES_H
# define TYPES_H

typedef enum e_token_type
{
	word,
	operator,

	// TODO next 3 token types are not necessary but I kept them as a good reference
	control_operator,		/* newline, ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’ */
	redirection_operator,	/* '<', '>', '<<', '>>',  */
	metacharacter			/* space, tab, newline, ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’ */
}				t_token_type;

typedef enum e_err_code
{
	MEMORY_FAIL
}				t_err_code;

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
