/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:22:37 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 11:17:06 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_format_id(t_all *all)
{
	int		i;
	char	*temp_ptr;

	i = 0;
	temp_ptr = all->format_ptr;
	while (*temp_ptr && !ft_strchr(FORMAT_ID, *temp_ptr))
		temp_ptr++;
	while (i < FORMAT_ID_SIZE)
	{
		if (*temp_ptr == all->format_id_str[i])
		{
			all->format_id = 1 << i;
			all->format_ptr = temp_ptr + 1;
			return (1);
		}
		i++;
	}
	free(all->padding_str);
	return (0);
}
