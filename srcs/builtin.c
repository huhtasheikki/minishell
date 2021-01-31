/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:04:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/25 16:38:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_unsetenv(int argc, char **argv, t_list *envl)
{
	if (argc < 2)
		return (err_minishell(ERR_TOO_FEW_ARGS, argv[0]));
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
	int		argc;

	argc = ft_strarrlen(argv);
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(1, argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argc, argv, envl));
	if (!ft_strcmp(argv[0], "setenv"))
		return (builtin_setenv(argc, argv, envl));
	if (!ft_strcmp(argv[0], "unsetenv"))
		return (builtin_unsetenv(argc, argv, envl));
	if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(argc, argv, envl));
	if (!ft_strcmp(argv[0], "exit"))
	{
		if (argc != 1)
			return (err_minishell(ERR_TOO_MANY_ARGS, argv[0]));
		else
			exit(0);
	}
	return (1);
}
