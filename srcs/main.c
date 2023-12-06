/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:23:07 by damachad          #+#    #+#             */
/*   Updated: 2023/12/06 16:21:03 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//global variable for signals
int	g_signo;

// Initializes variables in sh struct
void	shell_init(t_shell *sh, char **envp)
{
	char	*home;

	ft_bzero(sh, sizeof(t_shell));
	sh->mini_env = copy_envp(envp);
	create_env_list(sh);
	home = get_env_value(sh, "HOME");
	sh->home = ft_strdup(home);
	free(home);
	sh->index = malloc(sizeof(t_index));
	ft_bzero(sh->index, sizeof(t_index));
	sh->fd_out = STDOUT_FILENO;
	sh->nbr_commands = 1;
}

void	set_nulls(t_shell *sh)
{
	sh->ui = NULL;
	sh->lexer = NULL;
	sh->parser = NULL;
	sh->prompt = NULL;
	sh->pipes = NULL;
	sh->files = NULL;
	sh->cmds = NULL;
}

// Frees resourses and calls ft_loop
void	reset_loop(t_shell *sh)
{
	if (sh->ui)
		free(sh->ui);
	if (sh->lexer)
		free_lexer_list(sh->lexer);
	if (sh->parser)
		free_parser_tree(sh->parser);
	if (sh->prompt)
		free(sh->prompt);
	if (sh->pipes)
		free_int_matrix(sh);
	if (sh->files)
		free(sh->files);
	ft_bzero(sh->index, sizeof(t_index));
	set_nulls(sh);
	sh->nbr_commands = 1;
	sh->fd_in = STDIN_FILENO;
	sh->fd_out = STDOUT_FILENO;
	ft_loop(sh);
}

void	ft_loop(t_shell *sh)
{
	sh->prompt = get_prompt(sh);
	sh->ui = readline(sh->prompt);
	if (!sh->ui)
		empty_line(sh);
	line_empty_test(sh);
	add_history(sh->ui);
	open_pipe(sh);
	space_pipes(sh, sh->ui - 1);
	sh->lexer = ft_lexer(sh->ui, sh);
	if (!sh->lexer)
		reset_loop(sh);
	if (is_syntax_correct(sh->lexer))
	{
		ft_putstr_fd(UNEXPECTED_TOK, 2);
		sh->exit_code = is_syntax_correct(sh->lexer);
		reset_loop(sh);
	}
	heredoc_check(sh->lexer, sh);
	sh->parser = build_tree(&(sh->lexer), sh);
	create_pipes(sh);
	executor(sh, sh->parser, 0);
	close_pipes(sh);
	reset_loop(sh);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("minishell cannot receive arguments\n", 2);
		exit(1);
	}
	if (envp[0] == NULL)
	{
		ft_putstr_fd("environment is empty\n", 2);
		return (2);
	}
	shell_init(&sh, envp);
	reset_signals();
	ft_loop(&sh);
}
