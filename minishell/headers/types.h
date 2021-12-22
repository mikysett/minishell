/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <mikysett@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:13:20 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:55:37 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define ERROR_MESSAGE "minishell: syntax error near unexpected token `"

# define MAX_PROMPT_SIZE		80

# define EXIT_EXIT_ERROR		2
# define EXIT_PARSER_ERROR		258
# define EXIT_INCORRECT_USAGE	2
# define EXIT_FILE_NOT_EXEC		126
# define EXIT_FILE_NOT_FOUND	127
# define EXIT_SIGINT			130

/*
	SIGINT		Ctrl+C
	SIGQUIT		Ctrl+\
*/

typedef enum e_pipe_side
{
	PIPE_READ = 0,
	PIPE_WRITE = 1
}				t_pipe_side;

typedef enum e_prog_state
{
	TAKE_STATE,
	SIGINT_RECEIVED,
	PROG_OK,
	PROG_READ,
	PARSER_ERROR
}				t_prog_state;

typedef struct s_env_var
{
	char	*key;
	char	*value;
	bool	is_printed;
}				t_env_var;

typedef enum e_token_type
{
	WORD,
	OPERATOR
}				t_token_type;

typedef enum e_operator_type
{
	OP_NONE,
	OP_REDIR,
	OP_PIPE,
	OP_PARENS_OPEN,
	OP_PARENS_CLOSE,
	OP_LOGIC
}				t_operator_type;

typedef enum e_quote_type
{
	NO_QUOTING,
	SINGLE_QUOTES,
	DOUBLE_QUOTES
}				t_quote_type;

typedef enum e_err_code
{
	ERR_NO_PRINT,
	MEMORY_FAIL,
	WRONG_QUOTING
}				t_err_code;

typedef struct s_token
{
	t_token_type	type;
	t_operator_type	op_type;
	char			*str;
}				t_token;

typedef struct s_cmd
{
	int		id;
	int		group;
	bool	is_empty_cmd;
	char	*name;
	char	*full_path;
	char	**args;
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

typedef struct s_redirect
{
	t_redir_type	type;
	int				cmd_id;
	char			*file_name;
}				t_redirect;

typedef struct s_has_redirs
{
	bool	in;
	bool	out;
}				t_has_redirs;

typedef enum e_inst_type
{
	INSTR_CMD,
	INSTR_OR,
	INSTR_AND,
	INSTR_GRP_START,
	INSTR_GRP_END
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

typedef struct s_grammar_vars {
	t_list		*curr;
	t_list		*prev;
	t_list		*next;
	int			paren_count;
}				t_grammar_vars;

typedef struct s_minishell
{
	char		*prog_name;
	char		*prompt;

	t_list		**instructions;
	t_list		**redirect;
	t_list		**tokens;

	t_std_io	streams;

	char		**envp;
	t_list		**env_vars;
	char		**paths;

	int			exit_code;
}				t_minishell;

#endif
