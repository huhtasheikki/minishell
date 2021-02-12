/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 09:27:50 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 15:40:48 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		err_minishell(int errorno, char *name)
{
	if (errorno == ERR_INVALID_INPUT)
		ft_printf_fd(2, "minishell: %s: Invalid input.\n", name);
	else if (errorno == ERR_MALLOC)
		ft_printf_fd(2, "minishell: Malloc error!!\n");
	else if (errorno == ERR_HOME_NOT_SET)
		ft_printf_fd(2, "minishell: %s: HOME not set\n", name);
	else if (errorno == ERR_PATH_NOT_SET)
		ft_printf_fd(2, "minishell: %s: PATH not set\n", name);
	else if (errorno == ERR_FILE_NOT_FOUND)
		ft_printf_fd(2, "minishell: no such file or directory: %s\n", name);
	else if (errorno == ERR_NO_PERMISSION)
		ft_printf_fd(2, "minishell: permission denied: %s\n", name);
	else if (errorno == ERR_TOO_FEW_ARGS)
		ft_printf_fd(2, "minishell: %s: too few arguments\n", name);
	else if (errorno == ERR_TOO_MANY_ARGS)
		ft_printf_fd(2, "minishell: %s: too many arguments\n", name);
	else if (errorno == ERR_INPUT_INIT)
		ft_printf_fd(2, "minishell: \n", name);
	else if (errorno == ERR_FORK_ERROR)
		ft_printf_fd(2, "minishell: fork error: %s\n", name);
	else if (errorno == ERR_SIG)
		ft_printf_fd(2, "minishell: signal error\n");
	else if (errorno == ERR_NO_COMMAND)
		ft_printf_fd(2, "minishell: %s: Command not found\n", name);
	return (-1);
}
