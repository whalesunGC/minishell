/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:22 by apoh              #+#    #+#             */
/*   Updated: 2024/10/24 15:36:24 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

typedef struct s_redirections_params
{
	pid_t	pid;
	char	**output;
	char	*delimiter;
	char	*line;
	char	*new_line;
	char	*input1;
	char	*command_path;
	char	*args[2];
	int		i;
	int		j;
	int		input_fd;
	int		output_fd;
	int		pipefd[2];
	int		count;
}	t_redirections_params;

typedef struct s_piping_params
{
	pid_t	pid1;
	pid_t	pid2;
	char	*command_path;	
	char	*args[2];
	char	*args1[3];
	int		fd[2];
	int		i;
	int		command_count;
}	t_piping_params;

typedef struct s_command_params
{
	char	**tokens;
	char	*path;
	char	*temp_path;
	char	*full_path;
	int		k;
}	t_command_params;

// redirection_utils //
int		input_redirections_operator(t_redirections_params *params,
			char **av, char **env, char *input);

// redirections_utils1 //
void	handle_output_fd_error(char **av, char **env, char *input);
void	handle_dup2_error(t_redirections_params *params,
			char **av, char **env, char *input);
void	handle_no_command(char **av, char **env, char *input);
void	handle_command_error(t_redirections_params *params,
			char **av, char **env, char *input);

// redirections_utils2 //
int		output_redirections_operator(t_redirections_params *params,
			char **av, char **env, char *input);

// redirections_utils4 //
int		append_output_redirections_operator(t_redirections_params *params,
			char **av, char **env, char *input);

// path construction && path construction_utils //
char	*find_command(char **av, int index, char **env);
void	free_path_tokens(t_command_params *params);
int		check_valid_path_variable(t_command_params *params, char **env);
int		check_valid_split(t_command_params *params);
int		check_valid_temp_path(t_command_params *params);
int		check_valid_full_path(t_command_params *params, char **av, int index);

// piping //
void	piping_commands(char **av, char **env, char *input);

#endif
