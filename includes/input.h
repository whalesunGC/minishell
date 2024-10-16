/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:22 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 21:49:32 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

//input.c
char	*input_clean(char *input);
char	*ft_input_swap_whitespace(char *input);
char	*ft_input_remove_extra_whitespace(char *input);
char	*ft_input_add_whitespace(char *input);
int		ft_add_whitespace_special(char **input, int i, int in_s_q, int in_d_q);

//input_utils.c
int		ft_iswhitespace(int i);
int		ft_isspecial(int i);
int		ft_add_whitespace_helper(char **input, int i, int delta);

//input_validation.c
char	*ft_input_validation(char *input);
int		check_quotes_balance(const char *input);
int		check_parentheses_balance(const char *input);
int		check_pipe_placement(const char *input);

#endif
