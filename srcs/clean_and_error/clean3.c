/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:35:38 by damachad          #+#    #+#             */
/*   Updated: 2023/11/27 15:35:18 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Delete the heredoc temporary files
void	delete_heredoc_list(t_shell *sh)
{
	char	*file;
	int		i;

	i = 0;
	file = ft_calloc(2, sizeof(char));
	file[0] = '.';
	file = ft_strjoin_gnl(file, "a");
	while (!access(file, R_OK) && i++ < sh->n_heredocs)
	{
		unlink(file);
		file = ft_strjoin_gnl(file, "a");
	}
	free(file);
}

// Free the allocated memory for the parser tree
void	free_parser_tree(t_tree_node *root)
{
	if (!root)
		return ;
	if (root->cmd && root->cmd[0])
		free_matrix(root->cmd);
	root->cmd = NULL;
	if (root->in_redirs)
		free_lexer_list(root->in_redirs);
	root->in_redirs = NULL;
	if (root->out_redirs)
		free_lexer_list(root->out_redirs);
	root->out_redirs = NULL;
	free_parser_tree(root->left);
	free_parser_tree(root->right);
	free(root);
}

// Free the allocated memory for a lexer list, in reverse order
void	free_lexer_list_rev(t_lexer **tail)
{
	t_lexer	*current;
	t_lexer	*prev;

	current = *tail;
	prev = NULL;
	if (!tail)
		return ;
	while (current)
	{
		prev = current->prev;
		if (current->str)
		{
			free(current->str);
			current->str = NULL;
		}
		free(current);
		current = prev;
	}
	*tail = NULL;
}

// Close fds, free memory and exit
void	mini_clean(t_shell *sh, int exit_code)
{
	close(sh->fd_in);
	close(sh->fd_out);
	close(0);
	close(1);
	close_pipes(sh);
	clear_shell(sh);
	exit(exit_code);
}

void	handle_empty_line_herestr(t_shell *sh, int fd)
{
	printf("%s\nexit\n", UNEXPECTED_EOF);
	close(fd);
	clear_shell(sh);
	exit(3);
}
