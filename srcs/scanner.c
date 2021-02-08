/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:48:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/08 14:18:17 by hhuhtane         ###   ########.fr       */
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
*/

t_token		*general_op(char *input, t_token *tok, int j, t_lexer *lex)
{
	if (j > 0 && tok->type != TOKEN_OPERATOR)
	{
		tok = get_last_token(lex->tokens);
		if (!(tok->next = new_token(ft_strlen(input))))
			return (NULL); // OR ERROR_FUN
		tok = tok->next;
		j = 0;
	}
	tok->type = TOKEN_OPERATOR;
	tok->word[j] = *input;
	return (tok);
}

t_token		*general_machine(char *input, t_token *tok, int j, t_lexer *lex)
{
	if (*input == '\'' || *input == '"' || *input == '\\')
	{
		if (tok->word[0])
		{
			tok->subtoken = new_token(ft_strlen(input));
			tok = tok->subtoken;
			j = 0;
		}
		lex->quote = *input;
	}
	if (*input == ' ' || *input == '\t')
	{
		if (j == 0)
			return (tok);
		tok = get_last_token(lex->tokens);
		if (!(tok->next = new_token(ft_strlen(input))))
			return (NULL); // OR ERROR_FUN
		return (tok->next);
	}
	if (ft_strchr(METACHARS, *input))
		return (general_op(input, tok, j, lex));
	tok->type = TOKEN_WORD;
	tok->word[j] = *input;
	return (tok);
}

t_token		*quote_machine(char *input, t_token *tok, int i, t_lexer *lex)
{
	tok->word[ft_strlen(tok->word)] = input[i];
	if (input[i] == '\'' || input[i] == '"' || input[i] == '\\')
	{
		if (ft_isspace(input[i + 1] || ft_strchr(METACHARS, input[i + 1])))
		{
			tok = get_last_token(lex->tokens);
			if (!(tok->next = new_token(ft_strlen(input) - i)))
				return (NULL); // ERRORR FUN?
			return (tok->next);
		}
		tok->subtoken = new_token(ft_strlen(input) - i);
		tok = tok->subtoken;
	}
	return (tok);
}

t_token		*op_machine(char *input, t_token *tok, int i, t_lexer *lex)
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

int			scanner2(char *input, int size, t_lexer *lexer)
{
	t_token		*tok;
	char		quote;
	int			i;
	int			j;

	tok = init_scanner(lexer, &quote, size);
	i = 0;
	j = ft_strlen(tok->word);
	if (size == 0)
		return (0);
	while (i < size)
	{
		if (lexer->state == STATE_IN_GENERAL)
			tok = general_machine(input + i, tok, ft_strlen(tok->word), lexer);
		if (lexer->state == STATE_IN_QUOTED)
			tok = quote_machine(input + i, tok, 0, lexer);
		if (lexer->state == STATE_IN_OPERATOR)
			tok = op_machine(input + i, tok, 0, lexer);
		lexer->state = check_state(lexer->state, input[i++], &lexer->quote);
	}
	if (lexer->state == STATE_IN_QUOTED)
		return ((lexer->mode = PROMPT_QUOTE));
	return (1);
}
