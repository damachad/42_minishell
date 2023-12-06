/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:39:06 by damachad          #+#    #+#             */
/*   Updated: 2023/11/29 13:21:14 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	This function writes the prompt in the terminal
*/
void	redisplay_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
**	This function sets program response to CTRL+C
*/
void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 130;
		redisplay_prompt();
	}
}

/*
**	Set the global variable g_signo to the signal number
*/
void	sighandler_child(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		g_signo = 128 + signo;
}

/*
**	This function resets the signals to their default behavior
*/
void	reset_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
