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

typedef struct s_sig_data
{
	t_list	*exec_data_head;
	char	**env;
	char	*input;
	int		**pipes;
	int		pipe_count;
	char	*command_path;
	int		**heredocs_pipes;
	int		heredocs_count;
	char	*input1;
	int		*exit_status;
	int		z;
}		t_sig_data;

typedef struct s_redirect_single_command_params
{
	char		**av;
	int			**pipes;
	t_list		*exec_data_head;
	t_sig_data	*signal_data;
	int			*exit_status;
	t_list		*traverse;
	t_exec_node	*result;
	char		*command_path;
	char		*input1;
	pid_t		pid;
	int			ac;
	int			input_fd;
	int			output_fd;
	int			i;
	int			k;
	int			x;
	int			y;
	int			z;
	int			a;
	int			b;
	int			delimiter_counter;
	int			rd_arg_counter;
	int			pipe_count;
	int			count;
	int			loop_counter;
}	t_redirect_single_command_params;

typedef struct s_piping_multiple_command_params
{
	char		**av;
	int			**pipes;
	int			**heredocs_pipes;
	t_list		*traverse;
	t_exec_node	*result;
	t_list		*exec_data_head;
	t_sig_data	*signal_data;
	int			*exit_status;
	char		*command_path;
	char		*input1;
	pid_t		pid;
	int			ac;
	int			count;
	int			heredocs_count;
	int			total;
	int			i;
	int			j;
	int			x;
	int			z;
	int			a;
	int			b;
	int			rd_arg_counter;
	int			delimiter_counter;
	int			heredocs_pipe_number;
	int			heredocs_pipe_index;
	int			input_fd;
	int			output_fd;
	int			flag;
}	t_piping_multiple_command_params;

// multiple_command.c //
void	execution_with_pipes(t_list *node, char ***env, int *exit_status);

// multiple_commands_utils1 //
int		check_for_pipes(t_list *node);
int		check_total_commands(t_list *node);
int		**creating_new_pipes(int num_pipes);
int		setting_up_pipes(t_piping_multiple_command_params *params);
void	searching_for_heredocs(
			t_piping_multiple_command_params *params, t_list *node);

// multiple_commands_utils2 //
int		**creating_heredocs_pipes(int heredocs_count);
int		setting_up_heredocs_pipes(t_piping_multiple_command_params *params);

// multiple_commands_utils3 //
void	clean_up_function_multiple_commands(
			t_piping_multiple_command_params *params, char ***env);
void	handle_multiple_commands_null_heredocs_input(
			t_piping_multiple_command_params *params, char ***env);
void	handle_multiple_commands_heredocs_delimiter(
			t_piping_multiple_command_params *params, char ***env);
void	handle_multiple_commands_heredocs_input(
			t_piping_multiple_command_params *params);
void	handle_heredocs_readline_multiple_commands(
			t_piping_multiple_command_params *params, char ***env);

// multiple_commands_utils4 //
void	handle_counters_pipe_closing_and_redirects_array(
			t_piping_multiple_command_params *params);
void	handle_redirect_array_for_heredocs(
			t_piping_multiple_command_params *params, char ***env);
void	handle_heredocs_multiple_commands(
			t_piping_multiple_command_params *params, t_list *node,
			char ***env);

// multiple_commands_utils5 //
void	setting_up_input_redirections_multiple_commands(
			t_piping_multiple_command_params *params, char ***env);
void	setting_up_output_redirections_multiple_commands(
			t_piping_multiple_command_params *params, char ***env);
void	setting_up_heredocs_multiple_commands(
			t_piping_multiple_command_params *params, char ***env);
void	setting_up_pipes_to_redirect_output(
			t_piping_multiple_command_params *params, char ***env);
void	read_from_pipe_without_redirections(
			t_piping_multiple_command_params *params, char ***env);

// multiple_commands_utils6 //
void	handle_input_output_heredocs_multiple_commands(
			t_piping_multiple_command_params *params, char ***env);
void	setup_pipe_redirection_and_closing(
			t_piping_multiple_command_params *params, char ***env);
void	handle_built_in_multiple_piping_commands(
			t_piping_multiple_command_params *params, char ***env);
void	handle_exit_conditions_if_built_in(
			t_piping_multiple_command_params *params, char ***env);
void	handle_child_process(
			t_piping_multiple_command_params *params, char ***env);

// multiple_commands_utils7 //
void	handle_file_opening_errors(t_piping_multiple_command_params *params);
void	handle_file_opening_multiple_commands(
			t_piping_multiple_command_params *params);
void	handle_heredocs_pipe_number_multiple_commands(
			t_piping_multiple_command_params *params);
int		handle_arguments(
			t_piping_multiple_command_params *params, char ***env);
void	handle_pipe_and_waiting_for_child(
			t_piping_multiple_command_params *params);

// free_pipes.c //
void	free_pipes(int **pipes, int num_pipes);
void	free_heredocs_pipes(int **heredocs_pipes, int heredocs_count);

// single_command.c //
void	execution(t_list *node, char ***env, int *exit_status);

// single_command_utils1 //
int		checking_if_pipes_exist(t_list *node);
void	finding_heredocs(
			t_redirect_single_command_params *params, t_list *node);
int		handling_no_heredocs(
			t_redirect_single_command_params *params, char ***env,
			t_list *node);
int		creating_pipes(t_redirect_single_command_params *params);
int		handling_heredocs(
			t_redirect_single_command_params *params, char ***env,
			t_list *node);

// single_command_utils2 //
void	handle_file_opening_errors_redirection(
			t_redirect_single_command_params *params, char ***env);
void	handle_file_closing_input_redirection(
			t_redirect_single_command_params *params);
void	handle_file_closing_output_redirection(
			t_redirect_single_command_params *params);
void	handle_redirections_file_opening(
			t_redirect_single_command_params *params, char ***env);
void	handle_dup_and_closing_fd(
			t_redirect_single_command_params *params, char ***env);

// single_command_utils3 //
void	executing_execve(
			t_redirect_single_command_params *params, char ***env);
void	exiting_conditions_nonzero_pipecount(
			t_redirect_single_command_params *params, char ***env);
void	exiting_conditions_zero_pipecount(
			t_redirect_single_command_params *params, char ***env);
void	handle_execve_for_redirections(
			t_redirect_single_command_params *params, char ***env);

// single_command_utils4 //
void	handling_executing_execve_other_cases(
			t_redirect_single_command_params *params, char ***env);
void	handling_exit_conditions_other_cases(
			t_redirect_single_command_params *params, char ***env);
void	child_process_other_cases(
			t_redirect_single_command_params *params, char ***env);
int		handle_fork_plus_executing_child(
			t_redirect_single_command_params *params, char ***env);
int		handle_single_commands(
			t_redirect_single_command_params *params, char ***env);

// single_command_utils5 //
void	execute_child_process_for_redirections(
			t_redirect_single_command_params *params, char ***env);
int		handle_redirects(t_redirect_single_command_params *params, char ***env);
void	freeing_heredoc_pipes(t_redirect_single_command_params *params);
void	clean_up_function(
			t_redirect_single_command_params *params, char ***env);
int		handle_other_cases(
			t_redirect_single_command_params *params, char ***env);

// single_command_utils6 //
int		heredocs(t_redirect_single_command_params *params, char ***env);

// single_command_utils7 //
void	closing_current_pipe_after_writing_data(
			t_redirect_single_command_params *params);
int		handling_forking_process(
			t_redirect_single_command_params *params, char ***env);
void	handling_next_redirect(t_redirect_single_command_params *params);
int		handling_last_redirect(
			t_redirect_single_command_params *params, char ***env);
void	waiting_for_child_to_execute(t_redirect_single_command_params *params);

// single_command_utils8 //
void	closing_current_pipes_heredocs_single_command(
			t_redirect_single_command_params *params);
void	handle_null_heredocs_input(
			t_redirect_single_command_params *params, char ***env);
void	handle_heredocs_delimiter(
			t_redirect_single_command_params *params, char ***env);
void	handle_heredocs_input(t_redirect_single_command_params *params);
void	handle_heredoc_child_process(
			t_redirect_single_command_params *params, char ***env);

// single_comand_utils9 //
void	handle_exit_conditions_for_heredocs(
			t_redirect_single_command_params *params, char ***env);
void	handle_exit_file_opening_heredocs(
			t_redirect_single_command_params *params, char ***env);
void	checking_if_entire_command_has_errors(
			t_redirect_single_command_params *params, char ***env);
int		handle_execve_for_heredocs(
			t_redirect_single_command_params *params, char ***env);
int		handle_child_execution(
			t_redirect_single_command_params *params, char ***env);

#endif
