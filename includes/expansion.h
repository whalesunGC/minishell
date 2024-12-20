/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:06:36 by wichee            #+#    #+#             */
/*   Updated: 2024/11/20 21:55:59 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXPANSION_H
# define EXPANSION_H

# include "lexer.h"

//expansion.c
t_list	*expansion(t_list *token_data, char **env, int *exist_status);
char	*expansion_string(char *input, int ignore_quote, char **env,
			int *exist_status);
int		handle_quote_status(char *input, int *in_single_quote,
			int *in_d_quote, int *i);
void	handle_env_variable(char **input, int *i, char **env);
int		handle_quote_status_val_var(char *input, int *in_single_quote,
			int *in_d_quote, int *i);

//expansion_utils_a.c
char	*ft_str_replace(char *input, int index, char *rep_substring);
char	*ft_str_insert(char *input, int index, char *insert_string);
char	*ft_env_search(char *var, char **env);
void	expansion_replace_string(char *env_var, int index, char **exp_input);
void	handle_has_var(t_lex_data *data, char **env, int *exit_status);

//expansion_utils_b.c
t_list	*ft_expansion_tokens(t_list **token_data, char **env,
			int *exist_status);

//expansion_utils_c.c
int		ft_has_whitespace(char *string);
char	*ft_remove_quote(char *string);
t_list	**handle_word_split(char *string, t_list **current_token, char **env);
t_list	*ft_lstinsert(t_list *node, t_list *current);
int		has_env_variable(char *input, char **env, int i);

//expansion_utils_d.c
char	*ft_getenv(char *string, char **env);
char	*ft_var_exp(char **input, int start_index, char **env);
int		ft_env_len(const char *input);
char	*ft_remove_inquote(char *string);

//expansion_utils_e.c
char	*expansion_val_var(char *input, char **env,
			int *exit_status);
char	*ft_reset_quotes(char *env_var);	

#endif
