/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:10:45 by apoh              #+#    #+#             */
/*   Updated: 2024/10/15 20:10:53 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: variable_name_first_character_check_fail
 * @brief: to support first_parsing function below
 	prints error message and removes invalid identifier
 	if var_name is invalid
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static void	variable_name_first_character_check_fail(t_export_params *params)

{
	ft_printf("%s: not an identifier\n", params->var_name[params->i]);
	removing_invalid_identifier(params);
}

/**
 * @function: increment_counts_first_parsing
 * @brief: to support first_parsing function below
 	to increment counters
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static void	increment_counts_first_parsing(t_export_params *params)

{
	params->valid_count++;
	params->i++;
}

/**
 * @function: first_parsing
 * @brief: this function is used to support valid_export_arguments_first_parse
 	in export_utils1. this parsing is to check for invalid identifiers
 	prints error message if invalid
 	checks if there is any valid counts as well
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	first_parsing(t_export_params *params)

{
	while (params->var_name[params->i] != NULL)
	{
		params->current_char = params->var_name[params->i][0];
		if (params->current_char != 95 && ft_isalpha(params->current_char) == 0)
		{
			variable_name_first_character_check_fail(params);
			continue ;
		}
		variable_name_character_checks(params);
		if (params->is_valid == 0)
		{
			params->is_valid = 1;
			continue ;
		}
		else if (params->is_valid == 1)
		{
			variable_value_check(params);
			if (params->is_valid == 0)
			{
				params->is_valid = 1;
				continue ;
			}
		}
		increment_counts_first_parsing(params);
	}
}
