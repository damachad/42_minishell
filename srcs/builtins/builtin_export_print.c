/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:11:08 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/23 17:27:02 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Swaps the key and value of two env_lst nodes
*/
void	swap_env_nodes(t_envlst *a, t_envlst *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

/*
**  Sorts the env_lst alphabetically
*/
void	sort_env_lst(t_envlst *env_lst)
{
	int			swap;
	t_envlst	*temp;

	if (!env_lst || !env_lst->next)
		return ;
	while (1)
	{
		swap = 0;
		temp = env_lst;
		while (temp->next)
		{
			if (ft_strcmp(temp->key, temp->next->key) > 0)
			{
				swap_env_nodes(temp, temp->next);
				swap = 1;
			}
			temp = temp->next;
		}
		if (!swap)
			break ;
	}
}

/* 
**  Executes when there are no arguments
*/
void	print_export(t_shell *sh)
{
	t_envlst	*current;

	current = sh->env_lst;
	sort_env_lst(current);
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->key, 1);
		if (current->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}
