/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:28:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/12 16:24:43 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	print_lexes(t_token *tokens)
{
	t_token		*sub;

	while (tokens)
	{
		if (tokens->word)
			ft_printf("main %s type=%d \n", tokens->word, tokens->type);
		sub = tokens->subtoken;
		while (sub)
		{
			ft_printf("%s type=%d \n", sub->word, sub->type);
			sub = sub->subtoken;
		}
		tokens = tokens->next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token		*sub;
	t_token		*temp;
	t_token		*token;

	token = tokens;
	while (token)
	{
		if (token->word)
			free(token->word);
		sub = token->subtoken;
		while (sub)
		{
			free(sub->word);
			temp = sub;
			sub = sub->subtoken;
			free(temp);
		}
		token = tokens->next;
		free(tokens);
		tokens = token;
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

void	print_prompt(int mode)
{
	if (mode == PROMPT_NORMAL)
		ft_printf("$> ");
	if (mode == PROMPT_QUOTE)
		ft_printf("> ");
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

int		file_exist(char *path, char *file)
{
	(void)path; // KESKEN
	(void)file;
	return (0);
}

int		iscommand(char *command, t_lexer *lexer)
{
	char		**path;

	path = lexer->path;
	if (!command)
		return (0);
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
//	t_shell		shell;
	t_lexer		lexes;
	char		*buf;
//	char		path[256];
	t_list		*env_lst;
	int			fd;
//	char		*own_envp[1025];
	int			i;
	char		**argv2;
	char		**envp2;

	i = 0;
	lexes.tokens = new_token(0);
	lexes.state = STATE_IN_GENERAL;
	lexes.envl = copy_envp(envp); // ERROR SHOULD RETURN OR EXITi
//	env_lst = lexes.envl;
//	lst_to_array(env_lst, own_envp);

//	shell.path_arr = ft_strsplit(get_env_var("PATH", lexes.envl), ':');
//	lexes.path = shell.path_arr;
/*
	while (own_envp[i])
	{
		ft_putendl(own_envp[i]);
		i++;
	}
*/

/*
	env_lst = lexes.envl;
	while (env_lst->next)
	{
		env_lst = env_lst->next;
		ft_printf("%s\n", env_lst->content);
	}
*/

	env_lst = lexes.envl;

/*
	ft_setenv("SHELL", "hevonen", 1, env_lst);
	ft_setenv("SHELL", "koira", 1, env_lst);
	ft_setenv("AAUUUAUAUAUA", "koira", 1, lexes.envl);
*/

//	getcwd(path, 256);
//	ft_printf("FT path = %s\n", path);
//	chdir("..");
//	getcwd(path, 256);
//	ft_printf("FT after change path = %s\n", path);
	fd = open("/dev/stdin", O_RDWR);

//	ft_printf("$HOME=|%s|\n $USER=|%s|\n", get_env_var("HOME", env_lst), get_env_var("USER", env_lst));

//	ft_printf("$>");

	lexes.mode = PROMPT_NORMAL;
	while (1)
	{
		print_prompt(lexes.mode);
		get_next_line(fd, &buf); // how about line ending "\" and continueing next line
		if (ft_strcmp(buf, "exit") == 0)
		{
			free(buf);
			break;
		}
		if (ft_strcmp(buf, "") == 0)
		{
//			ft_printf("TYHJA\n");
			free(buf);
			continue;
		}
//		ft_printf("READ STDIN: |%s|\n", buf);
		if ((scanner2(buf, ft_strlen(buf), &lexes) == 2))
		{
			lexes.mode = PROMPT_QUOTE;
			continue;
		}
		lexes.mode = PROMPT_NORMAL;
//		lexer(buf, ft_strlen(buf), &lexes);
		expansions(lexes.tokens, lexes.envl);
//		print_lexes(lexes.tokens);

		clean_token(lexes.tokens);

//		ft_lstappend(&lexes.envl, ft_lstnew("ONNI", 4));
		argv2 = create_argv(lexes.tokens);
		envp2 = make_envp(lexes.envl);
//		ft_printf("argv2 address: %p\n", argv2);
//		ft_printf("envp2 address: %p\n", envp2);


/*
		env_lst = lexes.envl;
		while (env_lst->next)
		{
			env_lst = env_lst->next;
			ft_printf("envl %s\n", env_lst->content);
		}
		env_lst = lexes.envl;
*/

/*
		i = 0;
		while (envp2[i])
		{
			ft_printf("envp2[%d]=%s\n", i, envp2[i]);
			i++;
		}
*/

/*
		i = 0;
		while (argv2[i])
		{
			ft_printf("argv2[%d]=%s\n", i, argv2[i]);
			i++;
		}
*/
		if (ft_builtin(argv2, lexes.envl))
		{
//		if (!ft_echo(1, argv2))
			ft_printf("NOT BUILTIN!\n");
			call_simple_fun(argv2, envp2, lexes.envl);
		}
		free(buf);
		ft_strarrdel(&argv2);
		free(argv2);
		free(envp2);
		free_tokens(lexes.tokens);
		lexes.tokens = new_token(0);
	}

	(void)argc; // Same as argv
	(void)argv; // MAKE FUNCTION TO USE THESE
	return (0);
}
