/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:35:49 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/27 17:01:14 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef enum s_tokens
{
	WORD,
	PIPE,
	GREAT,
	DOU_GREAT,
	LESS,
	DOU_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		operator;
	int				i;
	char			*eof;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
	int	dquote;
	int	squote;
}	t_index;

typedef struct s_envlst
{
	char			*key;
	char			*value;
	int				visible;
	struct s_envlst	*next;
}				t_envlst;

typedef struct s_tree_node
{
	int					type;
	char				**cmd;
	t_lexer				*in_redirs;
	t_lexer				*out_redirs;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_shell
{
	char		*ui;
	char		*prompt;
	char		*home;
	char		*files;
	char		**mini_env;
	char		***cmds;
	t_envlst	*env_lst;
	t_lexer		*lexer;
	t_tree_node	*parser;
	t_index		*index;
	t_lexer		*heredoc_fd;
	int			exit_code;
	int			n_heredocs;
	int			here_quotes_eof;
	int			len;
	int			expanded;
	int			nbr_commands;
	int			**pipes;
	int			fd_in;
	int			fd_out;
	int			pid;
}				t_shell;

#endif
