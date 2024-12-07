/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:48:28 by apoh              #+#    #+#             */
/*   Updated: 2024/10/21 19:48:29 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_var_value_only_equal_sign(t_export_params *params)
{
	free(params->var_value[params->b]);
	params->var_value[params->b] = ft_strdup("");
	if (params->var_value[params->b] == NULL)
	{
		free_var_name(params);
		free_var_value(params);
		return (NULL);
	}
	params->str1 = ft_strjoin(params->var_name[params->b], "=");
	if (params->str1 == NULL)
		return (NULL);
	ft_strlcpy(params->new_env[params->j], params->str1,
		ft_strlen(params->str1) + 1);
	free(params->str1);
	return (params->new_env[params->j]);
}

void	handle_var_value_with_valid_data(t_export_params *params)
{
	params->str1 = ft_strjoin(params->var_name[params->b], "=");
	params->str2 = ft_strjoin(params->str1, params->var_value[params->b]);
	ft_strlcpy(params->new_env[params->j], params->str2,
		ft_strlen(params->str2) + 1);
	free(params->str1);
	free(params->str2);
}

/**
 * @function: has_equal_sign
 * @brief: supports valid_export_arguments function in export_utils7
 	mallocs data if your av structure has
 	an equal sign for that argument
 	uses the var_name, var_value structures
 	to be joined together
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: NULL if malloc fail. returns (params->new_env) if success.
 */

char	**has_equal_sign(t_export_params *params)

{
	if (ft_strcmp(params->var_value[params->b], "=") == 0)
		params->new_env[params->j] = (char *)malloc
			(sizeof(char) * (ft_strlen(params->av[params->i]) + 4));
	else
		params->new_env[params->j] = (char *)malloc
			(sizeof(char) * (ft_strlen(params->av[params->i]) + 1));
	if (params->new_env[params->j] == NULL)
		return (NULL);
	if (ft_strcmp(params->var_value[params->b], "=") == 0)
	{
		params->result = handle_var_value_only_equal_sign(params);
		if (params->result == NULL)
			return (NULL);
	}
	else
		handle_var_value_with_valid_data(params);
	return (params->new_env);
}

/**
 * @function: no_equal_sign
 * @brief: supports valid_export_arguments function in export_utils7
 	mallocs data if your av structure does not
 	have an equal sign for that argument.
 	uses the var_name structures to string join and copy to new_env
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 	***env : to update the correct environment variables
 		if appending is done in other functions
 * 
 * @return: NULL if malloc fail. returns (params->new_env) if success.
 */

char	**no_equal_sign(t_export_params *params)

{
	char	*str1;

	params->new_env[params->j] = (char *)malloc
		(sizeof(char) * (ft_strlen(params->av[params->i]) + 4));
	if (params->new_env[params->j] == NULL)
		return (NULL);
	str1 = ft_strjoin(params->var_name[params->b], "=''");
	ft_strlcpy(params->new_env[params->j], str1, ft_strlen(str1) + 1);
	free(str1);
	return (params->new_env);
}

/**
 * @function: setting_up_length
 * @brief: supports valid_export_arguments function in export_utils7
 	searches for = sign for manipulation of data.
 * 
 * @param t_export_params *params: created a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

void	setting_up_length(t_export_params *params)

{
	params->equal_sign = ft_strchr(params->av[params->i], '=');
	if (params->equal_sign != NULL)
	{
		params->length = params->equal_sign - params->av[params->i];
		params->equal_sign1 = params->equal_sign++;
	}
	else
		params->length = ft_strlen(params->av[params->i]);
}
