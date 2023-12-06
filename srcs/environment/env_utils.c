/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:52:32 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/23 15:02:55 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	This function frees the env_lst
*/
void	free_env_lst(t_envlst *env_lst)
{
	t_envlst	*temp;

	while (env_lst)
	{
		temp = env_lst;
		env_lst = env_lst->next;
		free(temp->key);
		temp->key = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
}

/*
**	This function free a node of the env_lst
*/
void	free_node_env(t_envlst *node)
{
	free(node->key);
	node->key = NULL;
	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
}

/*
**	This function frees all the nodes of the env_lst
*/
void	free_nodes_env(t_envlst **list)
{
	t_envlst	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	*list = NULL;
}

/*
**	Copy envp array into minishell structure 
** mini_envp uses malloc in strdup -> free at the end
*/
char	**copy_envp(char **envp)
{
	char	**mini_envp;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	mini_envp = ft_calloc(1, sizeof(char *) * (i + 1));
	if (!mini_envp)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		mini_envp[i] = ft_strdup(envp[i]);
		if (mini_envp[i] == NULL)
		{
			free_matrix(mini_envp);
			return (NULL);
		}
		i++;
	}
	return (mini_envp);
}

/*
**	This function adds a node at the end of the env_lst
*/
void	ft_lstadd_back_env(t_envlst **head, t_envlst *new_node)
{
	t_envlst	*last;

	if (!new_node)
	{
		free_nodes_env(head);
		return ;
	}
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new_node;
}
