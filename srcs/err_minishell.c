/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 09:27:50 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/13 15:52:07 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		err_minishell(int errorno, char *name)
{
	if (errorno == ERR_INVALID_INPUT)
		ft_printf("%s: INVLAID INPUT\n", name);
	else if (errorno == ERR_MALLOC)
		ft_printf("MALLOC ERROR!!\n");
	else if (errorno == ERR_HOME_NOT_SET)
		ft_printf("%s: HOME not set\n", name);
	return (-1);
}
