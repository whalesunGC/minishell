/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:18:06 by apoh              #+#    #+#             */
/*   Updated: 2024/11/02 13:18:27 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_piping_single_command_params
{
	char		**av;
	t_list		*traverse;
	t_exec_node	*result;
	pid_t		pid;
	int			ac;
}	t_piping_single_command_params;

typedef struct s_piping_multiple_command_params
{
	t_list		*traverse;
	t_exec_node	*result;
	char		*command_path;
	int			**pipes;
	pid_t		pid;
	int			count;
	int			total;
	int			i;
	int			j;
}	t_piping_multiple_command_params;

void	execution(t_list *node, char ***env, char *input);
void	execution_with_pipes(t_list *node, char **env);

// multiple_commands_utils1 //
int		check_total_commands(t_list *node);
int		check_for_pipes(t_list *node);
int		**creating_new_pipes(int num_pipes);
int		setting_up_pipes(t_piping_multiple_command_params *params);

#endif
