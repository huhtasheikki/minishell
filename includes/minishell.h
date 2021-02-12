/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:59:32 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 19:42:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "libft_shorthand.h"
# include "minishell_defs.h"

int			err_minishell(int errorno, char *name);

t_list		*copy_envp(char **envp);
char		**make_envp(t_list *envl);
char		*ft_getenv(const char *name, t_list *envl);
int			ft_setenv(char *name, char *val, int over, t_list *envl);
int			ft_unsetenv(const char *name, t_list *envl);

int			scanner2(char *input, int size, t_lexer *lexer);

int			expansions(t_token *token, t_list *envl);
char		*variable_exp(char *word, t_list *envl);

t_list		*create_commandlist(t_token *tok);

int			call_simple_fun(char **argv, t_list *envl);

void		clean_token(t_token *token);
int			ft_builtin(char **argv, t_list *envl);

int			search_command(char *file, char *epath, char *buf, size_t size);

int			is_absolute_path(char *path);

int			parse_commands(t_lexer *lex);

/*
** SCANNER
*/
int			scanner2(char *input, int size, t_lexer *lexer);

t_token		*new_token(size_t size);
int			check_state(int state, char c, char *quote);
t_token		*get_last_token(t_token *token);
t_token		*get_last_subtoken(t_token *token);
t_token		*init_scanner(t_lexer *lexer, char *quote, int size);

/*
** BUILTIN FUNCTIONS
*/

int			ft_echo(int fd, char **argv);
int			builtin_cd(int argc, char **argv, t_list *envl);
int			builtin_env(int argc, char **argv, t_list *envl);
int			builtin_setenv(int argc, char **argv, t_list *envl);

void		sig_int(int signo);
void		print_prompt(int mode);

#endif
