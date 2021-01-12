/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:04:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/12 16:26:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_unsetenv(char **argv, t_list *envl)
{
	argv++;
	while (*argv)
	{
		ft_unsetenv(*argv, envl);
		argv++;
	}
	return (0);
}

/*
int		builtin_cd(char **argv, t_list *envl)
{
	
}
*/

/*
int		builtin_env(char **argv, t_list *envl)
{
	(void)argv;

	ft_lstiter(envl->next, &ft_lstprint);
	return (1);
}
*/

int		ft_builtin(char **argv, t_list *envl)
{
	if (!ft_strcmp(argv[0], "echo"))
	{
//		ft_printf("ft_echo\n");
		return (ft_echo(1, argv));
	}
	if (!ft_strcmp(argv[0], "cd"))
	{
//		ft_printf("ft_cd\n");
		return (builtin_cd(argv, envl));
	}
	if (!ft_strcmp(argv[0], "setenv"))
	{
//		ft_printf("ft_setenv\n");
		return (builtin_setenv(argv, envl));
	}
	if (!ft_strcmp(argv[0], "unsetenv"))
	{
//		ft_printf("ft_unsetenv\n");
		return (builtin_unsetenv(argv, envl));
	}
	if (!ft_strcmp(argv[0], "env"))
	{
//		ft_printf("ft_env\n");
		return (builtin_env(argv, envl));
	}
	if (!ft_strcmp(argv[0], "exit"))
		return (ft_printf("ft_exit\n"));
	return (1);
}
