/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:54:08 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/23 15:03:51 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Create new node and fill in key and value
*/
t_envlst	*ft_lstnew_env(char *key, char *value, int visible)
{
	t_envlst	*new_node;

	new_node = ft_calloc(1, sizeof(t_envlst));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->visible = visible;
	new_node->next = NULL;
	return (new_node);
}

/*
**	Get key variable from env 
** free after use
*/
char	*get_key(char *mini_env)
{
	char	*key;
	int		size;

	size = 0;
	while (mini_env[size])
	{
		if (mini_env[size] == '=')
			break ;
		size++;
	}
	key = ft_calloc(1, sizeof(char) * (size + 1));
	if (!key)
		return (NULL);
	ft_memcpy(key, mini_env, size);
	return (key);
}

/*
**	Get value variable from env 
** free after use
*/
char	*get_value(char *mini_env)
{
	char	*value;
	char	*equal_sign;
	int		size;

	equal_sign = ft_strchr(mini_env, '=');
	if (equal_sign)
	{
		size = ft_strlen(equal_sign + 1);
		value = ft_calloc(1, sizeof(char) * (size + 1));
		if (value)
		{
			ft_memcpy(value, equal_sign + 1, size);
			return (value);
		}
	}
	return (NULL);
}

/*
**	Create environmental variable list
** extract key and value variables 
** fill new node with key and value data
** add new node to the last node
*/
void	create_env_list(t_shell *sh)
{
	char		*key;
	char		*value;
	int			i;
	t_envlst	*env_node;

	i = 0;
	while (sh->mini_env[i])
	{
		key = get_key(sh->mini_env[i]);
		value = get_value(sh->mini_env[i]);
		if (key && value)
		{
			env_node = ft_lstnew_env(key, value, 1);
			ft_lstadd_back_env(&sh->env_lst, env_node);
		}
		i++;
	}
}
