/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:37:00 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/27 17:20:40 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Executes the pdw command using the getcwd() function
*/
int	builtin_pwd(t_shell *sh)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		sh->exit_code = 1;
		error_4s("getcwd error: ", "", "", strerror(errno));
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	pwd = NULL;
	return (0);
}
