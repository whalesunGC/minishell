#include "../includes/minishell.h"

/**
 * @function: ft_input_validation
 * @brief: function validates the input string for syntax errors
 * 
 * @param input: input string from readline
 * @return: modified string that is delimited for the lexer module.
 */
char *ft_input_validation(char *input)
{
	if (!check_quotes_balance(input) || !check_parentheses_balance(input))
	{
		ft_printf("Error: Unbalanced quotes or parentheses\n");
		free(input);
		return (NULL);
	}
	if (!check_pipe_placement(input))
	{
		ft_printf("Error: Invalid pipe placement\n");
		free(input);
		return (NULL);
	}
	return (input);
}

/**
 * @function: check_quotes_balance
 * @brief: function checks if the quotes in the input string are balanced
 * 
 * @param input: input string from readline
 * @return: 1 if balanced, 0 if not
 */
int check_quotes_balance(const char *input)
{
    int single_quote;
    int double_quote;

    single_quote = 0;
    double_quote = 0;
    while (*input)
    {
        if (*input == '\'' && !double_quote)
            single_quote = !single_quote;
        else if (*input == '"' && !single_quote)
            double_quote = !double_quote;
        input++;
    }
    return (!single_quote && !double_quote);
}

/**
 * @function: check_parentheses_balance
 * @brief: function checks if the parentheses in the input string are balanced
 * 
 * @param input: input string from readline
 * @return: 1 if balanced, 0 if not
 */
int check_parentheses_balance(const char *input)
{
    int count;

    count = 0;
    while (*input)
    {
        if (*input == '(')
            count++;
        else if (*input == ')')
        {
            if (count == 0)
                return (0);
            count--;
        }
        input++;
    }
    return (count == 0);
}

/**
 * @function: check_pipe_placement
 * @brief: function checks if the pipe placement in the input string is valid
 * 
 * @param input: input string from readline
 * @return: 1 if valid, 0 if not
 */
int check_pipe_placement(const char *input)
{
    int     in_quotes;
    char    quote_char;
    int     last_char_pipe;
    int     found_non_space;

    in_quotes = 0;
    quote_char = 0;
    last_char_pipe = 0;
    found_non_space = 0;
    while (*input)
    {
        if ((*input == '\'' || *input == '"')
            && (!in_quotes || *input == quote_char))
        {
            in_quotes = !in_quotes;
            if (in_quotes)
                quote_char = *input;
            else
                quote_char = 0;
        }
        if (!in_quotes)
        {
            if (*input == '|')
            {
                if (!found_non_space || last_char_pipe)
                    return (0);
                
                last_char_pipe = 1;
                found_non_space = 0;
            }
            else if (!ft_iswhitespace(*input))
            {
                found_non_space = 1;
                last_char_pipe = 0;
            }
        }
        input++;
    }
    return (!last_char_pipe);
}
