/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commandlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:25:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/09 19:59:03 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		get_commandsize(t_token *token)
{
	size_t		size;

	size = 0;
	while (token && token->type != TOKEN_OPERATOR)
	{
		token = token->next;
		++size;
	}
	return (size);
}

size_t		get_tokenlen(t_token *token)
{
	int			len;

	len = ft_strlen(token->word);
	while (token->subtoken)
	{
		token = token->subtoken;
		len += ft_strlen(token->word);
	}
	return (len);
}

t_list		*create_commandlist(t_token *tok)
{
	t_list		*commands;
	t_token		*sub;
	char		**argv;
	size_t		size;
	int			i;

	i = 0;
	size = get_commandsize(tok->next) + 1;
	if (!(argv = ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	if (!(commands = ft_lstnew(NULL, 0)))
		return (NULL);
	while (tok->next)
	{
		tok = tok->next;
		if (tok->type == TOKEN_EMPTY)
			continue;
		if (tok->type == TOKEN_OPERATOR)
		{
			i = 0;
			ft_lstappend(&commands, ft_lstnew(argv, sizeof(char*) * size));
			free(argv);
			if (tok->next)
			{
				size = get_commandsize(tok->next) + 1;
				if (!(argv = ft_memalloc(sizeof(char*) * size)))
					return (NULL);
			}
			else
				return (commands);
		}
		else
		{
			if (!(argv[i] = ft_memalloc(sizeof(char) * get_tokenlen(tok) + 1)))
				return ((t_list*)ft_strarrdel(&argv));
			sub = tok;
			ft_strcat(argv[i], sub->word);
			while (sub->subtoken)
			{
				sub = sub->subtoken;
				ft_strcat(argv[i], sub->word);
			}
			i++;
		}
	}
	ft_lstappend(&commands, ft_lstnew(argv, sizeof(char*) * size));
	free(argv);
	return (commands);
}

int			parse_commands(t_list *commands, t_lexer *lex)
{
	char		**argv;

	while (commands->next)
	{
		commands = commands->next;
		argv = commands->content;
		if (ft_builtin(argv, lex->envl) > 0)
			call_simple_fun(argv, lex->envl);
	}
	return (0);
}
