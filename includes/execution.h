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
	int			**pipes;
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
	int			delimiter_counter;
	int			rd_arg_counter;
	int			z;
	int			y;
	int			pipe_count;
	int			count;
	int			loop_counter;
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

// multiple_command.c //
void	execution_with_pipes(t_list *node, char **env);

// multiple_commands_utils1 //
int		check_total_commands(t_list *node);
int		check_for_pipes(t_list *node);
int		**creating_new_pipes(int num_pipes);
int		setting_up_pipes(t_piping_multiple_command_params *params);

// heredocs.c //
int		handling_forking_process(
			t_redirect_single_command_params *params, char ***env, char *input);
void	handling_next_redirect(t_redirect_single_command_params *params);
int		handling_last_redirect(
			t_redirect_single_command_params *params, char ***env, char *input);
void	waiting_for_child_to_execute(t_redirect_single_command_params *params);
int		heredocs(t_redirect_single_command_params *params,
			char ***env, char *input);

// heredocs_utils1 //
void	handle_null_heredocs_input(t_redirect_single_command_params *params,
			char ***env, char *input);
void	handle_heredocs_delimiter(t_redirect_single_command_params *params,
			char ***env, char *input);
void	handle_heredocs_input(t_redirect_single_command_params *params);
void	handle_heredoc_child_process(t_redirect_single_command_params *params,
			char ***env, char *input);

// heredocs_utils2 //
void	handle_exit_conditions_for_heredocs(
			t_redirect_single_command_params *params, char ***env, char *input);
int		handle_execve_for_heredocs(
			t_redirect_single_command_params *params, char ***env, char *input);
int		handle_child_execution(
			t_redirect_single_command_params *params, char ***env, char *input);

// free_pipes.c //
void	free_pipes(int **pipes, int num_pipes);

// single_command.c //
void	finding_heredocs(t_redirect_single_command_params *params,
			t_list *node);
int		handling_no_heredocs(
			t_redirect_single_command_params *params,
			char ***env, char *input, t_list *node);
int		creating_pipes(t_redirect_single_command_params *params);
int		handling_heredocs(
			t_redirect_single_command_params *params,
			char ***env, char *input, t_list *node);
void	execution(t_list *node, char ***env, char *input);

// single_commands_utils1 //
void	handle_redirections_file_opening(
			t_redirect_single_command_params *params);
void	handle_dup_and_closing_fd(t_redirect_single_command_params *params);
void	executing_execve_redirections(t_redirect_single_command_params *params,
			char ***env, char *input);
void	handle_execve_for_redirections(t_redirect_single_command_params *params,
			char ***env, char *input);

// single_commands_utils2 //
void	clean_up_function(t_redirect_single_command_params *params,
			char ***env, char *input);
void	exiting_conditions_nonzero_pipecount(
			t_redirect_single_command_params *params, char ***env, char *input);
void	exiting_conditions_zero_pipecount(
			t_redirect_single_command_params *params, char ***env, char *input);

// single_commands_utils3 //
void	executing_execve_other_cases(
			t_redirect_single_command_params *params, char ***env, char *input);
void	handling_exit_conditions_other_cases(
			t_redirect_single_command_params *params, char ***env, char *input);
void	child_process_other_cases(
			t_redirect_single_command_params *params, char ***env, char *input);
int		handle_fork_plus_executing_child(
			t_redirect_single_command_params *params, char ***env, char *input);
int		handle_single_commands(
			t_redirect_single_command_params *params, char ***env, char *input);

// single_commands_utils4 //
int		checking_if_pipes_exist(t_list *node);
int		handle_redirects(t_redirect_single_command_params *params,
			char ***env, char *input);
void	execute_child_process_for_redirections(
			t_redirect_single_command_params *params, char ***env, char *input);
int		handle_single_commands_no_heredocs(
			t_redirect_single_command_params *params, char ***env, char *input);
int		handle_other_cases(
			t_redirect_single_command_params *params,
			char ***env, char *input);

#endif
