/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:02:39 by damachad          #+#    #+#             */
/*   Updated: 2023/12/06 16:07:35 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	pipes_together(char *str)
{
	bool	found_pipe;
	int		i;

	found_pipe = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			if (found_pipe)
				return (true);
			found_pipe = true;
		}
		else if (is_space(str[i]))
			continue ;
		else
			found_pipe = false;
	}
	return (false);
}

void	open_pipes_child(t_shell *sh)
{
	g_signo = 0;
	signal(SIGINT, heredoc_handler);
	ft_bzero(sh->index, sizeof(t_index));
	herestr_child(sh);
}

bool	is_solo_pipe(char *str)
{
	return (((ft_strstr(str, "|") == str))
		&& (ft_strstr(ft_strstr(str, "|") + 1, "|") == NULL
			|| ft_strstr(ft_strstr(str, "|") + 1, "||") == NULL));
}

bool	consecutive_pipes(char *str)
{
	int	consecutive_pipes;
	int	i;

	consecutive_pipes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			consecutive_pipes++;
			if (consecutive_pipes > 1)
				return (true);
		}
		else
			consecutive_pipes = 0;
		i++;
	}
	return (false);
}

/*
** SYNOPSIS: locate a substring in a string
**
** DESCRIPTION:
** 		The strstr() function locates the first occurrence of the null-
**	terminated string s2 in the null-terminated string s1.
*/
char	*ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (needle[0] == '\0')
		return (haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0')
		{
			if (needle[j + 1] == '\0')
				return (&haystack[i]);
			j++;
		}
		i++;
	}
	return (0);
}
