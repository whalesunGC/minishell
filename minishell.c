/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:20:45 by wichee            #+#    #+#             */
/*   Updated: 2024/10/06 13:21:40 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * @function: main
 * @brief: this is the entry point to the minishell program
 * 
 * @param: None
 * @return: returns int at exit. 0 for failure, 1 for success,
 */
int	main(void)
{
	char	*input;

	input = readline("minishell>> ");
	input = expansion(input);
	lexer(input);
	return (free(input), 1);
}
