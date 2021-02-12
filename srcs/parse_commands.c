/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:20:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 18:36:23 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_lst(void *data, size_t i)
{
	char		**argv;

	argv = data;
	while (argv && *argv)
	{
		ft_bzero(*argv, ft_strlen(*argv));
		free(*argv);
		argv++;
	}
	ft_bzero(data, i);
	free(data);
}

int				parse_commands(t_lexer *lex)
{
	t_list		*commands;
	t_list		*start;
	char		**argv;

	commands = create_commandlist(lex->tokens);
	start = commands;
	while (commands->next)
	{
		commands = commands->next;
		argv = commands->content;
		if (!argv[0])
			continue;
		if (ft_builtin(argv, lex->envl) > 0)
			call_simple_fun(argv, lex->envl);
	}
	ft_lstdel(&start, &delete_lst);
	return (0);
}
