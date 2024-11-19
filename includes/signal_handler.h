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

extern int	g_exit_status;

typedef enum e_process_type
{
	PARENT,
	CHILD,
}			t_process_type;

typedef struct s_signal_data
{
	t_list	*exec_data_head;
	int		exit_status;
	char	**env;
	char	*input;
	int		**pipes;
	int		pipe_count;
	char	*command_path;
	int		**heredocs_pipes;
	int		heredocs_count;
}		t_signal_data;

// signal.c
void	ft_signal(t_redirect_single_command_params *params_s,
			t_piping_multiple_command_params *params_m, char **env,
			t_process_type process_flag);
void	ft_free_signal(t_signal_data *data);
void	signal_cleanup(t_signal_data *data);

// handling ctrl + c and ctrl + / //
void	handle_child_sigint(int signum);
void	handle_parent_sigint(int signum);
void	parent_signal_handlers(void);
void	ignore_parent_signals(void);
void	setup_signal_handlers_for_child(void);

#endif 
