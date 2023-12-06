/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:48:02 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/27 17:09:37 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Prints all the env variables that contain a value
*/
void	print_env_list(t_shell *sh)
{
	t_envlst	*current;

	current = sh->env_lst;
	while (current)
	{
		if (current->visible)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

/*
**	Executes the env command
*/
int	builtin_env(t_shell *sh, char **cmds)
{
	if (ft_strlen_2d(cmds) > 1)
	{
		sh->exit_code = 127;
		return (error_3s(sh, "env: '", cmds[1], "': No such" \
		"file or directory"));
	}
	else
		print_env_list(sh);
	return (0);
}
