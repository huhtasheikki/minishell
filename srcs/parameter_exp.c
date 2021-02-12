/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:39:46 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 10:24:55 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_var_name(char *prefix, char *word)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 1;
	ft_bzero(prefix, 2048);
	if (word[j] == '{')
	{
		quote = '}';
		j++;
	}
	while (word[j] && word[j] != '"' && word[j] != quote && word[j] != '$' && \
			word[j] != ' ')
		prefix[i++] = word[j++];
	prefix[i] = '\0';
	if (word[j] == quote)
		j++;
	return (j);
}

int		variable_to_string(char *word, char *temp, int *temp_i, t_list *envl)
{
	char	prefix[2048];
	char	*ptr;
	int		i;

	i = get_var_name(prefix, word);
	if ((ptr = ft_getenv(prefix, envl)))
	{
		ft_strcat(temp, ptr);
		*temp_i += i;
	}
	return (i);
}

char	*variable_exp(char *word, t_list *envl)
{
	char	temp[2048];
	int		i;
	int		j;

	ft_bzero(temp, 2048);
	i = 0;
	j = 0;
	if (word[0] == '\'' || !ft_strchr(word, '$'))
		return (word);
	while (word[i] != '\0')
	{
		if (word[i] == '$')
			i += variable_to_string(word + i, temp, &j, envl);
		else if (word[i] == '\'' || word[i] == '"')
			i++;
		else
			temp[j++] = word[i++];
	}
	free(word);
	word = ft_strdup(temp);
	return (word);
}
