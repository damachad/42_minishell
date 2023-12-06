/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:14:23 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/24 18:11:50 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	remove_nulls(char **cmds, int nbr_cmds)
{
	int	i;
	int	j;
	int	nulls;

	nulls = nbr_cmds;
	i = 0;
	j = 0;
	while (i < nbr_cmds)
	{
		if (cmds[i] != NULL)
		{
			cmds[j++] = cmds[i];
			nulls--;
		}
		i++;
	}
	cmds[j] = NULL;
	return (nulls);
}

/*
**	This function expands the commands
** replacing "line" with the "key".
** It starts replacing at "i" and ends at "j"
*/
int	expand_cmds(char *value, int start, int end, char **line)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(*line, 0, start);
	tmp2 = ft_substr(*line, end, ft_strlen(*line) - end + 1);
	free(*line);
	*line = ft_strjoin_gnl(tmp, value);
	*line = ft_strjoin_gnl(*line, tmp2);
	free(tmp2);
	return (1);
}

/*
**	Expands an invalid env, replacing it with ""
*/
void	handle_invalid_env(int point, int len, char **line)
{
	char	*env_value;

	env_value = "\0";
	expand_cmds(env_value, point, point + len, line);
}

/*
**	Expands an existing env, expanding it with the value
*/
void	expand_valid_env(int beg, t_shell *sh, char *env_value, char **line)
{
	char	*tmp;

	tmp = ft_substr(*line, beg + sh->len, ft_strlen(*line) - beg + sh->len + 1);
	if (sh->index->dquote)
		expand_cmds(env_value, beg, beg + sh->len, line);
	else if (ft_count_words(env_value) > 1 && !beg && !tmp[0] && \
	ft_strlen_2d(*sh->cmds) == 1)
		update_cmds(sh, trim_spaces(sh, env_value), line);
	else
		expand_cmds(trim_spaces(sh, env_value), beg, beg + sh->len, line);
	free(tmp);
	free(env_value);
}

/*
**  Does the same as expand_cmds, but also frees the key
*/
int	expand_free(char *key, int i, int j, char **line)
{
	expand_cmds(key, i, j, line);
	free(key);
	return (1);
}
