/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:15:48 by apoh              #+#    #+#             */
/*   Updated: 2024/10/21 21:15:52 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_var_name
 * @brief: frees up var_name structure after using it.
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	free_var_name(t_export_params *params)

{
	int	i;

	i = 0;
	while (params->var_name[i] != NULL)
	{
		free(params->var_name[i]);
		i++;
	}
	free(params->var_name);
	params->var_name = NULL;
}

/**
 * @function: free_var_value
 * @brief: frees up variable value function after using it
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	free_var_value(t_export_params *params)

{
	int	i;

	i = 0;
	while (params->var_value[i] != NULL)
	{
		free(params->var_value[i]);
		i++;
	}
	free(params->var_value);
	params->var_value = NULL;
}

/**
 * @function: free_split_result
 * @brief: frees up split_result after usage
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	free_split_result(t_export_params *params)

{
	int	i;

	i = 0;
	while (params->split_result[i] != NULL)
	{
		free(params->split_result[i]);
		i++;
	}
	free(params->split_result);
	params->split_result = NULL;
}

/**
 * @function: free_new_env
 * @brief: freeing new_env if malloc fails while appending to new_env
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	free_new_env(t_export_params *params)

{
	int	index;

	index = params->j;
	while (index >= 0)
	{
		free(params->new_env[index]);
		params->new_env[index] = NULL;
		index--;
	}
	free(params->new_env);
}
