#ifndef TYPES_H
# define TYPES_H

# define CLR_WHITE	"\033[0;37m"
# define CLR_BLACK	"\033[0;30m"
# define CLR_GRAY	"\033[30;1m"
# define CLR_RED	"\033[0;31m"
# define CLR_GREEN	"\033[0;32m"
# define CLR_YELLOW	"\033[0;33m"
# define CLR_BLUE	"\033[0;34m"
# define CLR_PURPLE	"\033[0;35m"
# define CLR_CYAN	"\033[0;36m"

typedef enum e_pipe_side
{
	PIPE_READ = 0,
	PIPE_WRITE = 1
}				t_pipe_side;

typedef enum e_token_type
{
	WORD,
	OPERATOR,

	// TODO next 3 token types are not necessary but I kept them as a good reference
	control_operator,		/* newline, ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’ */
	redirection_operator,	/* '<', '>', '<<', '>>',  */
	metacharacter			/* space, tab, newline, ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’ */
}				t_token_type;

typedef enum e_quote_type
{
	NO_QUOTING,
	SINGLE_QUOTES,
	DOUBLE_QUOTES
}				t_quote_type;

typedef enum e_err_code
{
	MEMORY_FAIL,
	WRONG_QUOTING
}				t_err_code;

typedef enum e_prog_state
{
	TAKE_STATE,
	PROG_OK,
	PARSER_ERROR
}				t_prog_state;

typedef struct s_token
{
	t_token_type	type;
	t_quote_type	quote_type;
	char			*str;
}				t_token;

typedef struct s_cmd
{
	int		id;
	int		group;
	char	*name;
	char	*full_path;
	char	**args;
	bool	is_first_in_group;	// can be removed ?
	bool	is_last_in_group;	// can be removed ?
	bool	is_builtin;			// if better can be implemented in executor
}				t_cmd;

typedef enum e_redir_type
{
	REDIR_PIPE_IN,
	REDIR_PIPE_OUT,
	REDIR_IN,
	REDIR_HERE_DOC,
	REDIR_OUT,
	REDIR_OUT_APPEND
}				t_redir_type;

typedef struct	s_redirect
{
	t_redir_type	type;
	int				cmd_id;
	int				group_id;
	char			*file_name;
}				t_redirect;

typedef enum e_inst_type
{
	INSTR_CMD,
	INSTR_OR,
	INSTR_AND
}				t_instr_type;

typedef struct s_instruction
{
	t_instr_type	type;
	t_cmd			*cmd;
}				t_instruction;

typedef struct s_std_io
{
	int		stdin_fd;
	int		stdout_fd;
	bool	stdin_saved;
	bool	stdout_saved;

	int		curr_in;
	int		curr_out;
}				t_std_io;

typedef struct s_minishell
{
	char	*prog_name;
	
	t_list	**instructions;
	t_list	**redirect;
	t_list	**tokens;

	t_std_io	streams;

	char	**envp;
	char	**paths;

	int		exit_code;
}				t_minishell;

#endif
