/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:20:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/13 14:47:56 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_token_length(t_token *token)
{
	int			i;

	i = ft_strlen(token->word);
	while (token->subtoken)
	{
		token = token->subtoken;
		i += ft_strlen(token->word);
	}
	return (i);
}

char	**create_argv(t_token *token)
{
	t_token		*ptr;
	char		**argv;
	int			i;

	ptr = token;
	i = 0;
	while (ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	argv = ft_memalloc(sizeof(char*) * (i + 1)); //err?
	i = 0;

	while (token->next)
	{
		token = token->next;
//		ft_printf("token->word=%s\n", token->word);
		argv[i] = ft_memalloc(sizeof(char) * get_token_length(token) + 1); //err?
		ptr = token;
		ft_strcat(argv[i], ptr->word);
		while (ptr->subtoken)
		{
			ptr = ptr->subtoken;
			ft_strcat(argv[i], ptr->word);
		}
//		ft_printf("argv[%d]=%s\n", i, argv[i]);
		i++;
	}
	argv[i] = NULL;
	return (argv);

/*
	while (token->next)
	{
		token = token->next;
		ptr = token;
		i += get_token_length(t;
	}
*/
}

int			search_command(char *file, char *epath, char *buf, size_t size)
{
	char		**path_split;
	int			i;

	i = 0;
	ft_bzero(buf, size);
	if (!(path_split = ft_strsplit(epath, ':')))
		return (err_minishell(ERR_MALLOC));
	while (path_split[i])
	{
		ft_strcat(buf, path_split[i]);
		ft_strcat(buf, "/");
		ft_strcat(buf, file);
		if (!access(buf, F_OK))
			break;
		ft_bzero(buf, size);
		i++;
	}
	ft_strarrdel(&path_split);
	free(path_split);
	if (buf[0])
		return (1);
	return (0);
}

int			call_simple_fun(char **argv, char **envp, t_list *envl)
{
//	char		**paths;
	char		fpath[1024];
	char		*path_ptr;
	pid_t		parent;
	int			i;

	i = 0;
	ft_bzero(fpath, 1024);
// CHECK IF $PATH EXISTS
	if (!(path_ptr = ft_getenv("PATH", envl)))
		return (err_minishell(ERR_INVALID_INPUT)); // make err_minishell take argv[0];
	if (argv[0][0] == '/')
		ft_strcat(fpath, argv[0]);
	else
		search_command(argv[0], ft_getenv("PATH", envl), fpath, 1024);

/*
	paths = ft_strsplit(ft_getenv("PATH", envl), ':');
	while (paths[i])
	{
		ft_bzero(fpath, 1024);
		ft_strcat(fpath, paths[i]);
		ft_strcat(fpath, "/");
		ft_strcat(fpath, argv[0]);
		ft_printf("    %s\n", fpath);
		if (!access(fpath, F_OK))
		{
			ft_printf("FILE FOUND: %s\n", fpath);
			break;
		}
		i++;
	}
	ft_strarrdel(&paths);
	free(paths);
*/

//	ft_strcat(path, "/bin/");
//	ft_strcat(path, argv[0]);
//	ft_printf("path: %s\n", path);
	parent = fork();
	if (parent == 0)
	{
//		ft_printf("CHILD\n");
		execve(fpath, argv, envp);
		exit(1);
	}
	else
	{
//		ft_printf("PARENT\n");
		wait(NULL);
	}
	return (0);
}
