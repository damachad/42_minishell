/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:45:12 by fde-carv          #+#    #+#             */
/*   Updated: 2023/11/28 17:40:50 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Gets the str until the delimiter is found "token", putting a '\0' 
in its place and storing a pointer to the position after this '\0' */
char	*ft_strtok(char *str, char *delimiter)
{
	static char	*next_token = NULL;
	char		*token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL || *next_token == '\0')
		return (NULL);
	while (*next_token != '\0' && ft_strchr(delimiter, *next_token) != NULL)
		next_token++;
	if (*next_token == '\0')
		return (NULL);
	token = next_token;
	while (*next_token != '\0' && ft_strchr(delimiter, *next_token) == NULL)
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}

/* Checks if command is valid */
bool	check_comm(t_shell *sh, char **cmds)
{
	char	*path;

	path = NULL;
	if (ft_strcmp(cmds[0], "export") == 0)
		return (true);
	if (is_absolute_path(cmds[0]))
	{
		path = ft_strdup(cmds[0]);
		if (chdir(cmds[0]) == 0)
			h_cmd_not_exist(sh, cmds[0], 21, path);
	}
	else if (cmds[0][0])
		path = find_path(cmds[0], sh);
	if (!path)
		return (false);
	else
		free(path);
	return (true);
}

/* Get path, test it and execute */
void	execute_comm(t_shell *sh, char **cmds)
{
	char	*path;

	path = NULL;
	if (is_absolute_path(cmds[0]))
	{
		path = ft_strdup(cmds[0]);
		if (chdir(cmds[0]) == 0)
			h_cmd_not_exist(sh, cmds[0], 21, path);
	}
	else if (cmds[0][0])
		path = find_path(cmds[0], sh);
	if (path == NULL)
		null_path(sh, cmds);
	execve(path, cmds, sh->mini_env);
	ft_putstr_fd("minishell: execve", 2);
	mini_clean(sh, 1);
}

/* Sets output to a file */
void	handle_output_redir(t_shell *sh, t_tree_node *node)
{
	t_lexer	*temp;

	temp = node->out_redirs;
	while (temp)
	{
		remove_quotes_heredoc(temp->str);
		if (!access(temp->str, F_OK) && access(temp->str, W_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(temp->str, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			mini_clean(sh, 1);
		}
		if (temp->operator == DOU_GREAT)
			sh->fd_out = open(temp->str, O_WRONLY \
			| O_CREAT | O_APPEND, 0644);
		else
			sh->fd_out = open(temp->str, O_WRONLY \
			| O_CREAT | O_TRUNC, 0644);
		if (node->cmd && check_comm(sh, node->cmd))
			dup2(sh->fd_out, STDOUT_FILENO);
		close(sh->fd_out);
		temp = temp->next;
	}
}

/* Sets input from a file */
void	handle_input_redir(t_shell *sh, t_tree_node *node)
{
	t_lexer	*temp;

	temp = node->in_redirs;
	while (node->in_redirs)
	{
		remove_quotes_heredoc(node->in_redirs->str);
		if (access(node->in_redirs->str, R_OK))
			handle_file_not_found(sh, node->in_redirs->str);
		sh->fd_in = open(node->in_redirs->str, O_RDONLY);
		if (node->cmd && check_comm(sh, node->cmd))
			dup2(sh->fd_in, STDIN_FILENO);
		close(sh->fd_in);
		node->in_redirs = node->in_redirs->next;
	}
	node->in_redirs = temp;
}
