/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 20:16:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/11 18:37:27 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Tilde Expansion - FROM BASH DOCUMENTATION
**
** If a word begins with an unquoted tilde character (‘~’), all of the
** characters up to the first unquoted slash (or all characters, if there is
** no unquoted slash) are considered a tilde-prefix. If none of the characters
** in the tilde-prefix are quoted, the characters in the tilde-prefix
** following the tilde are treated as a possible login name. If this login
** name is the null string, the tilde is replaced with the value of the HOME
** shell variable. If HOME is unset, the home directory of the user executing
** the shell is substituted instead. Otherwise, the tilde-prefix is replaced
** with the home directory associated with the specified login name.
**
** If the tilde-prefix is ‘~+’, the value of the shell variable PWD replaces
** the tilde-prefix. If the tilde-prefix is ‘~-’, the value of the shell
** variable OLDPWD, if it is set, is substituted.
**
** If the characters following the tilde in the tilde-prefix consist of a
** number N, optionally prefixed by a ‘+’ or a ‘-’, the tilde-prefix is
** replaced with the corresponding element from the directory stack, as it
** would be displayed by the dirs builtin invoked with the characters
** following tilde in the tilde-prefix as an argument (see The Directory
** Stack). If the tilde-prefix, sans the tilde, consists of a number
** without a leading ‘+’ or ‘-’, ‘+’ is assumed.
**
** If the login name is invalid, or the tilde expansion fails, the word is
** left unchanged.
**
** Each variable assignment is checked for unquoted tilde-prefixes
** immediately following a ‘:’ or the first ‘=’. In these cases, tilde
** expansion is also performed. Consequently, one may use filenames with
** tildes in assignments to PATH, MAILPATH, and CDPATH, and the shell
** assigns the expanded value.
*/

int		tilde_plusminus(char *prefix, char *temp, t_list *envl)
{
	char	*ptr;

	if (prefix[1] != '+' && prefix[1] != '-')
		return (0);
	if (prefix[1] == '+' && (prefix[2] == '/' || prefix[2] == '\0'))
	{
		if ((ptr = get_env_var("PWD", envl)))
			ft_strncat(temp, ptr, 2049);
		else
			ft_strcat(temp, prefix);
	}
	if (prefix[1] == '-' && (prefix[2] == '/' || prefix[2] == '\0'))
	{
		if ((ptr = get_env_var("OLDPWD", envl)))
			ft_strncat(temp, ptr, 2049);
		else
			ft_strcat(temp, prefix);
	}
	return (1);
}

int		init_tilde(char *prefix, char *temp, char *word)
{
	int		i;

	i = 0;
	ft_bzero(prefix, 2049);
	ft_bzero(temp, 2049);
	while (word[i] && word[i] != '/' && i < 2048)
	{
		prefix[i] = word[i];
		i++;
	}
	prefix[i] = '\0';
	return (i);
}

char	*tilde_exp(char *word, t_list *envl)
{
	char	prefix[2049];
	char	temp[2049];
	char	*ptr;
	int		i;

	i = init_tilde(prefix, temp, word);
	if (i == 1)
	{
		if (!(ptr = get_env_var("HOME", envl)))
		{
			ft_strcat(temp, "/Users/");
			ptr = get_env_var("USER", envl);
		}
		if (ptr)
			ft_strncat(temp, ptr, 2040);
	}
	else if (!tilde_plusminus(prefix, temp, envl))
	{
		ft_strcat(temp, "/Users/");
		ft_strncat(temp, prefix + 1, 2048 - ft_strlen(temp));
	}
	if (word[i])
		ft_strncat(temp, word + i, 2048 - ft_strlen(temp));
	free(word);
	return (ft_strdup(temp));
}

int		expansions(t_token *token, t_list *envl)
{
	t_token		*sub;
	char		*word;

	while (token->next)
	{
		token = token->next;
		sub = token->subtoken;
		while (sub)
		{
			word = sub->word;
			sub->word = variable_exp(word, envl);
			sub = sub->subtoken;
		}
		if (token->word[0] == '~')
			token->word = tilde_exp(token->word, envl);
		token->word = variable_exp(token->word, envl);
		clean_token(token);
	}
	return (1);
}
