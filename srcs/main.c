/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:14:00 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/09 19:49:59 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*free_tokens(t_token *tokens)
{
	t_token		*sub;
	t_token		*temp;
	t_token		*token;

	if (tokens == NULL)
		return (NULL);
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
	return (NULL);
}

void		init_lexer(int argc, char **argv, t_lexer *lexer, char **envp)
{
	if (!(lexer->tokens = new_token(0)))
		exit((err_minishell(ERR_MALLOC, NULL)));
	if (!(lexer->envl = copy_envp(envp)))
		exit((err_minishell(ERR_MALLOC, NULL)));
	if (ft_setenv("SHELL", argv[0], 1, lexer->envl) < 0)
		exit(err_minishell(ERR_MALLOC, NULL));
	lexer->state = STATE_IN_GENERAL;
	lexer->mode = PROMPT_NORMAL;
	lexer->argc = argc;
	lexer->argv = argv;
}

void		print_prompt(int mode)
{
	if (mode == PROMPT_NORMAL)
		ft_printf("$> ");
	if (mode == PROMPT_QUOTE)
		ft_printf("> ");
}

void		delete_lst(void *data, size_t i)
{
	char	**argv;

	argv = data;
	while (argv && *argv)
	{
		ft_bzero(*argv, ft_strlen(*argv));
		free(*argv);
		argv++;
	}
	ft_bzero(data, i);
	free(data);
}

int			main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_list		*commands;
	t_lexer		lex;

	init_lexer(argc, argv, &lex, envp);
	buf = NULL;
	while (1)
	{
		if (lex.mode != PROMPT_QUOTE)
			lex.tokens->next = free_tokens(lex.tokens->next);
		print_prompt(lex.mode);
		free(buf);
		get_next_line(STDIN_FILENO, &buf);
		if (scanner2(buf, ft_strlen(buf), &lex) == PROMPT_QUOTE)
			continue;
		lex.mode = PROMPT_NORMAL;
		if (!ft_strcmp(buf, "") || lex.tokens->next->type != TOKEN_WORD)
			continue;
		expansions(lex.tokens, lex.envl);
		commands = create_commandlist(lex.tokens);
		parse_commands(commands, &lex);
		ft_lstdel(&commands, &delete_lst);
	}
	exit(0);
}
