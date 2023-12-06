/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:26:59 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 11:36:43 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	Returns size of linked list (excluding end node)
*/
int	list_len(t_lexer *start, t_lexer *end)
{
	int	i;

	i = 0;
	if (!start)
		return (0);
	while (start != end)
	{
		i++;
		start = start->next;
	}
	return (i);
}

/*
**	Copies command arguments from linked 
** list to char ** from tree node
*/
void	list_to_array(t_lexer *start, t_lexer *end, char ***cmd)
{
	int		i;

	i = 0;
	if (!start || start->operator == PIPE || start == end)
	{
		*cmd = ft_calloc(1, sizeof(char *));
		return ;
	}
	*cmd = ft_calloc(list_len(start, end) + 1, sizeof(char *));
	while (start != end)
	{
		(*cmd)[i++] = ft_strdup(start->str);
		start = start->next;
	}
}

/*
**	Creates a tree node of type PIPE
*/
t_tree_node	*pipe_node(void)
{
	t_tree_node	*pipe_node;

	pipe_node = ft_calloc(1, sizeof(t_tree_node));
	pipe_node->type = PIPE;
	return (pipe_node);
}

/*
**	Scans the linked list for a pipe operator
** and returns that node (if it exists)
*/
t_lexer	*search_pipe(t_lexer *start)
{
	while (start && start->operator != PIPE)
		start = start->next;
	return (start);
}

/*
**	Builds parse tree recursively and returns root pointer
*/
t_tree_node	*build_tree(t_lexer **start, t_shell *sh)
{
	t_tree_node	*root;
	t_lexer		*pipe;

	root = NULL;
	if (!*start)
		return (NULL);
	pipe = search_pipe(*start);
	if (pipe)
	{
		root = pipe_node();
		root->left = command_node(start, pipe, sh);
		root->right = build_tree(&(pipe->next), sh);
	}
	else
		root = command_node(start, NULL, sh);
	return (root);
}
