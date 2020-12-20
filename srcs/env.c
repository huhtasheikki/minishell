/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:34:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/12/19 17:16:45 by hhuhtane         ###   ########.fr       */
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
		if (!(lastl->next = ft_lstnew(*envp, ft_strlen(*envp))))
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
	t_list		lst_ptr;
	int			i;
	int			j;

	i = 0;
	lst_ptr = envl;
	while (lst_ptr)
	{
		lst_ptr = lst_ptr->next;
		i++;
	}
	if (!(envp = ft_memalloc(sizeof(char*) * (i + 1))))
		return (NULL); // ERRROR_FUN with malloc fail
	lst_ptr = envl;
	j = 0;
	while (lst_ptr)
	{
		evnp[j] = lst_ptr;
		lst->ptr = lst_ptr->next;
	}
	return (envp);
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
			if (!(envs = ft_strnew(len + ft_strlen(value) + 1))) // with or without 1?
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
	return (0);
}

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
