/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_shorthand.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 11:05:40 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 09:15:49 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SHORTHAND_H
# define LIBFT_SHORTHAND_H

/*
** SHORTHANDS FOR VARIABLE TYPES WITH BITSIZES
*/

typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef unsigned int		t_u32;
typedef unsigned long		t_u64;
typedef unsigned long long	t_ul64;
typedef char				t_s8;
typedef short				t_s16;
typedef int					t_s32;
typedef long				t_s64;
typedef long long			t_sl64;
typedef float				t_f32;
typedef double				t_f64;
typedef long double			t_f80;

# define _MSB_ 			0x8000000000000000
# define _NOT_MSB_		0x7FFFFFFFFFFFFFFF
# define _ALLBITS_		0xFFFFFFFFFFFFFFFF

#endif
