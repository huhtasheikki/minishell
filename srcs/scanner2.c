/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:48:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/06 10:01:21 by hhuhtane         ###   ########.fr       */
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

t_token		*new_token(size_t size)
{
	t_token		*token;

	if (!(token = ft_memalloc(sizeof(t_token))))
		exit(err_minishell(ERR_MALLOC, NULL));
	if (!(token->word = ft_strnew(size)))
		exit(err_minishell(ERR_MALLOC, NULL));
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
	return (STATE_IN_GENERAL);
}

t_token		*get_last_token(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

t_token		*get_last_subtoken(t_token *token)
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
	if (lexer->state != STATE_IN_GENERAL && token->word)
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
