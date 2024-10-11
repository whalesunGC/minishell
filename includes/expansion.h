/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:06:36 by wichee            #+#    #+#             */
/*   Updated: 2024/10/07 12:07:03 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANSION_H
# define EXPANSION_H

//expansion.c
char	*expansion(char *input);
char	*ft_env_search(char *var);
char	*ft_var_exp(char **input, int start_index);
int		ft_env_len(const char *input);

//expansion_utils_a.c
char	*ft_str_replace(char *input, int index, char *rep_substring);

#endif
