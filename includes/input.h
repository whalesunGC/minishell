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

// input.c
char	*input_clean(char *input);
char	*ft_input_swap_whitespace(char *input);
char	*ft_input_remove_extra_whitespace(char *input);
char	*ft_input_add_whitespace(char *input);
int		ft_add_whitespace_special(char **input, int i, int in_s_q, int in_d_q);

// input_utils.c
int		ft_iswhitespace(int i);
int		ft_isspecial(int i);
int		ft_add_whitespace_helper(char **input, int i, int delta);

// input_validation.c
char	*ft_input_validation(char *input);
int		check_pipe_placement(const char *input);
int		check_or_placement(const char *input);
int		check_and_placement(const char *input);

// input_validation_helper.c
int		check_quotes_balance(const char *input);
int		check_parentheses_balance(const char *input);
void	handle_quotes(int *in_quotes, char *quote_char, char current_char);
int		handle_pipe_flags(const char *input, int *found_non_space,
			int *last_char_pipe);
int		handle_seq_flags(const char **input, int *found_non_space, int *last_char_or,
			const char *seq);
#endif
