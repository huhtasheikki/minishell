/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:28:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/12/20 11:28:36 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	print_lexes(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("%s type=%d\n", tokens->word, tokens->type);
		tokens = tokens->next;
	}
}

void	test_split(char *input)
{
	if (!input)
	{
		ft_printf("EMPTY\n");
		exit(1);
	}
	while (*input)
	{
		if (ft_isspace(*input))
			ft_printf("MOI");
		input++;
	}
}

void	print_prompt(void)
{
	ft_printf("$>");
}

void	lst_to_array(t_list *envl, char *array[])
{
	int			i;

	i = 0;
	while (envl->next)
	{
		envl = envl->next;
		array[i] = envl->content;
		i++;
	}
	array[i] = NULL;
}

int		main(int argc, char **argv, char **envp)
{
	t_lexer		lexes;
	char		*buf;
	char		path[256];
	t_list		*env_lst;
	int			fd;
	char		*own_envp[1025];
	int			i;

	i = 0;
	lexes.tokens = new_token(0);
	lexes.state = STATE_IN_GENERAL;
	lexes.envl = copy_envp(envp); // ERROR SHOULD RETURN OR EXITi
	env_lst = lexes.envl;
	lst_to_array(env_lst, own_envp);
	while (own_envp[i])
	{
		ft_putendl(own_envp[i]);
		i++;
	}
	while (env_lst->next)
	{
		env_lst = env_lst->next;
		ft_printf("%s\n", env_lst->content);
	}
	env_lst = lexes.envl;

	getcwd(path, 256);
	ft_printf("FT path = %s\n", path);
	chdir("..");
	getcwd(path, 256);
	ft_printf("FT after change path = %s\n", path);
	fd = open("/dev/stdin", O_RDWR);

	ft_printf("$HOME=|%s|\n $USER=|%s|\n", get_env_var("HOME", env_lst), get_env_var("USER", env_lst));

//	ft_printf("$>");

	while (1)
	{
		print_prompt();
		get_next_line(fd, &buf); // how about line ending "\" and continueing next line
		if (ft_strcmp(buf, "exit") == 0)
		{
			free(buf);
			break;
		}
		if (ft_strcmp(buf, "") == 0)
		{
			ft_printf("TYHJA\n");
			free(buf);
			continue;
		}
		ft_printf("READ STDIN: |%s|\n", buf);
		scanner2(buf, ft_strlen(buf), &lexes);
//		lexer(buf, ft_strlen(buf), &lexes);
		expansions(lexes.tokens, lexes.envl);
		print_lexes(lexes.tokens);
		free(buf);
	}

	(void)argc; // Same as argv
	(void)argv; // MAKE FUNCTION TO USE THESE
	return (0);
}
