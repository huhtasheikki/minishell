/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:34:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/16 11:48:38 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*copy_envp(char **envp)
{
	t_list		*envl;
	t_list		*lastl;
	t_list		*newl;

	if (!(envl = ft_lstnew(NULL, 0)))
		return (NULL); // WHICH RETURN WHEN FAIL?
	lastl = envl;
	while(*envp)
	{
		if (!(lastl->next = ft_lstnew(*envp, ft_strlen(*envp) + 1)))
		{
			while (envl)
			{
				newl = envl->next;
				free(newl->content);
				free(newl);
				envl = envl->next;
			}
			return (NULL); //ERROR WITHOUT LEAKS? RETURN VALUE??
		}
		lastl = lastl->next;
		envp++;
	}
	return (envl);
}

char	**make_envp(t_list *envl)
{
	char		**envp;
	t_list		*lst_ptr;
	int			i;
	int			j;

	i = 0;
	lst_ptr = envl;
	while (lst_ptr->next)
	{
		lst_ptr = lst_ptr->next;
		i++;
	}
	if (!(envp = ft_memalloc(sizeof(char*) * (i + 1))))
		return (NULL); // ERRROR_FUN with malloc fail
	j = 0;
	while (envl->next)
	{
		envl = envl->next;
		envp[j++] = envl->content;
	}
	return (envp);
}

/*
**===========================================================================**
** FT_GETENV
**===========================================================================**
**   The getenv() function obtains the current value of the environment vari-
**   able, name.  The application should not modify the string pointed to by
**   the getenv() function.
**===========================================================================**
*/
char	*ft_getenv(const char *name, t_list *envl)
{
	char		*envs;
	size_t		len;

// UNCOMMENT THESE AT THE END WHEN EVERYTHING WORKS!
//	if (!name || !envl)
//		return (NULL);
	len = ft_strlen(name);
	while (envl->next)
	{
		envl = envl->next;
		envs = envl->content;
		if (!ft_strncmp(envs, name, len) && envs[len] == '=')
			return (envs + (len + 1));
	}
	return (NULL);
}

char	*get_env_var(char *var, t_list *envl)
{
	char		*temp;
	size_t		len;

	len = ft_strlen(var);
	while (envl->next)
	{
		envl = envl->next;
		temp = envl->content;
		if (!ft_strncmp(temp, var, len) && temp[len] == '=')
			return (temp + (len + 1));
	}
	return (NULL);
}

/*
// ft_setenv not tested yet
int		ft_setenv(const char *name, const char *value, int override, t_list *envl)
{
	size_t		len;
	char		*envs;

	if (!name || ft_strlen(name) == 0 || ft_strchr(name, '='))
		return (-1); // or own error function return(error_fun(EINVAL));
	len = ft_strlen(name);
	while (envl->next)
	{
		envl = envl->next;
		envs = envl->content;
		if (!ft_strncmp(envs, name, len) && (envs[len] == '=') && override)
		{
			if (!(envs = ft_strnew(len + ft_strlen(value) + 2))) // with or without 1, or 2 if ending null and extra = ?
				return (-1); // or error_fun(ENOMEM); which returns -1;
			free(envl->content);
			envs = ft_strncat(envs, name, len);
			envs[len] = '=';
			envs = ft_strncat(envs, value, ft_strlen(value));
			envl->content = envs;
			envl->content_size = len + ft_strlen(value) + 1; // with or without 1?
			return (0);
		}
	}
//	ft_printf("setenv %s, name %s\n", envl->content, name);
	envs = ft_strnew(len + ft_strlen(value) + 2);
	envs = ft_strncat(envs, name, len);
	envs[len] = '=';
	envs = ft_strncat(envs, value, ft_strlen(value));
//	envs[ft_strlen(envs)] = '\0';
//	ft_lstappend(&envl, ft_lstnew(envs, ft_strlen(envs) + 1));
	envl->next = ft_lstnew(envs, ft_strlen(envs) + 1);
//	envl->next = ft_lstnew("MOI", 3);
//	ft_printf("setenv envs=%s, value %s\n", envs, value);
	envl = envl->next;
//	ft_printf("env->next %s\n", envl->content);
	return (0);
}
*/

/*
**===========================================================================**
** FT_UNSETENV
**===========================================================================**
**   The unsetenv() function deletes all instances of the variable name pointed
**   to by name from the list.  Note that only the variable name (e.g., "NAME")
**   should be given; "NAME=value" will not work.
**===========================================================================**
*/

int		ft_unsetenv(const char *name, t_list *envl) // NOT TESTED YET
{
	t_list		*envl_link;
	size_t		len;
	char		*envs;

	if (!name || ft_strlen(name) == 0 || ft_strchr(name, '='))
		return (-1); // or own error function return(error_fun(EINVAL));
	len = ft_strlen(name);
	while (envl->next)
	{
		envl_link = envl;
		envl = envl->next;
		envs = envl->content;
		if (!ft_strncmp(envs, name, len) && (envs[len] == '='))
		{
			envl_link->next = envl->next;
			free(envl->content);
			free(envl);
			envl = envl_link;
		}
	}
	return (0);
}
