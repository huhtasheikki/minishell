/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:38:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/02 17:53:23 by hhuhtane         ###   ########.fr       */
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
			(path[1] == '.' && (path[2] == '\0' || path[2] == '/')))
			return (1);
	return (0);
}

char	*get_absolute_path(char *rel, t_list *envl, char *path)
{
	char	*cdpath;
	int		i;

	i = 0;
	if (is_absolute_path(rel))
		return (ft_strcpy(path, rel));
	if ((cdpath = ft_getenv("CDPATH", envl)))
	{
		if (search_command(rel, cdpath, path, 1024))
			return (path);
	}
	path = getcwd(path, 1024);
	path = ft_strcat(path, "/");
	path = ft_strcat(path, rel);
	return (path);
}

int		err_cd(int errorno, char *path)
{
	if (errorno == ERR_TOO_MANY_SYMLINKS)
		ft_printf("minishell: cd: Too many levels of symbolic links: %s\n",\
				path);
	else if (errorno == ERR_STAT)
		ft_printf("minishell: stat error: %s\n", path);
	else if (errorno == ERR_NOT_A_DIR)
		ft_printf("minishell: cd: not a directory: %s\n", path);
	else if (errorno == ERR_FILE_NOT_FOUND)
		ft_printf("minishell: cd: no such file or directory: %s\n", path);
	else if (errorno == ERR_NO_PERMISSION)
		ft_printf("minishell: cd: permission denied: %s\n", path);
	else
		ft_printf("minishell: cd: It just doesn't work today!\n");
	return (-1);
}

int		is_valid_path(char *path)
{
	t_stat		buf;

	if (lstat(path, &buf) == -1)
	{
		if (access(path, F_OK))
			return (err_cd(ERR_FILE_NOT_FOUND, path));
		if (access(path, X_OK))
			return (err_cd(ERR_NO_PERMISSION, path));
	}
	if ((buf.st_mode & S_IFMT) == S_IFLNK)
	{
		if (stat(path, &buf) == -1)
			return (err_cd(ERR_TOO_MANY_SYMLINKS, path));
	}
	if ((buf.st_mode & S_IFMT) != S_IFDIR)
		return (err_cd(ERR_NOT_A_DIR, path));
	if ((buf.st_mode & S_IXUSR) || (buf.st_mode & S_IXGRP))
		return (0);
	return (err_cd(ERR_NO_PERMISSION, path));
}

int		builtin_cd(int argc, char **argv, t_list *envl)
{
	char	path[1024];
	char	cwd[1024];
	char	*ptr;

	if (argc > 2)
		return (err_minishell(ERR_TOO_MANY_ARGS, argv[0]));
	if (argc == 2 && !ft_strcmp(argv[1], "-") && ft_getenv("OLDPWD", envl))
		ft_strcpy(path, ft_getenv("OLDPWD", envl));
	else if (argc == 2)
		get_absolute_path(argv[1], envl, path);
	else if ((ptr = ft_getenv("HOME", envl)))
		ft_strcpy(path, ft_getenv("HOME", envl));
	else
		return (err_minishell(ERR_HOME_NOT_SET, argv[0]));
	if (is_valid_path(path) == -1)
		return (-1);
	getcwd(cwd, 1024);
	ft_setenv("OLDPWD", cwd, 1, envl);
	if (chdir(path) == -1)
		return (err_cd(0, ""));
	getcwd(cwd, 1024);
	ft_setenv("PWD", cwd, 1, envl);
	return (0);
}
