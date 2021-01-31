/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:38:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/27 11:13:33 by hhuhtane         ###   ########.fr       */
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

char	*get_absolute_path(char *rel, t_list *envl, char *path)
{
	char	*cdpath;
	int		i;

	i = 0;
	if (is_absolute_path(rel))
		return (ft_strcat(path, rel));
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

int		builtin_cd(int argc, char **argv, t_list *envl)
{
	char	path[1024];
	char	cwd[1024];
	char	*ptr;

	ft_bzero(path, 1024);
	ft_bzero(cwd, 1024);
	if (argc > 2)
		return (err_minishell(ERR_TOO_MANY_ARGS, argv[0]));
	if (argc == 2)
		get_absolute_path(argv[1], envl, path);
	else if ((ptr = ft_getenv("HOME", envl)))
		ft_strcat(path, ft_getenv("HOME", envl));
	else
		return (err_minishell(ERR_HOME_NOT_SET, argv[0])); //errorsomething;
	if (access(path, F_OK))
		return (err_minishell(ERR_FILE_NOT_FOUND, argv[1]));
	getcwd(cwd, 1024);
	ft_setenv("OLDPWD", cwd, 1, envl);
	chdir(path); //error check?
	getcwd(cwd, 1024);
	ft_setenv("PWD", cwd, 1, envl);
	return (0);
}
