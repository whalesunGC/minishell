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

// handling ctrl + c and ctrl + / //
void	handle_sigint(int signum);
void	setup_signal_handlers(void);

#endif 
