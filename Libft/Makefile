CC		:=	cc
CFLAGS	:=	-g -Wall -Wextra -Werror
CPPFLAGS:=	-I .
AR		:=	ar -rcs
RM		:=	rm -f

NAME	=	libft.a

INCLUDE	=	libft.h

SRCS	=	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	ft_isascii.c	\
			ft_isprint.c	ft_strlen.c		ft_memset.c		ft_bzero.c		\
			ft_memcpy.c		ft_memmove.c	ft_strlcpy.c	ft_strlcat.c	\
			ft_toupper.c	ft_tolower.c	ft_strchr.c		ft_strrchr.c	\
			ft_strncmp.c	ft_memchr.c		ft_memcmp.c		ft_strnstr.c	\
			ft_atoi.c		ft_calloc.c		ft_strdup.c		ft_substr.c		\
			ft_strjoin.c	ft_strtrim.c	ft_split.c		ft_itoa.c		\
			ft_strmapi.c	ft_striteri.c	ft_putchar_fd.c	ft_putstr_fd.c	\
			ft_putendl_fd.c	ft_putnbr_fd.c	ft_atoll.c

BONUS_S	=	ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	\
			ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c	\
			ft_lstclear.c	ft_lstiter.c		ft_lstmap.c

PRINTF_S =	ft_printf.c		ft_printhexlow.c	ft_printhexup.c	\
			ft_printptr.c	ft_printstr.c		ft_printundeci.c	\
			ft_putunnbr.c	ft_printchar.c		ft_printdeci.c

DPRINTF_S =	ft_dprintf.c	ft_dprinthexlow.c	ft_dprinthexup.c	\
			ft_dprintptr.c	ft_dprintstr.c		ft_dprintundeci.c	\
			ft_dputunnbr.c	ft_dprintchar.c		ft_dprintdeci.c


GNL_S	=	get_next_line.c get_next_line_utils.c	\

OBJS	=	${SRCS:.c=.o}

BONUS_O	=	${BONUS_S:.c=.o}

PRINTF_O =	${PRINTF_S:.c=.o}

DPRINTF_O =	${DPRINTF_S:.c=.o}

GNL_O	=	${GNL_S:.c=.o}

all:		${NAME}

${NAME}:	${OBJS} $(PRINTF_O) $(DPRINTF_O) ${GNL_O}
			${AR} $@ $^

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@

bonus:		${BONUS_O}
			${AR} ${NAME} $^

clean:
			${RM} ${OBJS} ${BONUS_O} ${PRINTF_O} ${DPRINTF_O} ${GNL_O}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
