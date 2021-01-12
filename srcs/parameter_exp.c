/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:39:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/02 12:31:56 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_var_name(char *prefix, char *word)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	if (word[j] == '{')
	{
		quote = '}';
		j++;
	}
	while (word[j] && word[j] != '"' && word[j] != quote && word[j] != '$' && \
			word[j] != ' ')
	{
		prefix[i++] = word[j];
		j++;
	}
	prefix[i] = '\0';
	if (word[j] == quote)
		j++;
	return (j);
}

char	*variable_exp(char *word, t_list *envl)
{
	char	prefix[2049];
	char	temp[2049];
	char	*ptr;
	int		i;
	int		j;

	ft_bzero(prefix, 2049);
	ft_bzero(temp, 2049);
	i = 0;
	j = 0;
	if (word[0] == '\'' || !ft_strchr(word, '$'))
		return (word);
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			i++;
			i += get_var_name(prefix, word + i);
			ptr = get_env_var(prefix, envl);
			if (ptr)
			{
				ft_strcat(temp, ptr);
				j += ft_strlen(ptr);
			}
		}
		else if (word[i] == '\'' || word[i] == '"')
			i++;
		else
			temp[j++] = word[i++];
	}
	free(word);
	word = ft_strdup(temp);

//	ptr = ft_memccpy(temp, word, '$', ft_strlen(word));
//	ft_printf("temp %s\n", temp);
//	ft_printf("ptr %s\n", ptr);
//	word = ft_strchr(word, '$') + 1;
//	while (*word && j < 2048)
//	{
//		if (*word == '\'' || *word == '"')
//			break;
//		prefix[j++] = *word;
//		ptr++;
//		word++;
//	}
//	prefix[j] = '\0';
//	ft_printf("VAR name=%s\n", prefix);
//	ptr = get_env_var(prefix, envl);
//	ft_strcat(temp, ptr);
//	free(ptr2);
//	word = ft_strdup(temp);

	return (word);
//	return (variable_exp(word, envl));
}
