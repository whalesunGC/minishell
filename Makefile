# Compiler and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes
RM        := rm -f
LDFLAGS = -lreadline

# Source files names for each directory
LEXER_FILES = lexer.c	tokenize.c	lexer_utils.c	ft_split_ignore_quotes.c	ft_strchr_ignore_quotes.c
EXPANSION_FILES = expansion.c	expansion_utils_a.c
SIGNAL_FILES = signal_handler.c

# Directories
EXPANSION_DIR = 01_Expansion
LEXER_DIR = 02_Lexing
SIGNAL_DIR = 07_Signals

# Program name
NAME = minishell

# Source and object files
EXPANSION_SRCS = $(addprefix $(EXPANSION_DIR)/, $(EXPANSION_FILES))
LEXER_SRCS = $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
SIGNAL_SRCS = $(addprefix $(SIGNAL_DIR)/, $(SIGNAL_FILES))
SRCS = $(EXPANSION_SRCS) $(LEXER_SRCS) $(SIGNAL_SRCS) minishell.c 
		
OBJS = $(SRCS:.c=.o)

# Path to the Libft directory and its static library
LIBFT_DIR = Libft
LIBFT     = $(LIBFT_DIR)/libft.a

# Default target
all: $(NAME)

# Ensure libft.a is built before building minishell
$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR) all bonus clean

# Rule to create push_swap
$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Create mandatory object files from SRC and BONUS_S
%.o:		%.c
			$(CC) $(CFLAGS) -c $^ -o $@

# Clean up object files
clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 

# Clean up object files and the executable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything from scratch
re: fclean all

# Phony targets to prevent conflicts with files named 'clean', 'fclean', or 'all'
.PHONY: all bonus clean fclean re