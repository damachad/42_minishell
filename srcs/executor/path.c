/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:03:01 by damachad          #+#    #+#             */
/*   Updated: 2023/11/29 09:31:54 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (1);
	}
	return (0);
}

char	*search_executable(char *cmd, char *path_env)
{
	char	*token;
	char	*full_path;
	char	*full_path2;

	token = ft_strtok(path_env, ":");
	while (token != NULL)
	{
		full_path = ft_strjoin(token, "/");
		full_path2 = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!access(full_path2, X_OK) && !access(full_path2, F_OK))
			return (full_path2);
		free(full_path2);
		token = ft_strtok(NULL, ":");
	}
	if (!access(cmd, X_OK) && !access(full_path2, F_OK))
		return (cmd);
	return (NULL);
}

char	*find_path(char *cmd, t_shell *sh)
{
	char	*path_env;
	char	*full_path;

	path_env = get_env_value(sh, "PATH");
	if (path_env == NULL)
		return (NULL);
	full_path = search_executable(cmd, path_env);
	free(path_env);
	return (full_path);
}

void	null_path(t_shell *sh, char **cmds)
{
	if (ft_strchr(cmds[0], '/') != NULL)
	{
		if (access(cmds[0], F_OK))
			h_cmd_not_exist(sh, cmds[0], 2, NULL);
		else if (access(cmds[0], X_OK))
			h_cmd_not_exist(sh, cmds[0], 13, NULL);
		else
			h_cmd_not_exist(sh, cmds[0], 2, NULL);
	}
	else if (cmds[0][0] == '=')
		handle_command_not_found(sh, cmds[0]);
	else if (ft_strchr(cmds[0] + 1, '=') != NULL)
		mini_clean(sh, 4);
	else
		handle_command_not_found(sh, cmds[0]);
}
