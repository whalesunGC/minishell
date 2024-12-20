/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:35:47 by apoh              #+#    #+#             */
/*   Updated: 2024/10/11 21:36:12 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "execution.h"

typedef struct s_export_params
{
	char	**new_env;
	char	**av;
	char	**var_name;
	char	**var_value;
	char	**split_result;
	char	*equal_sign;
	char	*equal_sign1;
	char	*result;
	char	*str1;
	char	*str2;
	char	*result1;
	char	current_char;
	int		ac;
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
	int		b;
	int		d;
	int		e;
	int		f;
	int		total_args;
	int		counter;
	int		found;
	int		valid_count;
	int		is_valid;
	int		length;
	int		flag;
}	t_export_params;

// handle built-ins plus the supporting logic for export functions. //
char	**cd_command(int ac, char **av, char ***env, int *e_s);
char	**updating_env(char ***env, char *old_pwd);
void	pwd_command(int ac, char **av, int *e_s);
void	env_command(int ac, char **av, char **env, int *e_s);
void	exit_command(t_redirect_single_command_params *params, char **env,
			int *e_s);
void	exit_command_multiple(t_piping_multiple_command_params *params,
			char **env, int *e_s);
void	echo_command(int ac, char **av);
char	**unset_command(int ac, char **av, char **env);
char	**export_command(int ac, char **av, char ***env, int *e_s);

// export_utils1 //
void	only_export_command(t_export_params *params, char ***env);
void	setting_up_of_av_structure(t_export_params *params);
int		initialise_var_name_var_value(t_export_params *params);
int		valid_export_arguments_first_parse(t_export_params *params,
			char ***env, int *e_s);
void	processing_for_valid_counts(t_export_params *params, char ***env);

// export utils2 //
int		parse_export_arguments(t_export_params *params);

// export utils3 //
void	checking_for_duplicates_in_var_name(t_export_params *params);
void	variable_value_check(t_export_params *params);
void	removing_invalid_identifier(t_export_params *params);
void	variable_name_character_checks(t_export_params *params);

// export utils4 //
void	first_parsing(t_export_params *params);
int		ft_isvalidvariable(int c);

// export utils5 //
char	**has_equal_sign(t_export_params *params);
char	**no_equal_sign(t_export_params *params);
void	setting_up_length(t_export_params *params);

// export utils6 //
void	free_var_name(t_export_params *params);
void	free_var_value(t_export_params *params);
void	free_split_result(t_export_params *params);
void	free_new_env(t_export_params *params);

// export utils7 //
void	valid_export_arguments(t_export_params *params);

// export utils8 //
void	checking_env_data(t_export_params *params, char ***env);
void	handling_data_if_env_exists_and_var_value_is_empty(
			t_export_params *params);
void	initialise_counters_and_parsing(t_export_params *params);
void	initialise_counters_in_loop(t_export_params *params);

// exit_utils.c
int		ft_chk_ul(char *number);
void	exit_too_many_args(int *e_s);
int		is_argument_numeric(const char *arg);

//handle freeing of av after usage //
void	free_tokens(char **av);
void	free_dup_envp(char **env);

// copy envp so that you can manipulate the data //
char	**copy_envp(char **envp);
char	**handle_env_int(char **envp, int *e_s);

// copying from env in the event i need to append new data //
char	**copy_envp_with_ac(char **env, int space);

// external functions //
int		ft_strcmp(const char *s1, const char *s2);

#endif
