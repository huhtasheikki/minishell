/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:48:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/12/16 22:01:55 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token			*new_token(size_t size)
{
	t_token		*token;

	if (!(token = ft_memalloc(sizeof(t_token))))
		exit(1); // PROPER ERROR FUNCTION NEEDED WITH OWN ERRNO
	if (!(token->word = ft_strnew(size)))
		exit(1); // SAME AS ABOVE
	token->next = NULL;
	return (token);
}

int		check_state(int state, char c, char *quote)
{
	if (state == STATE_IN_GENERAL)
	{
		if (c == '\\' || c == '\'' || c == '"')
			return (STATE_IN_QUOTED);
		if (ft_strchr(METACHARS, c))
			return (STATE_IN_OPERATOR);
		else
			return (STATE_IN_GENERAL);
	}
	if (state == STATE_IN_QUOTED)
	{
		if (*quote == '\\' || c == *quote)
		{
			*quote = 0;
			return (STATE_IN_GENERAL);
		}
		else
			return (STATE_IN_QUOTED);
	}
	if (state == STATE_IN_OPERATOR && ft_strchr(METACHARS, c))
		return (STATE_IN_OPERATOR);
	return (STATE_IN_GENERAL); // IS THIS OK?
}

t_token			*init_scanner(t_lexer *lexer, char *quote, int size)
{
	t_token		*token;
	char		*temp;

	token = lexer->tokens;
	while (token->next)
		token = token->next;
	if (lexer->state != STATE_IN_GENERAL && token->word) // or token->word[0]?
	{
		temp = ft_strnew(ft_strlen(token->word) + size + 1);
		temp = ft_strcat(temp, token->word);
		free(token->word);
		token->word = temp;
	}
	else
	{
		token->next = new_token(size);
		token = token->next;
	}
	*quote = lexer->quote;
//	state = lexer->state;
	return (token);
}

int				general_machine(char *input, t_token *tok, int i, char *quote)
{
	int		j;

	j = ft_strlen(tok->word);
	if (input[i] == '\'' || input[i] == '"' || input[i] == '\\')
		*quote = input[i];
	if (input[i] == ' ')
	{
		if (j == 0)
			return (1);
		tok->word[j] = '\0';
		if (!(tok->next = new_token(ft_strlen(input) - i)))
			return (-1); // OR ERROR_FUN
		return (1);
	}
	if (ft_strchr(METACHARS, input[i]))
	{
		if (j > 0 && tok->type != TOKEN_OPERATOR)
		{
			tok->word[j] = '\0';
			if (!(tok->next = new_token(ft_strlen(input) - i)))
				return (-1); // OR ERROR_FUN
			tok = tok->next;
			j = 0;
		}
		tok->type = TOKEN_OPERATOR;
		tok->word[j] = input[i];
		return (1);
	}
	tok->type = TOKEN_WORD;
	tok->word[j] = input[i];
	return (1);
}

int				quote_machine(char *input, t_token *tok, int i, char *quote)
{
	tok->word[ft_strlen(tok->word)] = input[i];
	(void)quote; // remove
//	if (input[i] == *quote)
//		*quote = 0;
	return (1);
}

int				operator_machine(char *input, t_token *tok, int i, char *quote)
{
	int			j;

	j = ft_strlen(tok->word);
	if (ft_strchr(METACHARS, input[i]))
	{
		tok->word[j] = input[i];
		tok->type = TOKEN_OPERATOR;
	}
	else
	{
		tok->word[j] = '\0';
		if (!(tok->next = new_token(ft_strlen(input) - i)))
			return (-1); // OR ERROR_FUN WITH MALLOCERROR
		return (general_machine(input, tok->next, i, quote));
	}
	return (1);
}

int				scanner2(char *input, int size, t_lexer *lexer)
{
	t_token		*token;
	char		quote;
	int			i;
	int			j;

	token = init_scanner(lexer, &quote, size);
	i = 0;
	j = ft_strlen(token->word);
	if (size == 0)
		return (0);
	while (i < size) // should it stop at '\0' or this
	{
		if (lexer->state == STATE_IN_GENERAL)
			general_machine(input, token, i, &lexer->quote);
		if (lexer->state == STATE_IN_QUOTED)
			quote_machine(input, token, i, &lexer->quote);
		if (lexer->state == STATE_IN_OPERATOR)
			operator_machine(input, token, i, &lexer->quote);
		if (token->next)
			token = token->next;
		lexer->state = check_state(lexer->state, input[i++], &lexer->quote);
	}
	return (1);
}

/*
READ INPUT
SPLIT INPUT INTO TOKENS
	if backlash before newline+end of input READ INPUT AGAIN
EXPANSION
	brace expansion
	tilde
	parameter and variable
	command substitution
	arithmetic
	word splitting
	pathname
PARSE TOKENS TO SIMPLE COMMANDS (& other later)
	CREATE ABSTRACT SYNTAX TREE FROM COMMANDS
	CHECK THAT THE COMMAND WORKS WITH SHELL GRAMMAR
EXECUTE COMMAND TREE
	WAIT TILL ALL DONE
REPEAT
*/
