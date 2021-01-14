/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:14:00 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/14 11:38:13 by hhuhtane         ###   ########.fr       */
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

void	init_lexer(t_lexer *lexer, char **envp)
{
	if (!(lexer->tokens = new_token(0)))
		exit((err_minishell(ERR_MALLOC, NULL))); // error;
	if (!(lexer->envl = copy_envp(envp)))
		exit((err_minishell(ERR_MALLOC, NULL)));
	lexer->state = STATE_IN_GENERAL;
	lexer->mode = PROMPT_NORMAL;
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
//	char		buf[BUFFSIZE];
	char		*buf;
	t_lexer		lexer;

	(void)argc;
	(void)argv;
	init_lexer(&lexer, envp);
	while (1)
	{
		print_prompt(lexer.mode);
/*
		while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
			if (write(STDOUT_FILENO, buf, n) != n)
				err_sys(ERR_WRITE, NULL);
		if (n < 0)
			err_minishell(ERR_READ);
*/
		get_next_line(STDIN_FILENO, &buf);
		n = ft_strlen(buf);
		if (scanner2(buf, n, &lexer) == 2)
		{
			lexer.mode = PROMPT_QUOTE;
			continue;
		}
		lexer.mode = PROMPT_NORMAL;

//make these to fun
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

		expansions(lexer.tokens, lexer.envl);
		clean_token(lexer.tokens);
		lexer.argv = create_argv(lexer.tokens); // errorfun!
		lexer.envp = make_envp(lexer.envl); // is it needed here?
		if (ft_builtin(lexer.argv, lexer.envl))
			call_simple_fun(lexer.argv, lexer.envp, lexer.envl);
		ft_strarrdel(&lexer.argv);
		free(lexer.argv);
		free(lexer.envp);
		free_tokens(lexer.tokens->next);
		lexer.tokens->next = NULL;
	}
	exit(0);
}
