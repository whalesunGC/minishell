/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_e.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:37:52 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 17:10:42 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_str_replace_val_var
 * @brief: takes a input string and replaces the env variable with the substring
 * 
 * @param input: input string.
 * @param index: start position where replacement substring begins.
 * @param rep_substr: replacement substring.
 * 
 * @return: returns a new string that has the substring replaced
 */
char	*ft_str_replace_val_var(char *input, int index, char *rep_substring,
    t_ex_data *ex_data)
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
    ex_data->rem_count += rep_len + 1;
	return (free(input), result);
}

/**
 * @function: ft_remove_quote_val_var
 * @brief: removes all quotes from input string when not enclosed by quotes
 * untill the index "end"
 * returns new string  
 *
 * @param string: input string
 * @param end: end index
 * @param exp_data: exp_data struct
 * @return: new string with quotes removed when not enclosed by quotes up 
 * to index "end"
 */
char	*ft_remove_quote_val_var(char *string, int start, int end, t_ex_data *ex_data)
{
	int	i;

	if (!string)
		return (NULL);
	i = start - ex_data->rem_count;
	while (i < (end - ex_data->rem_count))
	{
		if (string[i] == '\'' && !ex_data->in_d_q)
			ex_data->in_s_q = !ex_data->in_s_q;
		if (string[i] == '\"' && !ex_data->in_s_q)
			ex_data->in_d_q = !ex_data->in_d_q;
		if ((string[i] == '\'') && !ex_data->in_d_q)
			string = ft_str_replace_val_var(string, i, "", ex_data);
		else if ((string[i] == '\"') && !ex_data->in_s_q)
			string = ft_str_replace_val_var(string, i, "", ex_data);
		else
			i++;
	}
	return (string);
}

void ft_free_int_index(int ***index)
{
    int i;

    i = 0;
    if ((*index))
    {
        while ((*index)[i])
        {
            free((*index)[i]);
            i++;
        }
        free((*index));
    }
}

static int ft_intarraylen(int *s)
{
    int len;

    len = 0;
    while (*s != 424242)
    {
        len++;
        s++;
    }
    return (len);
}

static int	*ft_intarraydup(int *s)
{
	int	    *ptr;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_intarraylen(s);
	ptr = (int *)malloc(sizeof(int) * (len + 1));
	if (!ptr)
		return (NULL);
	return ((int *)ft_memcpy(ptr, s, sizeof(int) * (len + 1)));
}

static void	handle_create_pair(int ***index, int j, int start, int end)
{
    int **new_index;
    int **temp;
    int k;

    new_index = (int **)malloc(sizeof(int *) * (j + 2));
    ft_memset(new_index, 0, sizeof(int *) * (j + 2));
    k = 0;
    if (*index)
    {
        while ((*index)[k])
        {
            new_index[k] = ft_intarraydup((*index)[k]);
            k++;
        }
    }
    new_index[j] = (int *)malloc(sizeof(int) * 3);
    new_index[j][0] = start;
    new_index[j][1] = end;
    new_index[j][2] = 424242;
    new_index[j + 1] = NULL;
    temp = *index;
    *index = new_index;
    ft_free_int_index(&temp);
}

/**
 * @function: handle_env_variable_val_var
 * @brief: takes identified parameter
 * and does variable expansion.
 *
 * @param input: address to the pointer of the
 * string(string by reference)
 * @param i: index value of where '$' is found
 * @param env: env variables copied from main
 * @param index: array of paired ints
 */
void	handle_env_variable_val_var(char **input, int *i, t_ex_data *ex_data)
{
	char		*env_var;
    int         start;
    int         end;

	env_var = ft_var_exp(input, *i, ex_data->env);
	expansion_replace_string(env_var, *i, input);
	if (env_var)
	{
        start = *i;
		*i += ft_strlen(env_var);
        end = *i;
        handle_create_pair(&ex_data->index, ex_data->j, start, end);
		free(env_var);
	}
}

/**
 * @function: handle_has_var
 * @brief: takes care of expansion within ft_expansion_tokens
 *
 * @param data: token data
 */
void	handle_has_var(t_lex_data *data, char **env, int *exit_status)
{
	t_ex_data   ex_data;
    int         i;

	ex_data.index = NULL;
    ex_data.env = env;
    ex_data.exit_status = exit_status;
    ex_data.j = 0;
    ex_data.rem_count = 0;
    ex_data.in_d_q = 0;
    ex_data.in_s_q = 0;
    i = 0;
	if (data->has_val_var)
    {
		data->raw_string = expansion_val_var(data->raw_string,
				&ex_data);
        while (ex_data.index[i])
        {
            if (i == 0)
                data->raw_string = ft_remove_quote_val_var(data->raw_string, 0, ex_data.index[i][0], &ex_data);
            else if (ex_data.index[i])
                data->raw_string = ft_remove_quote_val_var(data->raw_string, ex_data.index[i - 1][1], ex_data.index[i][0], &ex_data);
            i++;
        } 
        data->raw_string = ft_remove_quote_val_var(data->raw_string, ex_data.index[i - 1][1], ft_strlen(data->raw_string), &ex_data);
    }
	else
		data->raw_string = expansion_string(data->raw_string, 0,
				env, exit_status);
    ft_free_int_index(&ex_data.index);
}

/**
 * @function: expansion_val_var
 * @brief: takes input string that contains valid variables
 * and does variable expansion and quote removal
 *
 * @param input: any string, note that this
 * 	is malloced and needs to be freed after use.
 * @param env: env variables copied from main
 *
 * @return: returns expanded string.
 */
char	*expansion_val_var(char *input, t_ex_data *ex_data)
{
	int		in_single_quote;
	int		in_d_quote;
	int		i;
	char	*status;

	in_single_quote = 0;
	in_d_quote = 0;
	i = 0;
	status = ft_itoa(*ex_data->exit_status);
	while (input[i])
	{
		handle_quote_status_val_var(input, &in_single_quote, &in_d_quote, &i);
		if ((input[i] == '$' && input[i + 1] == '?'))
			input = ft_str_replace(input, i, status);
		else if ((input[i] == '$' && ft_is_env(input[i + 1]))
			&& (!in_single_quote || in_d_quote))
        {
			handle_env_variable_val_var(&input, &i, ex_data);
            ex_data->j += 1;
        }
		else
			i++;
	}
	return (free(status), input);
}
