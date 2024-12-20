/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:12:53 by apoh              #+#    #+#             */
/*   Updated: 2024/10/14 21:12:58 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_split_export()
 * @brief: static function split string on instance of input char
 * 
 * @param string: export argument
 * @param c: char to split on
 * @return: NULL if ft_split_export fails and prints error. char** 
 * if successfull.
 */
static char	**ft_split_export(char *string, char c)
{
	char	**result;
	char	*index;

	index = NULL;
	result = NULL;
	if (!string)
		return (NULL);
	index = ft_strchr(string, c);
	if (index)
	{
		result = (char **)malloc(3 * sizeof(char *));
		if (!result)
			return (NULL);
		result[0] = (char *)malloc(((index - string) + 1) * sizeof(char));
		if (!result[0])
			return (free(result), NULL);
		result[1] = (char *)malloc((ft_strlen(string) - (index - string))
				* sizeof(char));
		if (!result[1])
			return (free(result), NULL);
		ft_strlcpy(result[0], string, (index - string) + 1);
		ft_strlcpy(result[1], index + 1, ft_strlen(string) - (index - string));
		result[2] = NULL;
	}
	return (result);
}

/**
 * @function: splitting_arguments_by_delimiter
 * @brief: static function to support parse_export_arguments
 	function right below
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function

 * 
 * @return: -1 if ft_split fails and prints error. 0 if success.
 */
static int	splitting_arguments_by_delimiter(t_export_params *params)
{
	params->result = ft_strchr(params->av[params->i], '=');
	if (params->result != NULL)
	{
		params->split_result = ft_split_export(params->av[params->i], '=');
		if (params->split_result == NULL)
		{
			ft_dprintf(2, "splitting arguments failed\n");
			return (-1);
		}
	}
	return (0);
}

/**
 * @function: extracting_var_names
 * @brief: static function to support parse_export_arguments
 	function right below
 	based on ft_split_results, copy the first string to var_name
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 	 * 
 * @return: -1 if strdup fails. by this stage, ft_split is already successful
 	so need to free split_result. 0 if success.
 */

static int	extracting_var_names(t_export_params *params)
{
	if (params->result != NULL)
	{
		params->var_name[params->j] = ft_strdup(params->split_result[0]);
		if (params->var_name[params->j] == NULL)
		{
			free_split_result(params);
			return (-1);
		}
	}
	else
	{
		params->var_name[params->j] = ft_strdup(params->av[params->i]);
		if (params->var_name[params->j] == NULL)
			return (-1);
	}
	return (0);
}

/**
 * @function: extracting_var_values
 * @brief: static function to support parse_export_arguments
 	function right below
 	based on ft_split_results, copy the second string to var_value
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: -1 if strdup fails. by this stage,
 	var_name and split result is successful so need to free
 	0 if success
 */

static int	extracting_var_values(t_export_params *params)
{
	if (params->result != NULL)
	{
		if (params->split_result[1] != NULL)
		{
			if (ft_strcmp(params->split_result[1], "") == 0)
				params->var_value[params->j] = ft_strdup("=");
			else
				params->var_value[params->j]
					= ft_strdup(params->split_result[1]);
		}
	}
	else
		params->var_value[params->j] = ft_strdup("");
	if (params->var_value[params->j] == NULL)
	{
		free_var_name(params);
		free_split_result(params);
		return (-1);
	}
	return (0);
}

/**
 * @function: parse_export_arguments
 * @brief: the process of splitting up your arguments into
 	var_name and var_value using the av structure
 	already created in export_utils1
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: return success or failure
 */

int	parse_export_arguments(t_export_params *params)
{
	params->i = 0;
	params->j = 0;
	while (params->av[params->i] != NULL)
	{
		if (splitting_arguments_by_delimiter(params) == -1)
			return (-1);
		else
		{
			if (extracting_var_names(params) == -1)
				return (-1);
			if (extracting_var_values(params) == -1)
				return (-1);
			params->j++;
		}
		if (params->result != NULL)
			free_split_result(params);
		params->i++;
	}
	params->var_value[params->j] = NULL;
	params->var_name[params->j] = NULL;
	return (1);
}
