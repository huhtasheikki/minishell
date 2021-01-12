/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:38:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/11 11:19:03 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_absolute_path(char *path)
{
	if (!path)
		return (0);
	if (path[0] == '/')
		return (1);
	if (path[0] == '.')
		if (path[1] == '\0' || path[1] == '/' || \
			(path[1] =='.' && (path[2] == '\0' || path[2] == '/')))
			return (1);
	return (0);
}

/*
int		change_absolute_path(char *path, t_list *envl)
{
	char	buf[1024];

	if (!path)
		return (0);
	if (getcwd(buf, 1024) == NULL)
		return (-1); // return (err_fun("getcwd error"));
	if (ft_setenv("OLDPWD", buf, 1, envl) == -1 && ft_setenv("PWD", path, 1, envl == -1)
		return (-1); // error_fun;
	
}
*/

char	*get_absolute_path(char *rel, t_list *envl, char *path)
{
	char	*cdpath;
	char	**paths;
	int		i;

	i = 0;
	if (is_absolute_path(rel))
		return (ft_strcat(path, rel));
	if ((cdpath = ft_getenv("CDPATH", envl)))
	{
		if (!(paths = ft_strsplit(cdpath, ':')))
			return (NULL); //error fun;
		while (paths[i])
		{
			path = ft_strcat(path, paths[i]);
			path = ft_strcat(path, "/");
			path = ft_strcat(path, rel);
			if (!access(path, F_OK))
			{
				ft_strarrdel(&paths);
				free(paths);
				return (path);
			}
			i++;
			ft_bzero(path, 1024);
		}
		ft_strarrdel(&paths);
		free(paths);
	}
	path = getcwd(path, 1024);
	path = ft_strcat(path, "/");
	path = ft_strcat(path, rel);
	return (path);
}

int		builtin_cd(char **argv, t_list *envl)
{
	char	path[1024];
	char	*ptr;
	int		argc;

	argc = ft_strarrlen(argv);
	ft_bzero(path, 1024);
	if (argc > 2)
		return (-1); // error_mess("too many args or something");
	if (argc == 1)
	{
		if ((ptr = ft_getenv("HOME", envl)))
			ft_strcat(path, ft_getenv("HOME", envl));
		else
			return (-1); //errorsomething;
	}
//		return (change_absolute(ft_getenv("HOME", envl), envl));
	else
		get_absolute_path(argv[1], envl, path);
	ft_printf("KANSIO VAIHTUU!!!!!!! %s\n", path);
	chdir(path); //error check?
	return (0);
}
