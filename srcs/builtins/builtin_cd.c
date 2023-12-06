/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:00:40 by fde-carv          #+#    #+#             */
/*   Updated: 2023/12/04 09:42:21 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Changes the current directory to
** the home directory when called
*/
int	change_to_home_tilde(t_shell *sh)
{
	char	*home;

	home = get_env_value(sh, "HOME");
	if (!home)
	{
		chdir(sh->home);
		change_env_value(sh, "PWD", sh->home);
	}
	else if (chdir(home) == -1)
	{
		sh->exit_code = errno;
		error_4s("cd: ", home, ": ", strerror(errno));
		return (errno);
	}
	else
		change_env_value(sh, "PWD", home);
	if (home)
		free(home);
	return (0);
}

/*
**	Changes the current directory to
** the home directory when called
*/
int	change_to_home(t_shell *sh)
{
	char	*home;

	home = get_env_value(sh, "HOME");
	if (chdir(home) == -1)
	{
		if (!home)
		{
			sh->exit_code = 1;
			error_4s("cd: ", "HOME not set", "", "");
			return (1);
		}
		else
		{
			sh->exit_code = 1;
			error_4s("cd: ", home, ": ", strerror(errno));
			return (1);
		}
	}
	else
		change_env_value(sh, "PWD", home);
	if (home)
		free(home);
	return (0);
}

/*
**	Checks if there are no arguments or the first argument is ~,
** if so, changes the current directory to the home directory,
** else, does nothing.
*/
bool	is_home(t_shell *sh, char **cmds)
{
	if (cmds && ft_strlen_2d(cmds) == 1)
	{
		change_to_home(sh);
		return (true);
	}
	if (cmds && strn_strl_cmp(cmds[1], "~"))
	{
		change_to_home_tilde(sh);
		return (true);
	}
	return (false);
}

/*
**	Updates the PWD env variable to the current directory
*/
int	update_env_pwd(t_shell *sh)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (!path)
	{
		sh->exit_code = errno;
		error_4s("getcwd error: ", "", "", strerror(errno));
		return (errno);
	}
	change_env_value(sh, "PWD", path);
	free(path);
	path = NULL;
	return (0);
}

/*
**	Executes the cd command when called,
** if there are no arguments or the single argument is '~',
** changes the current directory to the home directory,
** if there is one argument, changes the current directory to the argument,
** if there are more than one argument, returns an error.
*/
int	builtin_cd(t_shell *sh, char **cmds)
{
	char	*old_pwd;

	if (is_home(sh, cmds))
		return (0);
	if (ft_strlen_2d(cmds) > 2)
	{
		sh->exit_code = 1;
		error_4s("cd: ", "too many arguments", "", "");
		return (1);
	}
	else if (cmds[1][0] && chdir(cmds[1]) == -1)
	{
		error_4s("cd: ", cmds[1], ": ", strerror(errno));
		return (1);
	}
	else
	{
		old_pwd = get_env_value(sh, "PWD");
		change_env_value(sh, "OLDPWD", old_pwd);
		free(old_pwd);
		update_env_pwd(sh);
	}
	return (0);
}
