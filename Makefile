# Compiler and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes
RM        := rm -f
LDFLAGS = -lreadline

# Source files names for each directory
INPUT_FILES = input.c	input_utils.c	input_validation.c
LEXER_FILES = lexer.c	tokenize.c	lexer_utils.c	ft_split_ignore_quotes.c	ft_strchr_ignore_quotes.c
EXPANSION_FILES = expansion.c	expansion_utils_a.c
PARSER_FILES = parser.c	parser_utils_a.c	parser_rd_helper.c	parser_recursive_descent.c	parser_print_tree.c
BUILT_INS_FILES = cd.c	updating_env_after_cd.c	copy_envp.c	copy_envp_with_ac.c env.c	free_dup_envp.c	exit.c	pwd.c	free_tokens.c	count_arg_validity.c	echo.c
SIGNAL_FILES = signal_handler.c

# Directories
INPUT_DIR = 00_Input
LEXER_DIR = 01_Lexing
EXPANSION_DIR = 02_Expansion
PARSER_DIR = 03_Parsing
BUILT_INS_DIR = 06_Built-Ins
SIGNAL_DIR = 07_Signals

# Program name
NAME = minishell

# Source and object files
INPUT_SRCS = $(addprefix $(INPUT_DIR)/, $(INPUT_FILES))
LEXER_SRCS = $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
EXPANSION_SRCS = $(addprefix $(EXPANSION_DIR)/, $(EXPANSION_FILES))
PARSER_SRS = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
BUILT_INS_SRCS = $(addprefix $(BUILT_INS_DIR)/, $(BUILT_INS_FILES))
SIGNAL_SRCS = $(addprefix $(SIGNAL_DIR)/, $(SIGNAL_FILES))
SRCS = $(INPUT_SRCS) $(EXPANSION_SRCS) $(LEXER_SRCS) $(PARSER_SRS) $(BUILT_INS_SRCS) $(SIGNAL_SRCS) minishell.c 
		
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
