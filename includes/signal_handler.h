/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:55:39 by apoh              #+#    #+#             */
/*   Updated: 2024/11/19 18:18:54 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include "execution.h"

typedef enum e_process_type
{
	PARENT,
	CHILD,
}			t_process_type;

// signal.c
void		ft_signal(t_redirect_single_command_params *params_s,
				t_piping_multiple_command_params *params_m, char **env,
				t_process_type process_flag);
void		ft_free_signal(t_sig_data *data);
void		signal_cleanup(t_sig_data *data);
void		signal_parent(int *exit_status);

// handling ctrl + c and ctrl + / //
void		handle_child_sigint(int signum);
void		handle_parent_sigint(int signum);
void		parent_signal_handlers(void);
void		ignore_parent_signals(void);
void		setup_signal_handlers_for_child(void);

//signal_utils.c
void		signal_parent(int *exit_status);
void		signal_cleanup(t_sig_data *data);
void		handle_cleanup_pipes(t_sig_data *data);

#endif
