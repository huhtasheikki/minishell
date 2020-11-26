/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 12:10:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/09 12:21:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_percent(void *param)
{
	t_all	*all;

	all = (t_all*)param;
}

void		get_percent(t_all *all)
{
	all->convert_str = ft_strdup("%");
	all->arg_len = 1;
}
