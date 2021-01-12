/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:28:27 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/12 16:24:14 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarrdel(char ***arr)
{
	char	**ptr;

	if (!arr)
		return ;
	ptr = *arr;
	while (*ptr)
	{
		ft_strdel(ptr);
		ptr++;
	}
	free(**arr);
	**arr = NULL;
}
