/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:31:58 by wichee            #+#    #+#             */
/*   Updated: 2024/11/14 17:32:01 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_has_whitespace
 * @brief: checks if string has whitespace
 * 
 * @param string: input string
 * @return: 1 or 0
 */
int ft_has_whitespace(char *string)
{
    if (!string)
        return (0);
    while (*string)
    {
        if (ft_iswhitespace(*string))
            return (1);
        string++;
    }
    return (0);
}

/**
 * @function: ft_remove_quote
 * @brief: removes all quotes from input string, returns new string
 * 
 * @param string: input string
 * @return: new string with no quotes
 */
char *ft_remove_quote(char *string)
{
    int i;

    if (!string)
        return (NULL);
    i = 0;
    while (string[i])
    {
        if (string[i] == '\'' || string[i] == '\"')
            string = ft_str_replace(string, i, "");
        else
            i++;
    }
    return (string);
}

/**
 * @function: ft_has_quote
 * @brief: checks if quotes exist in string
 * 
 * @param string: input string
 * @return: 1 or 0
 */
int ft_has_quote(char *string)
{
    if (!string)
        return (0);
    while (*string)
    {
        if (*string == '\'' || *string == '\"')
            return (1);
        string++;
    }
    return (0);
}