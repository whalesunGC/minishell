/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:53:20 by apoh              #+#    #+#             */
/*   Updated: 2024/11/01 19:58:46 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

/**
 * @function: handle_child_sigint
 * @brief: handle ctrl + c in child process
 * 
 * @param signum : this is the prototype, but variable not used
 * 
 * @return: void function
 */
void	handle_child_sigint(int signum)
{
	ft_dprintf(2, "entering child signal cleanup\n");
	signal_cleanup(NULL);
	(void)signum;
	exit(130);
}

/**
 * @function: handle_parent_sigint
 * @brief: handling ctrl + c in parent process
 * 
 * @param signum: this is the prototype, but variable not used
 * 
 * @return: void function
 */
void	handle_parent_sigint(int signum)
{
	(void)signum;
	signal_parent(NULL);
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf("\n");
	rl_redisplay();
}

/**
 * @function: parent_signal_handlers
 * @brief: setting up ctrl + c and ignoring ctrl + \
 	in parent process
 * 
 * @param void
 * 
 * @return: void function
 */
void	parent_signal_handlers(void)
{
	struct sigaction	signal_int;
	struct sigaction	signal_quit;

	ft_memset(&signal_int, 0, sizeof(signal_int));
	signal_int.sa_handler = handle_parent_sigint;
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

/**
 * @function: ignore_parent_signals
 * @brief: ignoring the signals in the parent process
 	while the child process is being run
 * 
 * @param void
 * 
 * @return: void function
 */
void	ignore_parent_signals(void)
{
	struct sigaction	signal_int;
	struct sigaction	signal_quit;

	ft_memset(&signal_int, 0, sizeof(signal_int));
	signal_int.sa_handler = SIG_IGN;
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

/**
 * @function: setup_signal_handlers_for_child
 * @brief: setting up of signal handler for child process
 * 
 * @param void
 * 
 * @return: void function
 */
void	setup_signal_handlers_for_child(void)
{
	struct sigaction	signal_child;
	struct sigaction	signal_quit;

	ft_memset(&signal_child, 0, sizeof(signal_child));
	signal_child.sa_handler = handle_child_sigint;
	sigemptyset(&signal_child.sa_mask);
	if (sigaction(SIGINT, &signal_child, NULL) == -1)
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
