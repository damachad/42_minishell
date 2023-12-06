/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:11 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/29 13:28:22 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Finds and hands the dollar sign
*/
int	find_dollar(t_shell *sh, int point, char *tmp, char **line)
{
	char	*key;
	char	*env_value;

	if (g_signo == 130)
		sh->exit_code = 130;
	if (tmp[1] == '?')
		return (expand_free(ft_itoa(sh->exit_code), point, point + 2, line));
	if (tmp[1])
	{
		sh->len = 1;
		while (ft_isalpha(tmp[sh->len]) || tmp[sh->len] == '_')
			sh->len++;
		sh->len += (ft_isalnum(tmp[sh->len]) > 0);
		while (sh->len > 2 && (ft_isalnum(tmp[sh->len]) || tmp[sh->len] == '_'))
			sh->len++;
		key = ft_substr(tmp, 1, sh->len - 1);
		env_value = get_env_value(sh, key);
		if (env_value)
			expand_valid_env(point, sh, env_value, line);
		else
			handle_invalid_env(point, sh->len, line);
		free(key);
		return (1);
	}
	return (0);
}

/*
**	Checks if there are open quotes
*/
int	check_quotes_str(const char *str, t_shell *sh)
{
	int		quotes;
	char	quote;

	quotes = 0;
	while (*str && (quotes % 2 == 0 || quotes == 0))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			quotes++;
			while (*str && *str != quote)
				str++;
			if (*str && *str == quote)
				quotes++;
		}
		if (*str)
			str++;
	}
	if (quotes % 2 != 0)
	{
		ft_putstr_fd("minishell: Open quote found.\n", 2);
		reset_loop(sh);
	}
	return (quotes);
}

/*
**	Searchs for the dollar sign outside single quotes
*/
void	env_expand_dollar(t_shell *sh, char *tmp, char **line)
{
	sh->index->dquote = 0;
	sh->index->squote = 0;
	while (*(++tmp))
	{
		if (*tmp == '"' && !sh->index->squote)
			sh->index->dquote = !sh->index->dquote;
		if (*tmp == '\'' && !sh->index->dquote)
			sh->index->squote = !sh->index->squote;
		if (*tmp == '$' && !ft_strchr(NOT_EXPRESSION, *(tmp + 1)) \
		&& !sh->index->squote && !((sh->index->dquote || sh->index->squote) \
		&& (*(tmp + 1) == '"' || *(tmp + 1) == '\'')))
		{
			if (find_dollar(sh, tmp - *line, tmp, line))
			{
				if (sh->index->j == -1)
					return ;
				tmp = *line - 1;
				sh->index->dquote = 0;
				sh->index->squote = 0;
			}
		}
	}
	check_quotes_str(*line, sh);
}

void	update_cmds(t_shell *sh, char *value, char **line)
{
	int		pos;
	char	**words;

	pos = -1;
	free(*line);
	words = ft_split(value, ' ');
	free(*sh->cmds);
	*sh->cmds = ft_calloc(ft_count_words(value) + 1, sizeof(char *));
	while (words[++pos])
		(*sh->cmds)[pos] = ft_strdup(words[pos]);
	free_matrix(words);
	sh->index->j = -1;
}
