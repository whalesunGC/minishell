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

typedef struct s_export_params
{
	char	**new_env;
	char	**av;
	char	*equal_sign;
	char	*equal_sign1;
	char	current_char;
	int		ac;
	int		i;
	int		j;
	int		k;
	int		count;
	int		valid_count;
	int		invalid_count;
	int		is_valid;
	int		length;
}	t_export_params;

// handle built-ins plus the supporting logic for export functions. //
char	**cd_command(int ac, char **av, char ***env);
char	**updating_env(char ***env, char *old_pwd);
void	pwd_command(int ac, char **av);
void	env_command(int ac, char **av, char **env);
void	exit_command(int ac, char **av, char **env, char *input);

//handle freeing of av after usage //
void	free_tokens(char **av);
void	free_dup_envp(char **env);

// copy envp so that you can manipulate the data //
char	**copy_envp(char **envp);

// copying from env in the event i need to append new data //
char	**copy_envp_with_ac(char **env, int space);

#endif
