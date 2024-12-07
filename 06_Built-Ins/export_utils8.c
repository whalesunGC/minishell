/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:31:59 by apoh              #+#    #+#             */
/*   Updated: 2024/12/07 18:32:01 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: checking_env_data
 * @brief: checking env to see if certain conditions are met
 	If so, do not append to env
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 	 ***env : to manipulate env depending on whether
 	 there is an argument to be appended into env
 * 
 * @return: void function
 */

void	checking_env_data(t_export_params *params, char ***env)
{
	if ((ft_strncmp((*env)[params->k], params->var_name[params->l],
			ft_strlen(params->var_name[params->l])) == 0)
		&& (*env)[params->k][ft_strlen(params->var_name[params->l])]
		== '=')
	{
		if (ft_strcmp(params->var_value[params->l], "") == 0)
			handling_data_if_env_exists_and_var_value_is_empty(params);
		else
			params->l++;
	}
}

/**
 * @function: handling_data_if_env_exists_and_var_value_is_empty
 * @brief: manipulating av structure if data is not needed
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	handling_data_if_env_exists_and_var_value_is_empty(
			t_export_params *params)
{
	params->counter = 0;
	while (params->var_name[params->counter] != NULL)
		params->counter++;
	while (params->l < params->counter)
	{
		free(params->var_name[params->l]);
		free(params->var_value[params->l]);
		free(params->av[params->l]);
		params->d = 0;
		params->d = params->l;
		while (params->d < params->counter)
		{
			params->var_name[params->d] = params->var_name[params->d + 1];
			params->var_value[params->d] = params->var_value[params->d + 1];
			params->av[params->d] = params->av[params->d + 1];
			params->d++;
		}
		params->var_name[params->d] = NULL;
		params->var_value[params->d] = NULL;
		params->av[params->d] = NULL;
		params->counter--;
		params->valid_count--;
		break ;
	}
}

/**
 * @function: initialise_counters_and_parsing
 * @brief: initialise_counters_and_doing_parsing to eliminate invalid identifiers
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	initialise_counters_and_parsing(t_export_params *params)
{
	params->total_args = params->i;
	params->is_valid = 1;
	params->i = 0;
	params->k = 0;
	first_parsing(params);
}

/**
 * @function: initialise_counters_in_loop
 * @brief: to reset certain counters before implementing the removal function
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	initialise_counters_in_loop(t_export_params *params)
{
	params->k = 0;
	params->l = 0;
}
