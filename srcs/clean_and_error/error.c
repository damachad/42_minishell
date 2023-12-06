/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:34:09 by damachad          #+#    #+#             */
/*   Updated: 2023/11/27 17:30:14 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Located in *clean.h*

/*
**	This function checks if there is a double operator
*/
bool	double_operator(t_lexer *lexer)
{
	t_lexer	*curr;
	t_lexer	*prev;

	curr = lexer;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		if (curr && prev->operator && curr->operator)
		{
			if (prev->operator == PIPE && curr->operator != PIPE)
				continue ;
			else
				return (true);
		}
	}
	return (false);
}

/*
**	This function checks if the syntax is correct
*/
int	is_syntax_correct(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (tmp && tmp->str[0] == '|')
		return (2);
	while (tmp)
	{
		if (tmp->str[0] == '|' && is_present(OPERATORS, tmp->str[1]))
			return (2);
		if (tmp->str[0] == '<' && is_present("|>", tmp->str[1]))
			return (2);
		if (tmp->str[0] == '>' && is_present("|<", tmp->str[1]))
			return (2);
		if (tmp->str[0] == '>' && tmp->str[1] == '>' \
		&& is_present(OPERATORS, tmp->str[2]))
			return (2);
		if (tmp->str[0] == '<' && tmp->str[1] == '<' \
		&& is_present(OPERATORS, tmp->str[2]))
			return (2);
		tmp = tmp->next;
	}
	if (double_operator(lexer) || empty_redir(lexer))
		return (2);
	return (0);
}

/* 
**	Output error message and return error number
** always starts with "minishell: "
** has space for 3 input strings
*/
int	error_3s(t_shell *sh, char *str1, char *str2, char *str3)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	return (sh->exit_code);
}

/* 
**	Output error message and return error number
** always starts with "minishell: "
** has space for 4 string inputs
*/
void	error_4s(char *str1, char *str2, char *str3, char *str4)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
	write(2, str4, ft_strlen(str4));
	write(2, "\n", 1);
}

/*
**	This function is called when 
** there is no redirection found
*/
bool	empty_redir(t_lexer *lexer)
{
	t_lexer	*curr;
	t_lexer	*prev;

	curr = lexer;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		if (!curr && prev->operator)
			return (true);
	}
	return (false);
}
