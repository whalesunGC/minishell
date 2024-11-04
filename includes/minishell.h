/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:07:31 by wichee            #+#    #+#             */
/*   Updated: 2024/10/05 12:16:59 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include "../Libft/ft_printf.h"
# include "input.h"
# include "expansion.h"
# include "lexer.h"
# include "parser.h"
# include "signal_handler.h"
# include "built_in.h"
# include "redirections.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <termios.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <limits.h>
# include <fcntl.h>

#endif
