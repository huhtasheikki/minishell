/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 23:35:42 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/11 18:36:21 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		term_buffer[2048];

void	err_fatal(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	init_terminal_data (t_lexer *lex)
{
	t_list	*envl;
	char	*termtype;
	int		success;

	envl = lex->envl;
	termtype = ft_getenv("TERM", envl);
	if (termtype == 0)
		err_fatal("Specify a terminal type with `setenv TERM <yourtype>'.");
	success = tgetent (term_buffer, termtype);
	if (success < 0)
		err_fatal("Could not access the termcap data base.");
	if (success == 0)
		err_fatal("Terminal type is not defined.");
}

void	ft_termcaps(t_lexer *lex)
{
	t_list		*envl;
	char		*termtype;
	int			success;

	envl = lex->envl;
	termtype = ft_getenv("TERM", envl);
	success = tgetent(term_buffer, termtype);
}
