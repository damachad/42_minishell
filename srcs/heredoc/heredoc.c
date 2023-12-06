/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:59:19 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 15:25:58 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	Create a new t_lexer node for the heredoc
t_lexer	*ft_heredoc_new(char *limiter)
{
	t_lexer	*heredoc_node;

	heredoc_node = ft_calloc(1, sizeof(t_lexer));
	heredoc_node->eof = limiter;
	heredoc_node->operator = DOU_LESS;
	return (heredoc_node);
}

//	Remove the quotes from the heredoc delimiter
void	remove_quotes_heredoc(char *str)
{
	char	quote;
	int		i;
	int		len;

	quote = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
		{
			quote = str[i];
			ft_memmove(str + i, str + i + 1, (len - i));
			len--;
		}
		else if (quote && str[i] == quote)
		{
			quote = 0;
			ft_memmove(str + i, str + i + 1, (len - i));
			len--;
		}
		else
			i++;
	}
}

//	Caller function to check and create heredoc temp files
void	heredoc_check(t_lexer *lexer, t_shell *sh)
{
	t_lexer	*tmp_lexer;
	t_lexer	*temp;

	temp = NULL;
	tmp_lexer = lexer;
	sh->files = ft_calloc(2, sizeof(char));
	sh->files[0] = '.';
	while (tmp_lexer && tmp_lexer->next)
	{
		if (tmp_lexer->operator == DOU_LESS)
		{
			sh->here_quotes_eof = 0;
			sh->files = ft_strjoin_gnl(sh->files, "a");
			check_quotes_str(tmp_lexer->next->str, sh);
			if (ft_strchr(tmp_lexer->next->str, '"') \
			|| ft_strchr(tmp_lexer->next->str, '\''))
				sh->here_quotes_eof = 1;
			remove_quotes_heredoc(tmp_lexer->next->str);
			temp = ft_heredoc_new(tmp_lexer->next->str);
			temp->str = ft_strdup(sh->files);
			lexer_add_back(&sh->heredoc_fd, temp);
			heredoc_maker(temp, sh);
		}
		tmp_lexer = tmp_lexer->next;
	}
}
