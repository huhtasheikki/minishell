/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/31 19:22:09 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** NOTIONS:
** - ENV with -i flag will print info that env has been cleared.
*/

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
			ft_printf("#ft_env clearing environ\n");
			ft_lstdel(&envl->next, &ft_lstfree);
		}
		else if (flags[i] == 'P')
			options |= ENV_P_FLAG;
		else if (flags[i] == 'u')
			options |= ENV_U_FLAG;
		else
			return (-1);
		i++;
	}
	return (options);
}

int		execute_env(char **argv, t_list *envl, char *altpath, int options)
{
	char	path[1024];
	char	**envp;
	int		ret;

	if (argv[0])
	{
		if (options & ENV_P_FLAG)
			ret = search_command(argv[0], altpath, path, 1024);
		else
			ret = search_command(argv[0], ft_getenv("PATH", envl), path, 1024);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (err_minishell(ERR_FILE_NOT_FOUND, argv[0]));
		if (!(envp = make_envp(envl))) // THIS IS NOT CORRECT!!! WRONG ERROR
			return (err_minishell(ERR_MALLOC, NULL));
		execve(path, argv, envp);
	}
	else
		ft_lstiter(envl->next, &ft_lstprint);
	return (0);
}

int		get_setenvs(int argc, char **argv, t_list *envl, int i)
{
	char	*ptr;

	while (i < argc && (ptr = ft_strchr(argv[i], '=')))
	{
		*ptr = '\0';
		if (ft_setenv(argv[i], ++ptr, 1, envl) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int		get_env_options(char **argv, t_list *envl, int *options, char *altpath)
{
	int		temp;
	int		i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		temp = 0;
		if ((temp = get_options(argv[i], envl)) == -1 || (temp > 8 && temp != 16))
			return (err_minishell(ERR_INVALID_INPUT, "env"));
		else if (temp & ENV_P_FLAG)
		{
			ft_strncpy(altpath, argv[++i], 1024);
			*options |= ENV_P_FLAG;
		}
		else if (temp & ENV_U_FLAG)
			ft_unsetenv(argv[++i], envl);
		i++;
	}
	return (i);
}

int		builtin_env(int argc, char **argv, t_list *envl)
{
	char	altpath[1024];
	pid_t	pid;
	int		options;
	int		i;

	i = 0;
	options = 0;
	if ((pid = fork()) < 0)
		return (-1); // err_fun("fork error");
	else if (pid == 0)
	{
		if ((i = get_env_options(argv, envl, &options, altpath)) < 0)
			return (-1);
		if ((i = get_setenvs(argc, argv, envl, i)) < 0)
			return (-1);
		exit(execute_env(argv + i, envl, altpath, options));
	}
	else
		wait(NULL);
	return (0);
}
