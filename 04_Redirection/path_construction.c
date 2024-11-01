/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:52:07 by apoh              #+#    #+#             */
/*   Updated: 2024/10/31 19:52:10 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: find_command
 * @brief: this function will start to create a full path
 	if the command is not absolute path
 * 
 * @param **av : string of arguments
 	 index : index for referencing to which string you are at
 * 
 * @return: NULL if path cannot be created
 */

char	*find_command(char **av, int index, char **env)

{
	t_command_params	params;

	ft_memset(&params, 0, sizeof(t_command_params));
	if (av[index] == NULL)
		return (NULL);
	if (check_valid_path_variable(&params, env) == -1)
		return (NULL);
	if (check_valid_split(&params) == -1)
		return (NULL);
	while (params.tokens[params.k] != NULL)
	{
		if (check_valid_temp_path(&params) == -1)
			return (NULL);
		if (check_valid_full_path(&params, av, index) == -1)
			return (NULL);
		if (access(params.full_path, X_OK) == 0)
		{
			free_path_tokens(&params);
			return (params.full_path);
		}
		free(params.full_path);
		params.k++;
	}
	free_path_tokens(&params);
	return (NULL);
}
