/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:45:12 by fde-carv          #+#    #+#             */
/*   Updated: 2023/12/04 09:41:18 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_continue(t_shell *sh, t_tree_node *node)
{
	if (node->in_redirs)
		handle_input_redir(sh, node);
	if (node->out_redirs)
		handle_output_redir(sh, node);
	if (is_builtin_child(node->cmd))
	{
		sh->exit_code = builtin_router(sh, node->cmd);
		mini_clean(sh, sh->exit_code);
	}
	else if (node->cmd && node->cmd[0])
	{
		close_pipes(sh);
		execute_comm(sh, node->cmd);
	}
	mini_clean(sh, 0);
}

void	child_process(t_shell *sh, t_tree_node *node)
{
	signal(SIGINT, sighandler_child);
	signal(SIGQUIT, sighandler_child);
	if (is_builtin_parent(node->cmd))
	{
		close_pipes(sh);
		clear_shell(sh);
		exit(0);
	}
	if (node->cmd && sh->fd_in != STDIN_FILENO && check_comm(sh, node->cmd))
	{
		dup2(sh->fd_in, STDIN_FILENO);
		close(sh->fd_in);
	}
	if (node->cmd && sh->fd_out != STDOUT_FILENO && check_comm(sh, node->cmd))
	{
		dup2(sh->fd_out, STDOUT_FILENO);
		close(sh->fd_out);
	}
	child_continue(sh, node);
}

void	end_parent(t_shell *sh, int i)
{
	if (i == sh->nbr_commands - 1)
	{
		while (i-- >= 0)
			waitpid(0, NULL, 0);
	}
	delete_heredoc_list(sh);
	reset_signals();
}

void	parent_process(t_shell *sh, t_tree_node *node, int *status, int i)
{
	if (is_builtin_parent(node->cmd) && sh->nbr_commands == 1)
	{
		sh->exit_code = builtin_router(sh, node->cmd);
		close_pipes(sh);
		reset_signals();
		delete_heredoc_list(sh);
		reset_loop(sh);
	}
	else if (i == sh->nbr_commands - 1)
	{
		close_pipes(sh);
		waitpid(sh->pid, status, 0);
		set_exit_status(sh, *status);
	}
	if (sh->fd_in != STDIN_FILENO)
		close(sh->fd_in);
	if (i < sh->nbr_commands - 1)
		close(sh->pipes[i][1]);
	if (sh->nbr_commands > 1)
		sh->fd_in = sh->pipes[i][0];
}

// Call with last parameter as 0 and store head pointer
// of the parser before calling
// Caller recursive function for the execution of the commands
void	executor(t_shell *sh, t_tree_node *parser, int i)
{
	t_tree_node	*node;
	int			status;

	status = 0;
	node = parser;
	if (node->type == PIPE)
		node = parser->left;
	if (i == sh->nbr_commands - 1)
		sh->fd_out = STDOUT_FILENO;
	else
		sh->fd_out = sh->pipes[i][1];
	expander(&node->cmd, sh);
	signal(SIGINT, SIG_IGN);
	sh->pid = fork();
	if (sh->pid == 0)
		child_process(sh, node);
	else
	{
		parent_process(sh, node, &status, i);
		if (parser->type == PIPE)
			executor(sh, parser->right, ++i);
	}
	end_parent(sh, i);
}
