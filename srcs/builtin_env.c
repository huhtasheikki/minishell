/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/12 15:31:26 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_options(char *flags, t_list *envl)
{
	int		i;
	int		options;

	i = 1;
	options = 0;
	while (flags[i])
	{
		if (flags[i] == 'i')
		{
			ft_printf("#ft_env clearing environ\n"); // v-flag option, not always
			ft_lstdel(&envl->next, &ft_lstfree);
//			options |= ENV_I_FLAG;
		}
		else if (flags[i] == 'P')
			options |= ENV_P_FLAG;
//		else if (flags[i] == 'S')
//			options |= ENV_S_FLAG;
		else if (flags[i] == 'u')
			options |= ENV_U_FLAG;
//		if (flags[i] == 'v')
//			options |= ENV_V_FLAG;
		else
			return (-1); // input error
		i++;
	}
	return (options);
}

int		init_env(char **argv, t_list *envl)
{
//	t_list	*new_envl;
	char	path[1024];
	char	altpath[1024];
	char	**envp;
	char	*ptr;
	int		i;
	int		options;
	int		temp;

	i = 0;
	options = 0;
	temp = 0;
//	if (!(new_envl = ft_lstnew(NULL, 0)))
//		return (-1); // error fun;
	while (argv[i])
	{
		temp = 0;
		if (argv[i][0] == '-')
		{
			if ((temp = get_options(argv[i], envl) == -1))
				return (-1); // error;
			if (temp > 8 && temp != 16) // P and/or S and/or U flags cannot be together on
				return (-1); // input error
			else if (temp & ENV_P_FLAG)
			{
				ft_bzero(altpath, 1024);
				ft_strcat(altpath, argv[++i]);
			}
//			if (temp & ENV_S_FLAG)
//				printf("STRING to ENVL %s\n", argv[++i]);
			else if (temp & ENV_U_FLAG)
				ft_unsetenv(argv[++i], envl);
			options |= temp & ENV_P_FLAG;
		}
		else
			break;
		i++;
	}
	while (argv[i])
	{
		if ((ptr = ft_strchr(argv[i], '='))) //do better error check
		{
			*ptr = '\0';
			ft_setenv(argv[i], ++ptr, 1, envl);
		}
		else
			break;
		i++;
	}
	if (argv[i])
	{
		if (options & ENV_P_FLAG)
			search_command(argv[i], altpath, path, 1024); //if ret value -1 error, 0 not found, positive number then command found;
		else
			search_command(argv[i], ft_getenv("PATH", envl), path, 1024);
		if (!(envp = make_envp(envl)))
			return (err_minishell(ERR_MALLOC));
		execve(path, argv + i, envp);
	}
	else
		ft_lstiter(envl->next, &ft_lstprint);
	return (0);
}

int		builtin_env(char **argv, t_list *envl)
{
	pid_t	pid;
	int		options;

	options = 0;
	if ((pid = fork()) < 0)
		return (-1); // err_fun("fork error");
	else if (pid == 0)
	{
		exit(init_env(argv, envl)); //make sure this is correct!
	}
	else
		wait(NULL);
/*
	if (argc == 1)
		ft_lstiter(envl->next, &ft_lstprint);

	else
	{
		//fork here so we can edit envl
		init_env(argv, envl);
	}
*/
	return (0);
}
