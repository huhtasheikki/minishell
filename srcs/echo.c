/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 15:08:17 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/12 19:00:50 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*******************************************************************************
** ECHO
*******************************************************************************
**
**   The echo utility writes any specified operands, separated by single blank
**   (` ') characters and followed by a newline (`\n') character, to the stan-
**   dard output.
**
*******************************************************************************
*/

int		ft_echo(int fd, char **argv)
{
	int		i;

	i = 1;
	if (ft_strcmp(argv[0], "echo"))
		return (1);
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', fd);
	}
	if (!argv[1] || ft_strcmp(argv[1], "-n"))
		ft_putchar_fd('\n', fd);
	return (0);
}
