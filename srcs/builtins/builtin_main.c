/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:58:35 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/27 17:18:01 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* compare two strings by content and by length 
* returns "true" if strings are equal */
bool	strn_strl_cmp(char *s1, char *s2)
{
	if (!s1)
		return (false);
	if (!ft_strncmp(s1, s2, ft_strlen(s2)) && ft_strlen(s1) == ft_strlen(s2))
		return (true);
	return (false);
}

/*
**	This function checks if the command is a builtin
** that doesn't change the environment
*/
bool	is_builtin_child(char **cmds)
{
	if (!cmds || !cmds[0])
		return (false);
	if (strn_strl_cmp(cmds[0], "echo"))
		return (true);
	if (strn_strl_cmp(cmds[0], "env"))
		return (true);
	if (strn_strl_cmp(cmds[0], "pwd"))
		return (true);
	if (strn_strl_cmp(cmds[0], "export") && !cmds[1])
		return (true);
	return (false);
}

/*
**	This function checks if the command is a buildin
** that changes the environment
*/
bool	is_builtin_parent(char **cmds)
{
	if (!cmds || !cmds[0])
		return (false);
	if (strn_strl_cmp(cmds[0], "cd"))
		return (true);
	if (strn_strl_cmp(cmds[0], "exit"))
		return (true);
	if (strn_strl_cmp(cmds[0], "unset"))
		return (true);
	if (strn_strl_cmp(cmds[0], "export") && cmds[1])
		return (true);
	return (false);
}

/*
**	This function searches and executes
** the builtin command
*/
int	builtin_router(t_shell *sh, char **cmds)
{
	if (strn_strl_cmp(cmds[0], "cd"))
		return (builtin_cd(sh, cmds));
	if (strn_strl_cmp(cmds[0], "echo"))
		return (builtin_echo(cmds));
	if (strn_strl_cmp(cmds[0], "env"))
		return (builtin_env(sh, cmds));
	if (strn_strl_cmp(cmds[0], "exit"))
		builtin_exit(sh, cmds);
	if (strn_strl_cmp(cmds[0], "export"))
		return (builtin_export(sh, cmds));
	if (strn_strl_cmp(cmds[0], "pwd"))
		return (builtin_pwd(sh));
	if (strn_strl_cmp(cmds[0], "unset"))
		return (builtin_unset(sh, cmds));
	return (0);
}
