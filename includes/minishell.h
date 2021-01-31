/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:59:32 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/31 15:14:01 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h> // fork, getcwd, etc.
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/wait.h> // wait, wait3, wait4, waitpid
# include <sys/types.h> //kill?
# include <signal.h> //kill, signal
# include <stdlib.h> // exit
# include "ft_printf.h"
# include "libft_shorthand.h"

/* IF ENUM DOESN'T WORK USE THESE
# define CHAR_GENERAL 1
# define CHAR_NULL 2
# define CHAR_LESS 4
# define CHAR_GREATER 8
# define CHAR_NEWLINE 16
# define CHAR_TAB 32
# define CHAR_BACKSLASH 64
# define CHAR_SEMICOLON 128
# define CHAR_SPACE 256
# define CHAR_AMPERSAND 512
# define CHAR_PIPE 1024
# define CHAR_DQUOTE 2048
# define CHAR_QUOTE 4096
*/

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

# define MAXPATHLEN 256
# define FNAME_MAX 256

# define METACHARS "|&;()<>" // operator: control or redirection need one this;
# define METACHARS2 "|&;()<> \t$" // operator: control or redirection need one this;
# define CONTROL_OPERATOR "|| & && ; ;; ( ) | \n" // split with space
# define TOKEN_SPLIT " <>^|;" // NOT SURE ANYMORE

# define PROMPT_NORMAL 1
# define PROMPT_QUOTE 2

# define ENV_I_FLAG 1
# define ENV_V_FLAG 2
# define ENV_P_FLAG 4
# define ENV_S_FLAG 8
# define ENV_U_FLAG 16

/*
** DEFINE LIMITS
*/
//# define NAME_MAX
//# define PATH_MAX



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

/* SOME OF THESE MIGHT BE USELESS  */
// // // //
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

typedef struct			s_shell
{
	char				**path_arr;
	char				path[MAXPATHLEN];
	pid_t				process_id; // group, parent, child, what?
}						t_shell;



typedef struct s_token	t_token;

struct					s_token
{
	char				*word;
	t_token				*subtoken;
	int					type;
	t_token				*next;
};

typedef struct s_lexer	t_lexer;

struct 					s_lexer
{
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

int					err_minishell(int errorno, char *name);

void				test(void);

int					run_execve(char *program, char **argv, char **envp);

t_list				*copy_envp(char **envp);
char				**make_envp(t_list *envl);
char				*ft_getenv(const char *name, t_list *envl);
char				*get_env_var(char *var, t_list *envl);
int					ft_setenv(const char *name, const char *val, int over, t_list *envl);
int					ft_unsetenv(const char *name, t_list *envl);

//int					lexer(char *input, int size, t_lexer *lexes);

int					scanner2(char *input, int size, t_lexer *lexer);
t_token				*new_token(size_t size);

int					expansions(t_token *token, t_list *envl);
char				*variable_exp(char *word, t_list *envl);

char				**create_argv(t_token *token);

int					call_simple_fun(char **argv, char **envp, t_list *envl);

void				clean_token(t_token *token);
int					ft_builtin(char **argv, t_list *envl);

int					search_command(char *file, char *epath, char *buf, size_t size);

int					is_absolute_path(char *path);

/*
** BUILTIN FUNCTIONS
*/

int					ft_echo(int fd, char **argv);
int					builtin_cd(int argc, char **argv, t_list *envl);
int					builtin_env(int argc, char **argv, t_list *envl);
int					builtin_setenv(int argc, char **argv, t_list *envl);

#endif
