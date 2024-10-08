/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:37:52 by wichee            #+#    #+#             */
/*   Updated: 2024/10/07 18:02:39 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_str_replace
 * @brief: takes a input string
 * 
 * @param input: input string.
 * @param index: start position where replacement substring begins.
 * @param rep_substr: replacement substring.
 * 
 * @return: returns a new string that has the substring replaced
 */
char	*ft_str_replace(char *input, int index, char *rep_substring)
{
	char	*result;
	int		input_len;
	int		rep_len;
	int		result_len;

	if (!input || !rep_substring || index < 0)
		return (NULL);
	input_len = ft_strlen(input);
	rep_len = ft_strlen(rep_substring);
	result_len = input_len - ft_strlen(input + index) + rep_len;
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, input, index + 1);
	ft_strlcat(result, rep_substring, result_len + 1);
	ft_strlcat(result, input + index + ft_strlen(input + index), result_len + 1);
	free(input);
	return (result);
}
