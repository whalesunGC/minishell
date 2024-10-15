/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:37:52 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 17:10:42 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_str_insert
 * @brief: takes a input string and inserts the substring after
 * the index
 * 
 * @param input: input string.
 * @param index: start position where replacement substring begins.
 * @param rep_substr: replacement substring.
 * 
 * @return: returns a new string that has the substring replaced
 */
char	*ft_str_insert(char *input, int index, char *rep_substring)
{
	char	*result;
	int		input_len;
	int		insert_len;
	int		result_len;

	if (!input || !rep_substring || index < 0)
		return (NULL);
	input_len = ft_strlen(input);
	insert_len = ft_strlen(rep_substring);
	result_len = input_len + insert_len;
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, input, index + 2);
	ft_strlcat(result, rep_substring, result_len + 1);
	ft_strlcat(result, input + index + 1, result_len + 1);
	return (free(input), result);
}

/**
 * @function: ft_str_replace
 * @brief: takes a input string and replaces the env variable with the substring
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
	int		env_len;

	if (!input || !rep_substring || index < 0)
		return (NULL);
	input_len = ft_strlen(input);
	env_len = ft_env_len(input + index);
	rep_len = ft_strlen(rep_substring);
	result_len = input_len - env_len + rep_len;
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, input, index + 1);
	ft_strlcat(result, rep_substring, result_len + 1);
	ft_strlcat(result, input + index + env_len, result_len + 1);
	return (free(input), result);
}
