/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:09:06 by apoh              #+#    #+#             */
/*   Updated: 2024/10/21 22:09:12 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: append_new_env_if_data_exists
 * @brief: static function to support parse_valid_arguments_function
 	overwrites the data if new_env already has a duplicate in new_env
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static int	append_new_env_if_data_exists(t_export_params *params)

{
	while (params->new_env[params->j] != NULL)
	{
		if (ft_strncmp(params->new_env[params->j], params->var_name[params->b],
				ft_strlen(params->var_name[params->b])) == 0
			&& params->new_env[params->j]
			[ft_strlen(params->var_name[params->b])] == '=')
		{
			free(params->new_env[params->j]);
			if (params->equal_sign != NULL)
				params->new_env = has_equal_sign(params);
			else
				params->new_env = no_equal_sign(params);
			if (params->new_env == NULL)
			{
				free_new_env(params);
				return (-1);
			}
			params->found = 1;
			while (params->new_env[params->j] != NULL)
				params->j++;
			break ;
		}
		params->j++;
	}
	return (0);
}

/**
 * @function: append_new_env_if_data_is_new
 * @brief: static function to support parse_valid_argument_function
 	appends right at the end of new_env if nothing is found
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static int	append_new_env_if_data_is_new(t_export_params *params)

{
	if (params->found != 1)
	{
		if (params->equal_sign != NULL)
			params->new_env = has_equal_sign(params);
		else
			params->new_env = no_equal_sign(params);
		if (params->new_env == NULL)
		{
			free_new_env(params);
			return (-1);
		}
	}
	return (0);
}

/**
 * @function: increment count
 * @brief: static function to support parse_valid_argument
 	increment of counters for the function
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static void	increment_count(t_export_params *params)

{
	params->b++;
	params->i++;
}

/**
 * @function: setting_up_counters_and_flags
 * @brief: static function to support parse_valid_argument
 	counters and flags are setup to search new_env for duplicates
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static void	setting_up_counters_and_flags(t_export_params *params)

{
	params->found = 0;
	params->j = 0;
}

/**
 * @function: valid_export_arguments
 * @brief: arguments that makes it to this stage are already valid.
 	Hence, appending is done depending on whether new_env already
 	has those variables to begin with
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	valid_export_arguments(t_export_params *params)

{
	params->i = 0;
	while (params->av[params->i] != NULL)
	{
		setting_up_length(params);
		if (params->is_valid == 1)
		{	
			setting_up_counters_and_flags(params);
			if (append_new_env_if_data_exists(params) == -1)
				return ;
			if (append_new_env_if_data_is_new(params) == -1)
				return ;
		}
		increment_count(params);
	}
}
