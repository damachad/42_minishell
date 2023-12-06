/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:42:16 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:59:38 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Save heredoc file information in the tree
*/
void	handle_heredoc(t_shell *sh, t_lexer **in_redirs)
{
	t_lexer		*tmp;

	tmp = sh->heredoc_fd;
	sh->heredoc_fd = sh->heredoc_fd->next;
	tmp->next = NULL;
	lexer_add_back(in_redirs, tmp);
}

/*
**	Assistant of rm_in_redir() function
*/
void	handle_in_redirs(t_lexer **redirs, t_lexer *tmp, int i, t_shell *sh)
{
	t_lexer	*new;

	new = lexer_new(ft_strdup(tmp->next->str), i, sh);
	new->operator = tmp->operator;
	lexer_add_back(redirs, new);
}

/*
**	Removes input redirections from lexer linked list
** and creates a new linked list (type t_lexer)
*/
void	rm_in_redir(t_lexer **start, t_lexer *end, t_lexer **in, t_shell *sh)
{
	int		i;
	t_lexer	*tmp;
	t_lexer	*tmp_to_delete;

	i = 0;
	tmp = *start;
	while (tmp && tmp->next && tmp != end)
	{
		if (tmp->next && (tmp->operator == LESS))
			handle_in_redirs(in, tmp, i++, sh);
		else if (tmp->next && (tmp->operator == DOU_LESS))
			handle_heredoc(sh, in);
		if (tmp->operator == LESS || tmp->operator == DOU_LESS)
		{
			tmp_to_delete = tmp;
			tmp = tmp->next->next;
			lexer_deltwo(start, tmp_to_delete->i);
		}
		if (tmp && tmp->next && tmp->operator < LESS && tmp != end)
			tmp = tmp->next;
	}
}

/*
**	Removes output redirections from lexer linked list
** and creates a new linked list (type t_lexer)
*/
void	rm_out_redir(t_lexer **start, t_lexer *end, t_lexer **out, t_shell *sh)
{
	int		i;
	t_lexer	*tmp;
	t_lexer	*tmp_to_delete;
	t_lexer	*new_o_redir;

	i = 0;
	tmp = *start;
	while (tmp != end)
	{
		if (tmp->next && (tmp->operator == GREAT || tmp->operator == DOU_GREAT))
		{
			new_o_redir = lexer_new(ft_strdup(tmp->next->str), i++, sh);
			new_o_redir->operator = tmp->operator;
			lexer_add_back(out, new_o_redir);
			tmp_to_delete = tmp;
			tmp = tmp->next->next;
			lexer_deltwo(start, tmp_to_delete->i);
			if (!tmp)
				break ;
		}
		else if (tmp != end)
			tmp = tmp->next;
	}
}

/*
**	Creates a tree node of type CMD that contains a 
** linked list of redirections and a char ** of arguments
*/
t_tree_node	*command_node(t_lexer **start, t_lexer *end, t_shell *sh)
{
	t_tree_node	*cmd_node;

	cmd_node = ft_calloc(1, sizeof(t_tree_node));
	cmd_node->type = CMD;
	rm_in_redir(start, end, &(cmd_node->in_redirs), sh);
	rm_out_redir(start, end, &(cmd_node->out_redirs), sh);
	if (*start != end)
		list_to_array(*start, end, &(cmd_node->cmd));
	return (cmd_node);
}
