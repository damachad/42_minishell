/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:56:29 by damachad          #+#    #+#             */
/*   Updated: 2023/11/28 17:37:13 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_command_not_found(t_shell *sh, const char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)command, 2);
	ft_putstr_fd(": command not found\n", 2);
	mini_clean(sh, 3);
}

void	handle_file_not_found(t_shell *sh, const char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	mini_clean(sh, 4);
}

void	h_cmd_not_exist(t_shell *sh, const char *cmd, int err_no, char *path)
{
	if (path)
		free(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(err_no), 2);
	ft_putstr_fd("\n", 2);
	if (err_no == 13)
		mini_clean(sh, 126);
	if (err_no == 2)
		mini_clean(sh, 127);
	mini_clean(sh, err_no);
}

// Creates all necessary pipes for the execution of the commands
void	create_pipes(t_shell *sh)
{
	int	i;

	i = 0;
	if (sh->nbr_commands > 1)
	{
		sh->pipes = ft_calloc(sh->nbr_commands, sizeof(int *));
		while (i < sh->nbr_commands)
		{
			sh->pipes[i] = malloc(sizeof(int) * 2);
			if (pipe(sh->pipes[i]) == -1)
			{
				perror("pipe_creation");
				exit(1);
			}
			i++;
		}
	}
}

// Closes all pipes created for the execution of the commands
void	close_pipes(t_shell *sh)
{
	int	i;

	i = -1;
	if (sh->nbr_commands > 1)
	{
		while (++i <= sh->nbr_commands - 1)
		{
			close(sh->pipes[i][0]);
			close(sh->pipes[i][1]);
		}
	}
}
