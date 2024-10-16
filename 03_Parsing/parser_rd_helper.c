#include "../includes/minishell.h"

/**
 * @brief Adds a child node to the specified parent node
 *
 * @param parent The parent node to which the child node will be added
 * @param child The child node to be added
 */
void	add_child_node(t_ast_node *parent, t_ast_node *child)
{
	t_ast_node	*current;

	current = NULL;
	if (!parent->left)
		parent->left = child;
	else if (!parent->right)
		parent->right = child;
	else
	{
		current = parent->right;
		while (current->right)
			current = current->right;
		current->right = child;
	}
	child->parent = parent;
}

/**
 * @brief Checks if the current token matches the specified type
 *
 * @param context The parser context containing the current token
 * @param type The token type to check against
 * @return int 1 if the token type matches, 0 otherwise
 */
int	is_token_type(t_parser_context *context, t_token_type type)
{
	t_lex_data	*token_data;

	token_data = NULL;
	if (context->current_token == NULL)
		return (0);
	token_data = (t_lex_data *)context->current_token->content;
	return (token_data->type == type);
}

/**
 * @brief Advances the current token to the next token in the list
 *
 * @param context The parser context to update
 */
void	advance_token(t_parser_context *context)
{
	if (context->current_token != NULL)
		context->current_token = context->current_token->next;
}

/**
 * @brief Creates a new AST node with the specified type
 *
 * @param type The type of the AST node to create
 * @return t_ast_node* Pointer to the newly created AST node,
	or NULL if allocation fails
 */
t_ast_node	*create_ast_node(t_ast_node_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

/**
 * @brief Expects the current token to be of a specific type,
	advances if correct, sets error if not
 *
 * @param context The parser context containing the current token
 * @param expected_type The expected token type
 * @return int 1 if the token type matches, 0 otherwise
 */
int	expect_token(t_parser_context *context, t_token_type expected_type)
{
	if (!is_token_type(context, expected_type))
	{
		context->error = 1;
		context->error_message = ft_strdup("Unexpected token type");
		return (0);
	}
	advance_token(context);
	return (1);
}
