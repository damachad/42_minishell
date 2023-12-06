/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:22:48 by fde-carv          #+#    #+#             */
/*   Updated: 2023/12/04 09:47:48 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Changes the env value; If no key is found,
** or the key has no value, add new env node;
** If key has no value, set it to invisible in env_list
*/
void	export_change_value(t_shell *sh, char *key, char *value, int visible)
{
	t_envlst	*env_node;

	env_node = NULL;
	if (visible == 1 && ft_strcmp(key, "_") && \
	!change_env_value(sh, key, value))
	{
		env_node = ft_lstnew_env(key, value, 1);
		ft_lstadd_back_env(&sh->env_lst, env_node);
	}
	else if (!value && visible == 0 && ft_strcmp(key, "_"))
	{
		env_node = ft_lstnew_env(key, value, 0);
		ft_lstadd_back_env(&sh->env_lst, env_node);
	}
	else
	{
		free (key);
		free (value);
	}
}

/*
**	Checks if key starts with letter or '_' and
** contains only alfanumeric characters
*/
int	key_error(t_shell *sh, char *str)
{
	int		i;

	i = 0;
	if (!str || ft_strlen(str) == 0)
	{
		sh->exit_code = 1;
		error_4s("export: '", str, "': ", "not a valid identifier");
		return (1);
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		sh->exit_code = 1;
		error_4s("export: '", str, "': ", "not a valid identifier");
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			sh->exit_code = 1;
			return (error_3s(sh, "export: '", str, INVALID_ID));
		}
		i++;
	}
	return (0);
}

/*
**	Executes export when there is an argument
*/
int	do_export(t_shell *sh, char *cmd)
{
	char	*key;
	char	*value;

	if (key_error(sh, cmd) == 0)
	{
		key = get_key(cmd);
		value = get_value(cmd);
		if (ft_strchr(cmd, '='))
			export_change_value(sh, key, value, 1);
		else
			export_change_value(sh, key, value, 0);
		return (0);
	}
	return (1);
}

/*
**	Executes the export command checking if
** there are arguments or not
*/
int	builtin_export(t_shell *sh, char **cmds)
{
	int	i;
	int	e_code;

	i = 1;
	e_code = 0;
	if (ft_strlen_2d(cmds) == 1)
		print_export(sh);
	else
	{
		while (cmds[i])
		{
			e_code = do_export(sh, cmds[i]);
			i++;
		}
		update_mini_env(sh);
	}
	return (e_code);
}
