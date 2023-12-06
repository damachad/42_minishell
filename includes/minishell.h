/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:37:26 by damachad          #+#    #+#             */
/*   Updated: 2023/12/06 16:40:16 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Includes

# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

# include "../libft/libft.h"
# include "prototypes.h"
# include "structs.h"

// Macros

# define CMD 2
# define SPACES "\t\n\v\f\r "
# define NOT_EXPRESSION "|><&();/ \t\n\v\f\r"
# define OPERATORS "<>|"
# define MINISHELL "[MINISHELL]:"
# define HERE "warning: here-document delimited by end-of-file (wanted"
# define UNEXPECTED_TOK "minishell: syntax error near unexpected token\n"
# define UNEXPECTED_EOF "minishell: syntax error: unexpected end of file"
# define INVALID_ID "': not a valid identifier"

//global variable exit code
extern int	g_signo;

#endif
