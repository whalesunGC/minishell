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

#include "../Libft/libft.h"
#include "../Libft/ft_printf.h"
#include "signal_handler.h"
#include "lexer.h"
#include "expansion.h"
#include <signal.h>
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <fcntl.h>