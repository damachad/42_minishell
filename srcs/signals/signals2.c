/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:49:22 by damachad          #+#    #+#             */
/*   Updated: 2023/11/29 13:19:01 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exit_status(t_shell *sh, int status)
{
	g_signo = 0;
	if (WTERMSIG(status))
		sh->exit_code = 128 + WTERMSIG(status);
	else if (WEXITSTATUS(status) == 13 || WEXITSTATUS(status) == 20)
		sh->exit_code = 126;
	else if (WEXITSTATUS(status) == 3)
		sh->exit_code = 127;
	else if (WEXITSTATUS(status) == 1 || WEXITSTATUS(status) == 4)
		sh->exit_code = 1;
	else if (WEXITSTATUS(status) == 21)
		sh->exit_code = 126;
	else
		sh->exit_code = WEXITSTATUS(status);
	if (sh->exit_code == 130)
		write(1, "\n", 1);
	else if (sh->exit_code == 131)
		write(1, "Quit: (core dumped)\n", 20);
}

void	heredoc_handler(int signo)
{
	int	fd;

	fd = 0;
	if (signo == SIGINT)
	{
		g_signo = 130;
		fd = open(".nfs0000013f1dca2zx", O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd, 0);
		close(fd);
		ioctl(0, TIOCSTI, "\n");
	}
}
