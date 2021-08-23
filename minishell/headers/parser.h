#ifndef PARSER_H
# define PARSER_H

t_minishell	parser(char *line);

// LEXER
t_list		**lexer(char *line);
char		*next_non_space(char *str);
char		*get_token_end(char *str);
bool		is_operator(char c);
#endif
