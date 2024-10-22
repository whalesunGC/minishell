/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:07:34 by apoh              #+#    #+#             */
/*   Updated: 2024/10/14 21:07:50 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * @function: only_export_command
 * @brief: illusrates what happens the only argument is export
 		will print out the details inside the environment
 		this function is to be used in export_command function
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 	***env : to update the correct environment variables
 		if appending is done in other functions
 * 
 * @return: void function
 */

void	only_export_command(t_export_params *params, char ***env)

{
	while ((*env)[params->i] != NULL)
	{
		ft_printf("%s\n", (*env)[params->i]);
		params->i++;
	}
}

/**
 * @function: setting_up_of_av_structure
 * @brief: to create an av structure which can be used
 	as the final product to append data if needed
 	for example av is tokenisied in my main - export abc def
 	These are 3 tokens. this structure will
 	remove the export word and leaves abc def inside
 	this function is to be used in export_command function
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 * 
 * @return: (*env)
 */

void	setting_up_of_av_structure(t_export_params *params)

{
	free(params->av[0]);
	while (params->i < params->ac)
	{
		params->av[params->i] = params->av[params->i + 1];
		params->i++;
	}
	params->av[params->i] = NULL;
}

/**
 * @function: initialise_var_name_var_value
 * @brief: malloc spaces for var_name and var_value which is to be used
 	for manipulation purposes. this function is to be
 	used in export_command function
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 * 
 * @return: -1 if malloc fails, 0 if success
 */

int	initialise_var_name_var_value(t_export_params *params)

{
	params->var_name = malloc(sizeof(char *) * (params->ac + 1));
	if (params->var_name == NULL)
		return (-1);
	params->var_value = malloc(sizeof(char *) * (params->ac + 1));
	if (params->var_value == NULL)
	{
		free_var_name(params);
		return (-1);
	}
	return (0);
}

/**
 * @function: valid_export_arguments_first_parse
 * @brief: to check if there is a valid argument. If yes malloc space
 	and copy env to new_env and create more space for it and get ready
 	for appending. This function is to be used in export_utils2
 	parse_export_arguments function. first_parsing function in
 	export utils4 
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 	 ***env : to manipulate env depending on whether
 	 there is an argument to be appended into env
 * 
 * @return: -1 if malloc fails when there is valid count
 	0 if no valid count or malloc success
 */

int	valid_export_arguments_first_parse(t_export_params *params,
		char ***env)

{
	params->is_valid = 1;
	params->i = 0;
	first_parsing(params);
	if (params->valid_count > 0)
	{
		params->new_env = copy_envp_with_ac(*env, params->valid_count);
		if (params->new_env == NULL)
		{
			free_var_name(params);
			free_var_value(params);
			return (-1);
		}
	}
	return (0);
}

/**
 * @function: processing_for_valid_counts
 * @brief: function is to be used in export_utils7
 	valid_export_arguments_second_parse where second parsing takes place
 	this is to be used to append the data into new_env
 	and set a null terminator for new_env after that
 	*env will then copy the pointers to itself
 	to be used for subsequent commands
 	freeing up of var_name and var_value structures will be done after that
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 	 ***env : to manipulate env depending on whether
 	 there is an argument to be appended into env
 * 
 * @return: (*env)
 */

void	processing_for_valid_counts(t_export_params *params, char ***env)

{
	valid_export_arguments(params);
	params->new_env[params->j + 1] = NULL;
	*env = params->new_env;
}
