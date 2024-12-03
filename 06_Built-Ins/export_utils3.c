/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:49:53 by apoh              #+#    #+#             */
/*   Updated: 2024/10/14 21:49:59 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: removal_of_duplicates_in_var_name
 * @brief: static function to support checking_for_duplicates_in_var_name
 	function below. if duplicates encountered as we are to
 	use the last argument do take note we need to manipulate var_name,
 	var_value and av structures
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static void	removal_of_duplicates_in_var_name(t_export_params *params)

{
	params->f = params->d;
	while (params->f < params->counter - 1)
	{
		params->var_name[params->f] = params->var_name[params->f + 1];
		params->var_value[params->f] = params->var_value[params->f + 1];
		params->av[params->f] = params->av[params->f + 1];
		params->f++;
	}
	params->var_name[params->f] = NULL;
	params->var_value[params->f] = NULL;
	params->av[params->f] = NULL;
}

/**
 * @function: checking_for_duplicates_in_var_name
 * @brief: to support first_parsing function in export_utils4
 	comparing the strings inside the var_name structure.
 	if duplicates are found, use the last argument.
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	checking_for_duplicates_in_var_name(t_export_params *params)

{
	while (params->var_name[params->counter] != NULL)
		params->counter++;
	while (params->d < params->counter)
	{
		params->e = params->d + 1;
		while (params->e < params->counter)
		{
			if (ft_strcmp(params->var_name[params->d],
					params->var_name[params->e]) == 0)
			{
				free(params->var_name[params->d]);
				free(params->var_value[params->d]);
				free(params->av[params->d]);
				removal_of_duplicates_in_var_name(params);
				params->counter--;
				params->e = params->d + 1;
			}
			else
				params->e++;
		}
		params->d++;
	}
}

/**
 * @function: variable_value_check
 * @brief: to support first_parsing function in export_utils4
 	to check if var_value is a valid
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	variable_value_check(t_export_params *params)

{
	params->j = 0;
	while (params->var_value[params->i][params->j] != '\0')
	{
		params->current_char = params->var_value[params->i][params->j];
		if (ft_isvalidvariable(params->current_char) == 0)
		{
			params->is_valid = 0;
			ft_dprintf(2, "%s%s: not an identifier2\n",
				params->var_name[params->i],
				params->var_value[params->i]);
			removing_invalid_identifier(params);
			break ;
		}
		params->j++;
	}
}

/**
 * @function: removing_invalid_identifier
 * @brief: to support first_parsing_function in export utils4
 	to manipulate the data structures of var_name, var_value, av
 	when invalid_identifiers are found.
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	removing_invalid_identifier(t_export_params *params)

{
	params->counter = 0;
	while (params->var_name[params->counter] != NULL)
		params->counter++;
	while (params->i < params->counter)
	{
		free(params->var_name[params->i]);
		free(params->var_value[params->i]);
		free(params->av[params->i]);
		params->d = 0;
		params->d = params->i;
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
		break ;
	}
}

/**
 * @function: variable_name_character_checks
 * @brief: to support first_parsing function in export_utils4
 	to check if var_name is valid
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	variable_name_character_checks(t_export_params *params)

{
	params->j = 1;
	while (params->var_name[params->i][params->j] != '\0')
	{
		params->current_char = params->var_name[params->i][params->j];
		if (params->current_char == 95
			|| ft_isdigit(params->current_char) == 1
			|| ft_isalpha(params->current_char) == 1)
		{
		}
		else
		{
			params->is_valid = 0;
			ft_dprintf(2, "%s=%s: not an identifier1\n",
				params->var_name[params->i],
				params->var_value[params->i]);
			removing_invalid_identifier(params);
			break ;
		}
		params->j++;
	}
}
