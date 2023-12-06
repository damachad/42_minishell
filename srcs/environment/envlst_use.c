/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:54:02 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/25 11:18:57 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Counts the number of nodes in the linked list
*/
int	ft_list_size_env(t_envlst *list)
{
	int	size;

	size = 0;
	while (list)
	{
		list = list->next;
		size++;
	}
	return (size);
}

/*
**	This function adds a variable to the array
*/
void	join_mini_env(t_envlst *env_lst, char **mini_env, int i)
{
	if (env_lst->visible)
	{
		mini_env[i] = ft_strjoin_gnl(mini_env[i], env_lst->key);
		if (env_lst->value)
		{
			mini_env[i] = ft_strjoin_gnl(mini_env[i], "=");
			mini_env[i] = ft_strjoin_gnl(mini_env[i], env_lst->value);
		}
	}
}

/*
**	Overwrite the env array in the main structure with data from 
** env linked list, ignore empty envs
*/
void	update_mini_env(t_shell *sh)
{
	t_envlst	*head;
	int			size;
	int			i;

	size = ft_list_size_env(sh->env_lst);
	if (sh->mini_env)
		free_matrix(sh->mini_env);
	if (!sh->env_lst)
	{
		sh->mini_env = NULL;
		return ;
	}
	sh->mini_env = ft_calloc(1, sizeof(char *) * (size + 1));
	head = sh->env_lst;
	i = 0;
	sh->mini_env[i] = NULL;
	while (sh->env_lst)
	{
		join_mini_env(sh->env_lst, sh->mini_env, i);
		i++;
		sh->env_lst = sh->env_lst->next;
	}
	sh->env_lst = head;
}

/* 
**	Returns string that contains the value of the key
** that is passed as a parameter
** free "value" after using, strdup uses malloc
*/
char	*get_env_value(t_shell *sh, char *key)
{
	t_envlst	*head;
	char		*value;

	head = sh->env_lst;
	value = NULL;
	while (sh->env_lst)
	{
		if (strn_strl_cmp(key, sh->env_lst->key) && sh->env_lst->visible)
		{
			value = ft_strdup(sh->env_lst->value);
			break ;
		}
		sh->env_lst = sh->env_lst->next;
	}
	sh->env_lst = head;
	return (value);
}

/*
**	Changes the value of the requested key
*/
int	change_env_value(t_shell *sh, char *key, char *new_value)
{
	t_envlst	*head;

	head = sh->env_lst;
	while (sh->env_lst)
	{
		if (strn_strl_cmp(key, sh->env_lst->key))
		{
			free(sh->env_lst->value);
			sh->env_lst->value = ft_strdup(new_value);
			sh->env_lst->visible = 1;
			sh->env_lst = head;
			update_mini_env(sh);
			return (1);
		}
		sh->env_lst = sh->env_lst->next;
	}
	sh->env_lst = head;
	return (0);
}
