/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:02:10 by apoh              #+#    #+#             */
/*   Updated: 2024/09/30 21:02:14 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: setting_up_ac_av
 * @brief: a static function to support the export_command function
 	ac will capture the total arguments in the main function
 	av is used to capture the tokens created in the main
 	will be manipulated later on in the other functions
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static void	setting_up_ac_av(t_export_params *params, int ac, char **av)
{
	params->av = av;
	params->ac = ac;
}

/**
 * @function: free_var_structures
 * @brief: a static function to support the export_command function
 	frees up var_name and var_value structures after use
 * 
 * @param t_export_params *params : Creates a structure
 	to store variables required for the export function
 * 
 * @return: void function
 */

static void	free_var_structures(t_export_params *params)
{
	free_var_name(params);
	free_var_value(params);
}
/**
 * @function: export_command
 * @brief: illusrates what happens when export command is being typed.
 * 
 * @param ac : the total number of arguments which comes from the main
 	 **av : the string belonging to each argument
 	 ***env : to manipulate env depending on whether
 	 there is an argument to be appended into env.
 * 
 * @return: (*env)
 */

char	**export_command(int ac, char **av, char ***env)
{
	t_export_params	params;

	ft_memset(&params, 0, sizeof(t_export_params));
	setting_up_ac_av(&params, ac, av);
	if (params.ac > 0 && ft_strncmp(params.av[0], "export", 6) == 0)
	{
		if (params.ac == 1 && ft_strlen(params.av[0]) == 6)
			only_export_command(&params, env);
		else if (params.ac > 1 && ft_strlen(params.av[0]) == 6)
		{
			setting_up_of_av_structure(&params);
			if (initialise_var_name_var_value(&params) == -1)
				return (NULL);
			parse_export_arguments(&params);
			checking_for_duplicates_in_var_name(&params);
			if (valid_export_arguments_first_parse(&params, env) == -1)
				return (NULL);
			if (params.valid_count > 0)
				processing_for_valid_counts(&params, env);
			free_var_structures(&params);
		}
		else if (params.ac > 1 && ft_strlen(params.av[0]) != 6)
			ft_dprintf(1, "%s: command not valid\n", params.av[0]);
	}
	return (*env);
}
