# Compiler and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -Iincludes -MMD -MP
RM        := rm -f
LDFLAGS = -lreadline

# Source files names for each directory
INPUT_FILES = input.c	input_utils.c	input_validation.c	input_validation_helper.c
LEXER_FILES = lexer.c	tokenize.c	lexer_utils.c	ft_split_ignore_quotes.c	ft_strchr_ignore_quotes.c
EXPANSION_FILES = expansion.c	expansion_utils_a.c	expansion_utils_b.c	expansion_utils_c.c
PARSER_FILES = parser.c	parser_utils_a.c	parser_utils_b.c	parser_rd_helper.c	parser_rd_helper_b.c	parser_recursive_descent.c	parser_print_tree.c	parser_ast_to_ll.c	parser_exec.c
REDIRECTION_FILES = path_construction.c	path_construction_utils.c
EXECUTION_FILES = single_command.c	single_command_utils1.c	single_command_utils2.c	single_command_utils3.c	single_command_utils4.c	single_command_utils5.c	single_command_utils6.c	single_command_utils7.c	single_command_utils8.c	single_command_utils9.c	multiple_commands.c	multiple_commands_utils1.c	multiple_commands_utils2.c	multiple_commands_utils3.c	multiple_commands_utils4.c	multiple_commands_utils5.c	multiple_commands_utils6.c	multiple_commands_utils7.c	multiple_commands_utils8.c	multiple_commands_utils9.c	free_pipes.c
BUILT_INS_FILES = cd.c	updating_env_after_cd.c	copy_envp.c	copy_envp_with_ac.c env.c	free_dup_envp.c	exit.c	exit1.c	pwd.c	free_tokens.c	echo.c	unset.c	export.c	export_utils1.c	export_utils2.c	export_utils3.c	export_utils4.c	export_utils5.c	export_utils6.c	export_utils7.c	ft_strcmp.c
SIGNAL_FILES = signal_handler.c	signal.c	signal_utils.c

# Directories
INPUT_DIR = 00_Input
LEXER_DIR = 01_Lexing
EXPANSION_DIR = 02_Expansion
PARSER_DIR = 03_Parsing
REDIRECTION_DIR = 04_Redirection
EXECUTION_DIR = 05_Execution
BUILT_INS_DIR = 06_Built-Ins
SIGNAL_DIR = 07_Signals

# Program name
NAME = minishell

# Source and object files
INPUT_SRCS = $(addprefix $(INPUT_DIR)/, $(INPUT_FILES))
LEXER_SRCS = $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))
EXPANSION_SRCS = $(addprefix $(EXPANSION_DIR)/, $(EXPANSION_FILES))
PARSER_SRS = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
REDIRECTION_SRCS = $(addprefix $(REDIRECTION_DIR)/, $(REDIRECTION_FILES))
EXECUTION_SRCS = $(addprefix $(EXECUTION_DIR)/, $(EXECUTION_FILES))
BUILT_INS_SRCS = $(addprefix $(BUILT_INS_DIR)/, $(BUILT_INS_FILES))
SIGNAL_SRCS = $(addprefix $(SIGNAL_DIR)/, $(SIGNAL_FILES))
SRCS = $(INPUT_SRCS) $(EXPANSION_SRCS) $(LEXER_SRCS) $(PARSER_SRS) $(REDIRECTION_SRCS) $(EXECUTION_SRCS) $(BUILT_INS_SRCS) $(SIGNAL_SRCS) minishell.c 
		
OBJS = $(SRCS:.c=.o)
DEPEND = $(SRCS:.c=.d)

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
	rm -rf $(OBJS) $(DEPEND)
	$(MAKE) -C $(LIBFT_DIR) clean 

# Clean up object files and the executable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything from scratch
re: fclean all

# Include dependency files, generated by -MMD -MP flags
-include $(DEPEND)

# Valgrind call
valgrind: $(NAME)
			valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)
			
valgrind_bash: $(NAME)
			valgrind --leak-check=full --trace-children=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp bash

# Phony targets to prevent conflicts with files named 'clean', 'fclean', or 'all'
.PHONY: all bonus clean fclean re
