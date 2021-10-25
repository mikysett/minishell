#ifndef PARSER_H
# define PARSER_H

// PARSER
t_minishell		*parser(char *line, t_minishell *minishell);

// LEXER
t_list			**lexer(char *line, t_list **tokens);

// QUOTE_UTIL
t_quote_type	get_quote_type(char c);
bool			update_quote_type(t_quote_type curr, t_quote_type *prev);

// TOKENS
char			*get_token_end(char *str, t_token *token);

// PERFORM_EXPANSIONS
void			perform_expansions(t_list **tokens);

// PARAMETER_EXPANSION
void			parameter_expansion(t_list **tokens);
void			expand_parameter(char *start_name, int size_name,
	t_token *token);

// FILENAME_EXPANSION
void			filename_expansion(t_list **tokens);
void			save_expansion_if_match(t_list **new_tokens, char *d_name,
					char *token_str);

// QUOTE_REMOVAL
void			quote_removal(t_list *curr_token_lst);

// LEXER_UTILS
bool			is_operator(char *str);
char			*next_non_space(char *str);

// PARSER_UTILS
t_token			*get_token(t_list *curr_node);
int				take_length_of_command(t_list *node);
t_cmd			*init_empty_cmd(int cmd_id, int cmd_group);
t_cmd			*init_instruction(t_minishell *ms, t_instr_type type);
t_redirect		*init_redirection(t_minishell *ms, t_redir_type type);
void			create_redir(t_token *token, char *file_name,
					int redir_type, int cmd_id);
int				get_redir_type(t_token *token);
void			validate_grammar(t_list *curr_node);
void	parse_tokens(t_list *curr_node, int cmd_id, int cmd_group);
t_list	*parse_logical_op(t_list *curr_node);
t_list	*parse_command(t_list *tokens, t_cmd *cmd, int cmd_id, int cmd_group);
t_list	*parse_pipe(t_list *curr_node, int cmd_id);
t_list	*parse_redir(t_list *curr_node, int cmd_id);
void create_command_and_redir(t_list *curr_node, int cmd_id, int cmd_group);


#endif
