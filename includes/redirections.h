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

typedef struct s_command_params
{
	char	**tokens;
	char	*path;
	char	*temp_path;
	char	*full_path;
	int		k;
}	t_command_params;

// path construction && path construction_utils //
char	*find_command(char **av, int index, char **env);
void	free_path_tokens(t_command_params *params);
int		check_valid_path_variable(t_command_params *params, char **env);
int		check_valid_split(t_command_params *params);
int		check_valid_temp_path(t_command_params *params);
int		check_valid_full_path(t_command_params *params, char **av, int index);

#endif
