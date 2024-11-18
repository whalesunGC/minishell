/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:55:39 by apoh              #+#    #+#             */
/*   Updated: 2024/10/11 21:55:58 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

extern int	g_exit_status;

typedef struct s_signal_data
{
    t_list  *exec_data_head;
    int     exit_status;
}       t_signal_data;

// handling ctrl + c and ctrl + / //
void	handle_child_sigint(int signum);
void	handle_parent_sigint(int signum);
void	parent_signal_handlers(void);
void	ignore_parent_signals(void);
void	setup_signal_handlers_for_child(void);

#endif 
