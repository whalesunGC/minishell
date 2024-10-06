# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
RM        := rm -f
LDFLAGS = -lreadline

# Source files names for each directory
LEXER_FILES = lexer.c	\

# Directories
LEXER_DIR = 01_Lexing

# Program name
NAME = minishell

# Source and object files
LEXER_SRCS = $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
SRCS = minishell.c $(LEXER_SRCS)
		
OBJS = $(SRCS:.c=.o)

# Path to the Libft directory and its static library
LIBFT_DIR = Libft
LIBFT     = ${LIBFT_DIR}/libft.a

# Default target
all: ${NAME}

# Ensure libft.a is built before building minishell
${LIBFT}:
			${MAKE} -C ${LIBFT_DIR} all bonus clean

# Rule to create push_swap
${NAME}:	${OBJS} ${LIBFT}
			${CC} ${CFLAGS} $^ -o $@ ${LDFLAGS}

# Create mandatory object files from SRC and BONUS_S
%.o:		%.c
			$(CC) $(CFLAGS) -c $^ -o $@

# Clean up object files
clean:
	rm -rf $(OBJS)
	${MAKE} -C ${LIBFT_DIR} clean 

# Clean up object files and the executable
fclean: clean
	rm -f $(NAME)
	${MAKE} -C ${LIBFT_DIR} fclean

# Rebuild everything from scratch
re: fclean all

# Phony targets to prevent conflicts with files named 'clean', 'fclean', or 'all'
.PHONY: all bonus clean fclean re
