/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:53:39 by damachad          #+#    #+#             */
/*   Updated: 2023/11/29 12:30:41 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Returns the last node of the list
*/
t_lexer	*last_node(t_lexer *start)
{
	while (start && start->next)
		start = start->next;
	return (start);
}

/*
**	Creates a new node of type t_lexer and initializes it 
** with the word passed as parameter, the index of the node 
** and the operator (which one)
*/
t_lexer	*lexer_new(char *word, int i, t_shell *sh)
{
	t_lexer		*new;

	new = ft_calloc(1, sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = word;
	new->operator = is_operator(word, sh);
	new->i = i;
	return (new);
}

/*
**	Adds a new node of type t_lexer at the end of the list
*/
void	lexer_add_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*last_node;

	if (!(*lexer))
	{
		(*lexer) = new;
		return ;
	}
	last_node = (*lexer);
	if (last_node == new)
		return ;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new;
	new->prev = last_node;
}

/*
**	Creates the linked list of type t_lexer
** using the ui as a parameter
*/
t_lexer	*ft_lexer(char *ui, t_shell *sh)
{
	t_lexer	*lexer;
	char	*word;

	lexer = NULL;
	while (ui[sh->index->i])
	{
		if (is_space(ui[sh->index->i]))
			sh->index->i++;
		else
		{
			word_end_pos(ui, sh);
			word = ft_substr(ui, sh->index->i, sh->index->j - sh->index->i);
			lexer_add_back(&lexer, lexer_new(word, sh->index->k++, sh));
			sh->index->i = sh->index->j;
		}
	}
	return (lexer);
}
