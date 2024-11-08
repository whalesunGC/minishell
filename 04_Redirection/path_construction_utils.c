/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:11:40 by apoh              #+#    #+#             */
/*   Updated: 2024/10/07 15:11:51 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_path_tokens
 * @brief: freeing your path variable which is split into tokens
 * 
 * @param t_command_params params : structure created to handle
 	find_command function in execve_utils1.c
 * 
 * @return: void function
 */

void	free_path_tokens(t_command_params *params)

{
	int	i;

	i = 0;
	while (params->tokens[i] != NULL)
	{
		free(params->tokens[i]);
		i++;
	}
	free(params->tokens);
}

/**
 * @function: check_valid_path_variable
 * @brief: function to search the env variable and extract the PATH variable
 * 
 * @param t_command_params params : structure created to handle
 	find_command function in execve_utils1.c
 * 
 * @return: -1 if failure, 0 if success
 */

int	check_valid_path_variable(t_command_params *params, char **env)

{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			params->path = malloc(sizeof(char) * (ft_strlen(env[i]) - 4));
			if (params->path == NULL)
			{
				ft_printf("creating PATH variable failed.\n");
				return (-1);
			}
			ft_strlcpy(params->path, env[i] + 5, ft_strlen(env[i]) - 4);
		}
		i++;
	}
	if (params->path == NULL)
	{
		ft_printf("PATH environment variable not set.\n");
		return (-1);
	}
	return (0);
}

/**
 * @function: check_valid_split
 * @brief: checks if ft_split of path variable
 	using : as delimiter is successful
 * 
 * @param t_command_params params : structure created to handle
 	find_command function in execve_utils1.c
 * 
 * @return: -1 if failure, 0 if success
 */

int	check_valid_split(t_command_params *params)

{
	params->tokens = ft_split(params->path, ':');
	free(params->path);
	if (params->tokens == NULL)
	{
		ft_printf("memory allocation failed when splitting PATH.\n");
		return (-1);
	}
	return (0);
}

/**
 * @function: check_valid_temp_path
 * @brief: checks if the construction of path variable with
 	"/" string is successful
 * 
 * @param t_command_params params : structure created to handle
 	find_command function in execve_utils1.c
 * 
 * @return: -1 if failure, 0 if success
 */

int	check_valid_temp_path(t_command_params *params)

{
	params->temp_path = ft_strjoin(params->tokens[params->k], "/");
	if (params->temp_path == NULL)
	{
		ft_printf("memory allocation failed for temp_path.\n");
		free_tokens(params->tokens);
		return (-1);
	}
	return (0);
}

/**
 * @function: check_valid_full_path
 * @brief: checks if the construction of full path if successful
 * 
 * @param t_command_params params : structure created to handle
 	find_command function in execve_utils1.c
 * 
 * @return: -1 if failure, 0 if success
 */

int	check_valid_full_path(t_command_params *params, char **av, int index)

{
	params->full_path = ft_strjoin(params->temp_path, av[index]);
	free(params->temp_path);
	if (params->full_path == NULL)
	{
		ft_printf("memory allocation failed for full_path.\n");
		free_path_tokens(params);
		return (-1);
	}
	return (0);
}
