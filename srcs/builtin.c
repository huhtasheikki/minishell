/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:04:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/16 13:39:56 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_unsetenv(char **argv, t_list *envl)
{
	if (!argv[1])
	{
		err_minishell(ERR_TOO_FEW_ARGS, argv[0]);
		return (0);
	}
	argv++;
	while (*argv)
	{
		ft_unsetenv(*argv, envl);
		argv++;
	}
	return (0);
}

int		ft_builtin(char **argv, t_list *envl)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(1, argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, envl));
	if (!ft_strcmp(argv[0], "setenv"))
		return (builtin_setenv(argv, envl));
	if (!ft_strcmp(argv[0], "unsetenv"))
		return (builtin_unsetenv(argv, envl));
	if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(argv, envl));
	if (!ft_strcmp(argv[0], "exit"))
	{
		if (argv[1])
			err_minishell(ERR_TOO_MANY_ARGS, argv[0]);
		else
			exit(0);
		return (ft_printf("ft_exit\n"));
	}
	return (1);
}
