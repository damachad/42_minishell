/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-carv <fde-carv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:02:38 by damachad          #+#    #+#             */
/*   Updated: 2023/11/30 17:29:18 by fde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	just_pipe(t_shell *sh, char *str)
{
	char	*no_spaces;

	if (!str)
		return ;
	no_spaces = ft_strtrim(str, SPACES);
	if (no_spaces[0] == '|')
	{
		printf("%s", UNEXPECTED_TOK);
		free(str);
		sh->exit_code = 2;
		reset_loop(sh);
	}
	free(no_spaces);
}

bool	is_empty_line(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (!str[i])
		return (true);
	return (false);
}

void	herestr_child(t_shell *sh)
{
	int		fd;
	char	*line;

	fd = open(".tempstr", O_RDWR | O_CREAT, 0644);
	line = readline("> ");
	if (!line && g_signo != 130)
		handle_empty_line_herestr(sh, fd);
	while (g_signo != 130 && is_empty_line(line))
	{
		free(line);
		line = readline("> ");
		if (!line && g_signo != 130)
			handle_empty_line_herestr(sh, fd);
	}
	if (g_signo != 130)
		ft_putstr_fd(line, fd);
	free(line);
	close(fd);
	close(0);
	unlink(".nfs0000013f1dca2zx");
	clear_shell(sh);
	if (g_signo == 130)
		exit(2);
	exit(0);
}

int	herestr_parent(t_shell *sh, pid_t pid)
{
	int		fd;
	int		status;
	char	*tempstr;

	tempstr = NULL;
	waitpid(pid, &status, 0);
	reset_signals();
	if (status == 512)
	{
		write(1, "\n", 1);
		sh->exit_code = 130;
		unlink(".tempstr");
		reset_loop(sh);
	}
	fd = open(".tempstr", O_RDWR);
	tempstr = get_next_line(fd);
	close(fd);
	unlink(".tempstr");
	just_pipe(sh, tempstr);
	if (WEXITSTATUS(status) != 3)
		sh->ui = ft_strjoin_gnl(sh->ui, tempstr);
	free(tempstr);
	return (status);
}

char	*open_pipe(t_shell *sh)
{
	char	*temp;
	pid_t	pid;

	temp = ft_strtrim(sh->ui, SPACES);
	if ((pipes_together(temp) || consecutive_pipes(temp)) || is_solo_pipe(temp))
		return (sh->ui);
	while (temp[ft_strlen(temp) - 1] == '|')
	{
		free(temp);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			open_pipes_child(sh);
		else if (herestr_parent(sh, pid) == 768)
		{
			clear_shell(sh);
			exit(2);
		}
		temp = ft_strtrim(sh->ui, SPACES);
	}
	free(temp);
	return (sh->ui);
}
