/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:38:44 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/11/26 15:53:06 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_execve(char *program, char **argv, char **envp)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid != 0)
		return (child_pid);
	else
	{
		execve(program, argv, envp);
		error_minishell(program, EXECVE_ERROR);
	}
}
