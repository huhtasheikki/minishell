/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:48:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/05 18:08:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Lexical Structure
**
** The shell splits input lines into words at blanks and tabs with the
** following exceptions. The characters &, |, ;, <, >, (, and ) form
** separate words. If doubled in &&, ||, <<, or >>, these pairs form
** single words. These parser metacharacters may be made part of other
** words, or have their special meaning prevented, by preceding them with
** a backslash (\). A newline preceded by a \ is equivalent to a blank.
**
** Strings enclosed in matched pairs of quotations, ', `, or ", form parts
** of a word; metacharacters in these strings, including blanks and tabs,
** do not form separate words. These quotations have semantics to be
** described later. Within pairs of ' or " characters, a newline preceded
** by a \ gives a true newline character.
**
** When the shell's input is not a terminal, the character # introduces
** a comment that continues to the end of the input line. This special
** meaning is prevented when preceded by \ and in quotations using `, ',
** and ".
**
*/

t_token		*new_token(size_t size)
{
	t_token		*token;

	if (!(token = ft_memalloc(sizeof(t_token))))
		exit(1); // PROPER ERROR FUNCTION NEEDED WITH OWN ERRNO
	if (!(token->word = ft_strnew(size)))
		exit(1); // SAME AS ABOVE
	token->type = TOKEN_EMPTY;
	token->subtoken = NULL;
	token->next = NULL;
	return (token);
}

int			check_state(int state, char c, char *quote)
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

t_token		*get_last_token(t_token *token) // NEW. OK?
{
	while (token->next)
		token = token->next;
	return (token);
}

t_token		*get_last_subtoken(t_token *token) // NEW. OK?
{
	while (token->next)
		token = token->next;
	if (token->subtoken)
		token = get_last_token(token->subtoken);
	return (token);
}

t_token		*init_scanner(t_lexer *lexer, char *quote, int size)
{
	t_token		*token;
	char		*temp;

	if (lexer->state != STATE_IN_QUOTED)
	{
		token = get_last_token(lexer->tokens);
		lexer->state = STATE_IN_GENERAL;
	}
	else
		token = get_last_subtoken(lexer->tokens);
	if (lexer->state != STATE_IN_GENERAL && token->word) // or token->word[0]?
	{
		temp = ft_strnew(ft_strlen(token->word) + size + 1);
		temp = ft_strcat(temp, token->word);
		free(token->word);
		token->word = temp;
	}
	else
	{
		token->next = new_token(size); //change this to just token;
		token = token->next;
	}
	*quote = lexer->quote;
	return (token);
}

t_token		*general_machine(char *input, t_token *tok, int i, t_lexer *lex)
{
	int		j;

	j = ft_strlen(tok->word);
	if (input[i] == '\'' || input[i] == '"' || input[i] == '\\')
	{
		if (tok->word[0])
		{
			tok->subtoken = new_token(ft_strlen(input) - i);
			tok = tok->subtoken;
			j = 0;
		}
		lex->quote = input[i];
	}
	if (input[i] == ' ' || input[i] == '\t')
	{
		if (j == 0)
			return (tok);
		tok = get_last_token(lex->tokens);
		if (!(tok->next = new_token(ft_strlen(input) - i)))
			return (NULL); // OR ERROR_FUN
		return (tok->next);
	}
	if (ft_strchr(METACHARS, input[i]))
	{
		if (j > 0 && tok->type != TOKEN_OPERATOR)
		{
			tok = get_last_token(lex->tokens);
			if (!(tok->next = new_token(ft_strlen(input) - i)))
				return (NULL); // OR ERROR_FUN
			tok = tok->next;
			j = 0;
		}
		tok->type = TOKEN_OPERATOR;
		tok->word[j] = input[i];
		return (tok);
	}
	if (tok->word[0] == '\'' || tok->word[0] == '"' || tok->word[0] == '\\')
	{
		tok->subtoken = new_token(ft_strlen(input) - i);
		tok = tok->subtoken;
		j = 0;
	}
	tok->type = TOKEN_WORD;
	tok->word[j] = input[i];
	return (tok);
}

t_token			*quote_machine(char *input, t_token *tok, int i, char *quote)
{
	tok->word[ft_strlen(tok->word)] = input[i];
	(void)quote; // remove
	return (tok);
}

t_token			*operator_machine(char *input, t_token *tok, int i, t_lexer *lex)
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
		if (!(tok->next = new_token(ft_strlen(input) - i)))
			return (NULL); // OR ERROR_FUN WITH MALLOCERROR
		return (general_machine(input, tok->next, i, lex));
	}
	return (tok);
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
			token = general_machine(input, token, i, lexer);
		if (lexer->state == STATE_IN_QUOTED)
			token = quote_machine(input, token, i, &lexer->quote);
		if (lexer->state == STATE_IN_OPERATOR)
			token = operator_machine(input, token, i, lexer);
		lexer->state = check_state(lexer->state, input[i++], &lexer->quote);
	}
	if (lexer->state == STATE_IN_QUOTED)
	{
		lexer->mode = PROMPT_QUOTE;
		return (2);
	}
	return (1);
}
