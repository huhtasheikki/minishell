/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:20:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 10:58:56 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_token_len(t_token *token)
{
	int			len;

	len = ft_strlen(token->word);
	while (token->subtoken)
	{
		token = token->subtoken;
		len += ft_strlen(token->word);
	}
	return (len);
}

int		get_argv_size(t_token *token)
{
	size_t		size;

	size = 0;
	while (token)
	{
		token = token->next;
		++size;
	}
	return (size);
}

int		search_command(char *file, char *epath, char *buf, size_t size)
{
	char		**path_split;
	int			i;

	i = 0;
	ft_bzero(buf, size);
	if (!(path_split = ft_strsplit(epath, ':')))
		return (err_minishell(ERR_MALLOC, NULL));
	while (path_split[i])
	{
		ft_strcat(buf, path_split[i]);
		ft_strcat(buf, "/");
		ft_strcat(buf, file);
		if (!access(buf, F_OK))
			break ;
		ft_bzero(buf, size);
		i++;
	}
	ft_strarrdel(&path_split);
	free(path_split);
	if (buf[0])
		return (1);
	return (0);
}

int		call_simple_fun(char **argv, t_list *envl)
{
	char		**envp;
	char		fpath[1024];
	char		*path_ptr;

	if (is_absolute_path(argv[0]))
		ft_strcpy(fpath, argv[0]);
	else if ((path_ptr = ft_getenv("PATH", envl)))
	{
		search_command(argv[0], path_ptr, fpath, 1024);
		if (access(fpath, F_OK) == -1)
			return (err_minishell(ERR_NO_COMMAND, argv[0]));
	}
	if (access(fpath, F_OK) == -1)
		return (err_minishell(ERR_FILE_NOT_FOUND, argv[0]));
	if (access(fpath, X_OK) == -1)
		return (err_minishell(ERR_NO_PERMISSION, argv[0]));
	if ((g_pid = fork()) == 0)
	{
		if (!(envp = make_envp(envl)))
			exit(err_minishell(ERR_MALLOC, NULL));
		exit(execve(fpath, argv, envp));
	}
	else
		wait(NULL);
	return ((g_pid = 0));
}
