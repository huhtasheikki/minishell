/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:59:32 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/11/26 16:30:56 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h> //kill?
# include <signal.h> //kill
# include "libft.h"
# include "libft_shorthand.h"

# define EXECVE_ERROR 2

void	test(void);

int		run_execve(char *program, char **argv, char **envp);

#endif
