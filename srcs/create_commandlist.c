/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commandlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:25:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/10 01:00:05 by hhuhtane         ###   ########.fr       */
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

static int	token_to_argument(t_token *tok, char **argv, int *i)
{
	t_token		*sub;

	if (!(argv[*i] = ft_memalloc(sizeof(char) * get_tokenlen(tok) + 1)))
	{
		ft_strarrdel(&argv);
		return (-1);
	}
	sub = tok;
	ft_strcat(argv[*i], sub->word);
	while (sub->subtoken)
	{
		sub = sub->subtoken;
		ft_strcat(argv[*i], sub->word);
	}
	*i = *i + 1;
	return (0);
}

t_list		*tok_to_list(t_token *tok, t_list *comm, char **argv, size_t size)
{
	int			i;

	i = 0;
	while (tok->next)
	{
		tok = tok->next;
		if (tok->type == TOKEN_EMPTY)
			continue;
		if (tok->type == TOKEN_OPERATOR)
		{
			i = 0;
			ft_lstappend(&comm, ft_lstnew(argv, sizeof(char*) * size));
			free(argv);
			if (!tok->next)
				return (comm);
			size = get_commandsize(tok->next) + 1;
			if (!(argv = ft_memalloc(sizeof(char*) * size)))
				return (NULL);
		}
		else if (token_to_argument(tok, argv, &i) == -1)
			return (NULL);
	}
	ft_lstappend(&comm, ft_lstnew(argv, sizeof(char*) * size));
	free(argv);
	return (comm);
}

t_list		*create_commandlist(t_token *tok)
{
	t_list		*commands;
	char		**argv;
	size_t		size;
	int			i;

	i = 0;
	size = get_commandsize(tok->next) + 1;
	if (!(argv = ft_memalloc(sizeof(char*) * size)))
		return (NULL);
	if (!(commands = ft_lstnew(NULL, 0)))
		return (NULL);
	return (tok_to_list(tok, commands, argv, size));
}
