/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:50:22 by damachad          #+#    #+#             */
/*   Updated: 2023/11/29 13:35:16 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Checks if a char is part of the string
*/
bool	is_present(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (true);
	}
	return (false);
}

/*
**	Searches for operators and returns the flag
*/
int	is_operator(char *word, t_shell *sh)
{
	if (word[0] == '|' && !is_present(OPERATORS, word[1]))
	{
		sh->nbr_commands++;
		return (PIPE);
	}
	else if (word[0] == '>' && word[1] == '>' && \
	!is_present(OPERATORS, word[2]))
		return (DOU_GREAT);
	else if (word[0] == '<' && word[1] == '<' && \
	!is_present(OPERATORS, word[2]))
	{
		sh->n_heredocs++;
		return (DOU_LESS);
	}
	else if (word[0] == '<' && !is_present(OPERATORS, word[1]))
		return (LESS);
	else if (word[0] == '>' && !is_present(OPERATORS, word[1]))
		return (GREAT);
	else
		return (WORD);
}

/*
**	Advances the index j to the next quote so I closes
*/
void	advance_quote(char *str, int *j, char next_char)
{
	(*j)++;
	while (str[*j] && str[*j] != next_char)
		(*j)++;
	if (str[*j] == next_char)
		(*j)++;
}

/*
**	Advances the index j to the next space,
** and separates operators from words
*/
void	advance_word(char *str, int *j)
{
	bool	quotes;

	if (str[*j] && is_present(OPERATORS, str[*j]))
	{
		while (str[*j] && is_present(OPERATORS, str[*j]))
			(*j)++;
		return ;
	}
	while (str[*j] && !is_present(SPACES, str[*j]) && \
	!is_present(OPERATORS, str[*j]))
	{
		if (is_present("\"\'", str[*j]))
		{
			quotes = !quotes;
			advance_quote(str, j, str[*j]);
		}
		else
			(*j)++;
	}
}

/*
**	Calculates the end position of a word
*/
void	word_end_pos(char *ui, t_shell *sh)
{
	sh->index->j = sh->index->i;
	if (ui[sh->index->j] == '\"' || ui[sh->index->j] == '\'')
	{
		advance_quote(ui, &sh->index->j, ui[sh->index->j]);
		while (!is_space(ui[sh->index->j]) && ui[sh->index->j] != '\0')
		{
			if (ui[sh->index->j] == '\"' || ui[sh->index->j] == '\'')
				advance_quote(ui, &sh->index->j, ui[sh->index->j]);
			else
				advance_word(ui, &sh->index->j);
		}
	}
	else
		advance_word(ui, &sh->index->j);
}
