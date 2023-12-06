/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:24:55 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/27 17:16:01 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_line(t_shell *sh)
{
	write(1, "exit\n", 5);
	rl_clear_history();
	clear_shell(sh);
	exit(sh->exit_code);
}

void	line_empty_test(t_shell *sh)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strtrim(sh->ui, SPACES);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		reset_loop(sh);
	}
	free(tmp);
}

/*
**	Searches and returns the value of the HOME variable
*/
char	*get_pwd(t_shell *sh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		sh->exit_code = 1;
		error_4s("getcwd error: ", "", "", strerror(errno));
	}
	return (pwd);
}

/*
**	If there is no HOME variable, the prompt
** will be the full pwd
*/
char	*if_no_home(char *prompt, char *pwd)
{
	prompt = ft_strjoin_gnl(prompt, MINISHELL);
	prompt = ft_strjoin_gnl(prompt, pwd);
	prompt = ft_strjoin_gnl(prompt, "$ ");
	return (prompt);
}

/*
**	Returns the prompt with the
** path of the current directory
*/
char	*get_prompt(t_shell *sh)
{
	char	*prompt;
	char	*pwd;
	char	*home;

	prompt = NULL;
	pwd = get_pwd(sh);
	home = get_env_value(sh, "HOME");
	if (!home)
	{
		prompt = if_no_home(prompt, pwd);
		free(pwd);
		return (prompt);
	}
	prompt = ft_strjoin_gnl(prompt, MINISHELL);
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0 && home)
	{
		prompt = ft_strjoin_gnl(prompt, "~");
		prompt = ft_strjoin_gnl(prompt, pwd + ft_strlen(home));
	}
	else
		prompt = ft_strjoin_gnl(prompt, pwd);
	prompt = ft_strjoin_gnl(prompt, "$ ");
	free(pwd);
	free(home);
	return (prompt);
}
