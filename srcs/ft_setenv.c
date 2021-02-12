/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:34:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 15:13:32 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**===========================================================================**
** FT_SETENV
**===========================================================================**
**   The setenv() function inserts or resets the environment variable name in
**   the current environment list.  If the variable name does not exist in the
**   list, it is inserted with the given value.  If the variable does exist,
**   the argument overwrite is tested; if overwrite is zero, the variable is
**   not reset, otherwise it is reset to the given value.
**   Return values:
**   - Success -> 0
**   - Fail -> -1
**===========================================================================**
*/

static int	setenvs(const char *name, const char *val, t_list *envl, int len)
{
	char		*envs;

	if (!(envs = ft_strnew(len + ft_strlen(val) + 2)))
		return (err_minishell(ERR_MALLOC, NULL));
	free(envl->content);
	envs = ft_strncat(envs, name, len);
	envs[len] = '=';
	envs = ft_strncat(envs, val, ft_strlen(val));
	envl->content = envs;
	envl->content_size = ft_strlen(envs) + 1;
	return (0);
}

int			ft_setenv(char *name, char *val, int over, t_list *envl)
{
	char		*envs;
	size_t		len;

	len = ft_strlen(name);
	if (!name || ft_strchr(name, '='))
		return (err_minishell(ERR_INVALID_INPUT, "setenv"));
	while (envl->next)
	{
		envl = envl->next;
		envs = envl->content;
		if (!ft_strncmp(envs, name, len) && (envs[len] == '='))
		{
			if (over)
				return (setenvs(name, val, envl, len));
			else
				return (0);
		}
	}
	if (!(envl->next = ft_lstnew(NULL, 0)))
		return (err_minishell(ERR_MALLOC, NULL));
	return (setenvs(name, val, envl->next, len));
}

int			builtin_setenv(int argc, char **argv, t_list *envl)
{
	if (argc == 1 || argc > 3 || ft_strlen(argv[1]) < 1)
		return (err_minishell(ERR_INVALID_INPUT, argv[0]));
	else if (argc == 2)
		return (ft_setenv(argv[1], "", 1, envl));
	return (ft_setenv(argv[1], argv[2], 1, envl));
}
