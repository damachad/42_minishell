/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:25:52 by damachad          #+#    #+#             */
/*   Updated: 2023/12/06 16:07:41 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Free the allocated memory for a lexer list
void	free_lexer_list(t_lexer *head)
{
	t_lexer	*current;
	t_lexer	*next;

	current = head;
	next = NULL;
	if (!head)
		return ;
	while (current)
	{
		next = current->next;
		if (current->str)
		{
			free(current->str);
			current->str = NULL;
		}
		free(current);
		current = next;
	}
}

// Free the allocated memory for a 2d array
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

// Free the allocated memory for a not-NULL-terminated 2d array
void	free_int_matrix(t_shell *sh)
{
	int	i;

	i = -1;
	if (sh == NULL || sh->pipes == NULL)
		return ;
	while (++i < sh->nbr_commands)
		free(sh->pipes[i]);
	free(sh->pipes);
}
