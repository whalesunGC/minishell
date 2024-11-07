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

typedef struct s_redirect_single_command_params
{
	char		**av;
	t_list		*traverse;
	t_exec_node	*result;
	char		*command_path;
	pid_t		pid;
	int			ac;
	int			input_fd;
	int			output_fd;
	int			i;
	int			k;
}	t_redirect_single_command_params;

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

// single_commands_utils1 //
void	handle_redirections_file_opening(
			t_redirect_single_command_params *params);
void	handle_dup_and_closing_fd(t_redirect_single_command_params *params);
void	handle_execve_for_redirections(t_redirect_single_command_params *params,
			char ***env, char *input);
void	execute_child_process_for_redirections(
			t_redirect_single_command_params *params, char ***env, char *input);

// single_commands_utils2 //
void	child_process_without_redirects(
			t_redirect_single_command_params *params, char ***env, char *input);
int		checking_if_pipes_exist(t_list *node);
int		handle_fork_plus_executing_child(
			t_redirect_single_command_params *params, char ***env, char *input);
int		handle_single_commands(
			t_redirect_single_command_params *params, char ***env, char *input);

#endif
