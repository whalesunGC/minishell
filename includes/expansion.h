/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:06:36 by wichee            #+#    #+#             */
/*   Updated: 2024/10/19 18:21:41 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANSION_H
# define EXPANSION_H

//expansion.c
t_list	*expansion(t_list *token_data, char **env);
char	*expansion_string(char *input, int ignore_quote, char **env);
char	*ft_var_exp(char **input, int start_index, char **env);
int		ft_env_len(const char *input);

//expansion_utils_a.c
char	*ft_str_replace(char *input, int index, char *rep_substring);
char	*ft_str_insert(char *input, int index, char *insert_string);
char	*ft_env_search(char *var, char **env);
void	expansion_replace_string(char *env_var, int index, char **exp_input);

//expansion_utils_b.c
char	*ft_string_trim_ends(char **string);
t_list	*ft_expansion_tokens(t_list **token_data, char **env);
char	*ft_getenv(char *string, char **env);

//expansion_utils_c.c
int     ft_has_whitespace(char *string);
char    *ft_remove_quote(char *string);
int     ft_has_quote(char *string);
#endif
