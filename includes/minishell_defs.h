/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_defs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:59:32 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 19:47:14 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFS_H
# define MINISHELL_DEFS_H

# define EXECVE_ERROR 2
# define ERR_INVALID_INPUT 4
# define ERR_MALLOC 8
# define ERR_HOME_NOT_SET 16
# define ERR_WRITE 32
# define ERR_FILE_NOT_FOUND 64
# define ERR_NO_PERMISSION 128
# define ERR_TOO_FEW_ARGS 256
# define ERR_TOO_MANY_ARGS 512
# define ERR_INPUT_INIT 1024
# define ERR_FORK_ERROR 2048
# define ERR_STAT 4096
# define ERR_NOT_A_DIR 8192
# define ERR_TOO_MANY_SYMLINKS 16384
# define ERR_PATH_NOT_SET 32768
# define ERR_SIG 65536
# define ERR_NO_COMMAND 131072

# define MAXPATHLEN 256
# define FNAME_MAX 256

# define METACHARS "|&;()<>"
# define METACHARS2 "|&;()<> \t$"

# define PROMPT_NORMAL 1
# define PROMPT_QUOTE 2

# define ENV_I_FLAG 1
# define ENV_V_FLAG 2
# define ENV_P_FLAG 4
# define ENV_S_FLAG 8
# define ENV_U_FLAG 16

pid_t			g_pid;

enum					e_token_type
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_SPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESS = '<',
	CHAR_TILDE = '~',
	CHAR_DOLLAR = '$',
	CHAR_NULL = '\0'
};

enum					e_state
{
	STATE_IN_QUOTED,
	STATE_IN_OPERATOR,
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
	STATE_IN_ESCAPESEQUENCE,
	STATE_IN_GENERAL,
	STATE_IN_VARIABLE,
	STATE_IN_OPTIONS,
	STATE_IN_SETENV,
	STATE_IN_UNSETENV,
	STATE_IN_ALTPATH
};

enum					e_token
{
	TOKEN_EMPTY,
	TOKEN_OPERATOR,
	TOKEN_WORD,
	TOKEN_EOI
};

typedef struct stat		t_stat;

typedef struct s_token	t_token;

struct					s_token
{
	char				*word;
	t_token				*subtoken;
	int					type;
	t_token				*next;
};

typedef struct s_lexer	t_lexer;

struct					s_lexer
{
	t_list				*commands;
	int					argc;
	char				**argv;
	char				**envp;
	int					mode;
	t_list				*envl;
	char				quote;
	int					state;
	int					token_count;
	t_token				*tokens;
	char				**path;
};

#endif
