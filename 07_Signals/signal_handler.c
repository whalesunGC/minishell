/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:49:29 by apoh              #+#    #+#             */
/*   Updated: 2024/10/14 16:49:34 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_sigint
 * @brief: handling the signal ctrl + c
 * 
 * @param signum: this is the prototype, but the variable is not used.
 * 
 * @return: void function
 */

void	handle_sigint(int signum)

{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf("\n");
	g_exit_status = 130;
	rl_redisplay();
}

/**
 * @function: setup_signal_handlers
 * @brief: setting up ctrl + c and ignoring ctrl + \
 * 
 * @param void
 * 
 * @return: void function
 */

void	setup_signal_handlers(void)

{
	struct sigaction	signal_int;
	struct sigaction	signal_quit;

	ft_memset(&signal_int, 0, sizeof(signal_int));
	signal_int.sa_handler = handle_sigint;
	sigemptyset(&signal_int.sa_mask);
	if (sigaction(SIGINT, &signal_int, NULL) == -1)
	{
		perror("Sigaction failed for SIGINT ");
		exit(EXIT_FAILURE);
	}
	ft_memset(&signal_quit, 0, sizeof(signal_quit));
	signal_quit.sa_handler = SIG_IGN;
	sigemptyset(&signal_quit.sa_mask);
	if (sigaction(SIGQUIT, &signal_quit, NULL) == -1)
	{
		perror("Sigaction failed for SIGQUIT ");
		exit(EXIT_FAILURE);
	}
}
