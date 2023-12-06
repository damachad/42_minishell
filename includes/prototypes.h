/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:46:31 by damachad          #+#    #+#             */
/*   Updated: 2023/12/06 16:44:49 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "minishell.h"
# include "structs.h"

/* -------------------- PROMPT -------------------- */

// Located in *prompt.c*
void		empty_line(t_shell *sh);
void		line_empty_test(t_shell *sh);
char		*get_prompt(t_shell *sh);

/* -------------------- LEXER -------------------- */

// Located in *lexer.c*
t_lexer		*last_node(t_lexer *start);
t_lexer		*lexer_new(char *word, int i, t_shell *sh);
void		lexer_add_back(t_lexer **lexer, t_lexer *new);
t_lexer		*ft_lexer(char *ui, t_shell *sh);

// Located in *lexer_utils.c*
bool		is_present(const char *str, char c);
int			is_operator(char *word, t_shell *sh);
void		advance_quote(char *str, int *j, char next_char);
void		advance_word(char *str, int *j);
void		word_end_pos(char *ui, t_shell *sh);

/* -------------------- PARSER -------------------- */

// Located in *parser_utils.c*
t_tree_node	*command_node(t_lexer **start, t_lexer *end, t_shell *sh);

// Located in *parser.c*
void		list_to_array(t_lexer *start, t_lexer *end, char ***cmd);
t_tree_node	*build_tree(t_lexer **start, t_shell *sh);

/* -------------------- HEREDOC -------------------- */

// Located in *heredoc_utils.c*
void		heredoc_maker(t_lexer *heredoc_node, t_shell *sh);

// Located in *heredoc.c*
void		remove_quotes_heredoc(char *str);
void		heredoc_check(t_lexer *lexer, t_shell *sh);

/* -------------------- OPEN_PIPE -------------------- */

// Located in *open_pipe.c*
void		herestr_child(t_shell *sh);
char		*open_pipe(t_shell *sh);

// Located in *open_pipe_2.c*
bool		pipes_together(char *str);
void		open_pipes_child(t_shell *sh);
bool		is_solo_pipe(char *str);
bool		consecutive_pipes(char *str);
char		*ft_strstr(char *haystack, char *needle);

/* -------------------- EXPANDER -------------------- */

// Located in *expander_utils.c*
int			remove_nulls(char **cmds, int nbr_cmds);
int			expand_cmds(char *key, int i, int j, char **line);
void		handle_invalid_env(int point, int len, char **line);
void		expand_valid_env(int point, t_shell *sh, char *env_value, \
							char **line);
int			expand_free(char *key, int i, int j, char **line);

// Located in *expand_arg.c*
int			find_dollar(t_shell *sh, int point, char *tmp, char **line);
int			check_quotes_str(const char *str, t_shell *sh);
void		env_expand_dollar(t_shell *sh, char *tmp, char **line);
void		update_cmds(t_shell *sh, char *value, char **line);

// Located in *expander.c*
void		space_pipes(t_shell *sh, char *tmp);
void		expander(char ***cmds, t_shell *sh);
char		*trim_spaces(t_shell *sh, char *str);

/* -------------------- SIGNALS -------------------- */

// Located in signals.c
void		sigint_handler(int signo);
void		sighandler_child(int signo);
void		reset_signals(void);

// Located in signals2.c
void		set_exit_status(t_shell *sh, int status);
void		heredoc_handler(int signo);

/* -------------------- EXECUTION -------------------- */

// Located at *command_handling.c*
char		*ft_strtok(char *str, char *delimiter);
bool		check_comm(t_shell *sh, char **cmds);
void		execute_comm(t_shell *sh, char **cmds);
void		handle_output_redir(t_shell *sh, t_tree_node *node);
void		handle_input_redir(t_shell *sh, t_tree_node *node);

// Located at *executor_utils.c*
void		handle_command_not_found(t_shell *sh, const char *command);
void		handle_file_not_found(t_shell *sh, const char *file);
void		h_cmd_not_exist(t_shell *sh, const char *cmd, int err_no, \
							char *path);
void		create_pipes(t_shell *sh);
void		close_pipes(t_shell *sh);

// Located at *path.c*
int			is_absolute_path(char *cmd);
char		*search_executable(char *cmd, char *path_env);
char		*find_path(char *cmd, t_shell *sh);
void		null_path(t_shell *sh, char **cmds);

// Located at *executor.c*
void		executor(t_shell *sh, t_tree_node *parser, int i);

/* -------------------- BUILT-INS -------------------- */

// Located in *builtin_cd.c*
bool		is_home(t_shell *sh, char **cmds);
int			builtin_cd(t_shell *sh, char **cmds);

// Located in *builtin_echo.c*
int			builtin_echo(char **cmds);

// Located in *builtin_env.c*
int			builtin_env(t_shell *sh, char **cmds);

// Located in *builtin_exit.c*
void		builtin_exit(t_shell *sh, char **cmds);

// Located in *builtin_export.c*
int			builtin_export(t_shell *sh, char **cmds);
// Located in *builtin_export_print.c*
void		print_export(t_shell *sh);

// Located in *builtin_pwd.c*
int			builtin_pwd(t_shell *sh);

// Located in *builtin_unset.c*
int			builtin_unset(t_shell *sh, char **cmds);

// Located in *builtin_main.c*
bool		strn_strl_cmp(char *s1, char *s2);
bool		is_builtin_parent(char **cmd);
bool		is_builtin_child(char **cmd);
int			builtin_router(t_shell *sh, char **cmds);

/* -------------------- ENVIRONMENT -------------------- */

// Located in *env.c*
t_envlst	*ft_lstnew_env(char *key, char *value, int visible);
char		*get_key(char *mini_env);
char		*get_value(char *mini_env);
void		create_env_list(t_shell *sh);

// Located in *env_utils.c*
void		free_env_lst(t_envlst *env_lst);
void		free_node_env(t_envlst *node);
void		free_nodes_env(t_envlst **list);
char		**copy_envp(char **envp);
void		ft_lstadd_back_env(t_envlst **head, t_envlst *new_node);

// Located in *envlst_use.c*
int			ft_list_size_env(t_envlst *list);
void		join_mini_env(t_envlst *env_lst, char **mini_env, int i);
void		update_mini_env(t_shell *sh);
char		*get_env_value(t_shell *sh, char *key);
int			change_env_value(t_shell *sh, char *key, char *new_value);

// Located in *builtin_env.c*
void		print_env_list(t_shell *sh);

/* -------------------- CLEAN-UP -------------------- */

// Located at *main.c*
void		reset_loop(t_shell *sh);
void		ft_loop(t_shell *sh);

// Located in *clean.c*
void		clear_shell(t_shell *sh);
void		lexer_deltwo(t_lexer **lexer, int key);
void		lexer_free_node(t_lexer *node);

// Located in *clean2.c*
void		free_lexer_list(t_lexer *head);
void		free_matrix(char **matrix);
void		free_int_matrix(t_shell *sh);

// Located in *clean3.c*
void		delete_heredoc_list(t_shell *sh);
void		free_parser_tree(t_tree_node *root);
void		free_lexer_list_rev(t_lexer **tail);
void		mini_clean(t_shell *sh, int i);
void		handle_empty_line_herestr(t_shell *sh, int fd);

// Located in *error.c*
bool		double_operator(t_lexer *lexer);
int			is_syntax_correct(t_lexer *lexer);
int			error_3s(t_shell *sh, char *str1, char *str2, char *str3);
void		error_4s(char *str1, char *str2, char *str3, char *str4);
bool		empty_redir(t_lexer *lexer);

/* -------------------- TESTING -------------------- */

// Tester functions
void		print_env_value(t_shell *sh, char *key);
void		print_mini_envp(char **mini_envp);
void		print_lexer(t_lexer *lexer);
// void		print_tree(t_tree_node *root, int depth);

#endif
