/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:11:27 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/28 16:55:16 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NOT SEND

#include "../includes/minishell.h"

void	print_env_value(t_shell *sh, char *key)
{
	t_envlst	*head;
	t_envlst	*current;

	head = sh->env_lst;
	current = sh->env_lst;
	while (current)
	{
		if (strn_strl_cmp(key, current->key) == true)
		{
			printf("%s", current->value);
			break ;
		}
		current = current->next;
	}
	sh->env_lst = head;
}

void	print_mini_envp(char **mini_envp)
{
	int	i;

	i = -1;
	while (mini_envp[++i])
		printf("%s\n", mini_envp[i]);
}

// Prints tree recursively (pre-order)
/*
void	print_tree(t_tree_node *root, int depth)
{
	int			i;
	t_tree_node	*tmp;

	i = -1;
	tmp = root;
	if (!tmp)
		return ;
	while (++i < depth)
		printf("__");
	if (tmp->type == PIPE)
		printf("Type: PIPE\n");
	else if (tmp->type == CMD)
		printf("Type: CMD\n");
	i = -1;
	if (tmp->cmd != NULL)
	{
		while (++i < depth)
			printf("__");
		printf("Command: ");
		i = 0;
		while (tmp->cmd[i] != NULL)
			printf("%s ", tmp->cmd[i++]);
		printf("\n");
	}
	if (tmp->in_redirs)
	{
		i = -1;
		while (++i < depth)
			printf("__");
		printf("in_redirs: ");
		while (tmp->in_redirs)
		{
			printf("operator: %d, filename: %s ", \
			tmp->in_redirs->operator, tmp->in_redirs->str);
			tmp->in_redirs = tmp->in_redirs->next;
		}
		printf("\n");
	}
	if (tmp->out_redirs)
	{
		i = -1;
		while (++i < depth)
			printf("__");
		printf("out_redirs: ");
		while (tmp->out_redirs)
		{
			printf("operator: %d, filename: %s ", \
			tmp->out_redirs->operator, tmp->out_redirs->str);
			tmp->out_redirs = tmp->out_redirs->next;
		}
		printf("\n");
	}
	print_tree(root->left, depth + 1);
	print_tree(root->right, depth + 1);
}
*/

// Print the lexer linked list's words
void	print_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (!tmp)
		printf("Lexer is empty\n");
	while (tmp)
	{
		printf("Operator : %d; Index: %d; String : (%s)\n", \
		tmp->operator, tmp->i, tmp->str);
		tmp = tmp->next;
	}
}
