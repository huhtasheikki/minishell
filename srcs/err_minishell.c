/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 09:27:50 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/12/30 09:37:18 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		err_minishell(int errorno)
{
	if (errorno == ERR_INVALID_INPUT)
		ft_printf("INVLAID INPUT\n");
	if (errorno == ERR_MALLOC)
		ft_printf("MALLOC ERROR!!\n");
	return (-1);
}
