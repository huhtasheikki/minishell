/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:59:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/04 11:23:48 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char **str)
{
	char		*word;
	size_t		len;

	word = *str;
	len = ft_strlen(word);
	if (word[0] == '\'' || word[0] == '"')
	{
		ft_memmove(word, word + 1, len - 2);
		word[len - 2] = '\0';
	}
}

void	remove_escape(char **str)
{
	char		*word;

	word = *str;
	while (*word)
	{
		if (*word == '\\')
		{
			ft_memmove(word, word + 1, ft_strlen(word));
			word++;
		}
		word++;
	}
}

void	clean_token(t_token *token)
{
	t_token		*sub;

	sub = token->subtoken;
	while (sub)
	{
		remove_quotes(&sub->word);
		remove_escape(&sub->word);
		sub = sub->subtoken;
	}
	remove_quotes(&token->word);
	remove_escape(&token->word);
}
