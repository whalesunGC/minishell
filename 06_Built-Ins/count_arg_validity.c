/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arg_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:45:14 by apoh              #+#    #+#             */
/*   Updated: 2024/10/01 13:45:22 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	count_argument_validity_first_parsing(t_export_params *params)

{
	params->j = 1;
	while (params->av[params->i][params->j] != '\0')
	{
		params->current_char = params->av[params->i][params->j];
		if (params->current_char == 95 || params->current_char == 61
			|| ft_isdigit(params->current_char) == 1
			|| ft_isalpha(params->current_char) == 1)
		{
		}
		else
		{
			params->is_valid = 0;
			break ;
		}
		params->j++;
	}
	if (params->is_valid == 0)
	{
		ft_printf("%s: not an identifier\n", params->av[params->i]);
		params->invalid_count++;
	}
	else
		params->valid_count++;
}

void	count_argument_validity_first_parsing_part2(t_export_params *params)

{
	ft_printf("%s: not an identifier\n", params->av[params->i]);
	params->invalid_count++;
}

void	count_argument_validity_second_parsing(t_export_params *params)

{
	params->k = 1;
	while (params->av[params->j][params->k] != '\0')
	{
		params->current_char = params->av[params->j][params->k];
		if (params->current_char == 95 || params->current_char == 61
			|| ft_isdigit(params->current_char) == 1
			|| ft_isalpha(params->current_char) == 1)
		{
		}
		else
		{
			params->count++;
			break ;
		}
		params->k++;
	}
}
