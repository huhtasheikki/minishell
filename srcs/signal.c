/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:17:54 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/10 12:02:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int signo)
{
	ft_printf("\n");
	(void)signo;
	if (g_pid != 0)
		kill(g_pid, 0);
	else
		print_prompt(PROMPT_NORMAL);
}
