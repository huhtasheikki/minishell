/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:14:00 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/31 15:13:38 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** THIS IS NOT YET IN THE PROJECT. UNIX BOOK MATERIAL TESTS.
*/

#include "minishell.h"

//#define BUFFSIZE 4096

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

void	init_lexer(int argc, char **argv, t_lexer *lexer, char **envp)
{
	if (!(lexer->tokens = new_token(0)))
		exit((err_minishell(ERR_MALLOC, NULL))); // error;
	if (!(lexer->envl = copy_envp(envp)))
		exit((err_minishell(ERR_MALLOC, NULL)));
	lexer->state = STATE_IN_GENERAL;
	lexer->mode = PROMPT_NORMAL;
	lexer->argc = argc;
	lexer->argv = argv;
}

void	print_prompt(int mode)
{
	if (mode == PROMPT_NORMAL)
		ft_printf("$> ");
	if (mode == PROMPT_QUOTE)
		ft_printf("> ");
}

int		main(int argc, char **argv, char **envp)
{
	int			n; // number of bytes read
	char		*buf;
	t_lexer		lexer;

	init_lexer(argc, argv, &lexer, envp);
	while (1)
	{
		print_prompt(lexer.mode);
		get_next_line(STDIN_FILENO, &buf);
		n = ft_strlen(buf);
		if (scanner2(buf, n, &lexer) == 2)
		{
			lexer.mode = PROMPT_QUOTE;
			continue;
		}
		lexer.mode = PROMPT_NORMAL;

		if (ft_strcmp(buf, "") == 0)
		{
//			ft_printf("TYHJA\n");
			free(buf);
			continue;
		}

		expansions(lexer.tokens, lexer.envl);
		clean_token(lexer.tokens);
		lexer.argv = create_argv(lexer.tokens); // errorfun!
		lexer.envp = make_envp(lexer.envl); // is it needed here?
		if (ft_builtin(lexer.argv, lexer.envl) > 0)
			call_simple_fun(lexer.argv, lexer.envp, lexer.envl);
		ft_strarrdel(&lexer.argv);
		free(buf);
		free(lexer.argv);
		free(lexer.envp);
		free_tokens(lexer.tokens->next);
		lexer.tokens->next = NULL;
	}
	exit(0);
}
