/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 09:27:50 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/10 12:37:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		err_minishell(int errorno, char *name)
{
	if (errorno == ERR_INVALID_INPUT)
		ft_printf("minishell: %s: INVLAID INPUT\n", name);
	else if (errorno == ERR_MALLOC)
		ft_printf("minishell: MALLOC ERROR!!\n");
	else if (errorno == ERR_HOME_NOT_SET)
		ft_printf("minishell: %s: HOME not set\n", name);
	else if (errorno == ERR_PATH_NOT_SET)
		ft_printf("minishell: %s: PATH not set\n", name);
	else if (errorno == ERR_FILE_NOT_FOUND)
		ft_printf("minishell: no such file or directory: %s\n", name);
	else if (errorno == ERR_NO_PERMISSION)
		ft_printf("minishell: permission denied: %s\n", name);
	else if (errorno == ERR_TOO_FEW_ARGS)
		ft_printf("minishell: %s: too few arguments\n", name);
	else if (errorno == ERR_TOO_MANY_ARGS)
		ft_printf("minishell: %s: too many arguments\n", name);
	else if (errorno == ERR_INPUT_INIT)
		ft_printf("minishell: \n", name);
	else if (errorno == ERR_FORK_ERROR)
		ft_printf("minishell: fork error: %s\n", name);
	else if (errorno == ERR_SIG)
		ft_printf("minishell: signal error\n");
	return (-1);
}
