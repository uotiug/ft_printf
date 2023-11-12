/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:02:18 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/12 17:10:59 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_u_num(unsigned int nb)
{
	if (nb >= 10)
	{
		print_u_num(nb / 10);
		print_u_num(nb % 10);
	}
	if (nb < 10)
		ft_putchar_fd('0' + nb, 1);
}

size_t	get_unsigned_int_size(t_opt opts, unsigned int u)
{
	size_t	len;

	len = max(ft_unsigned_intlen(u), opts.dot);
	len = max(len, opts.width);
	return (len);
}

size_t	calc_u_size(int u, t_opt opts)
{
	size_t	len;

	len = 0;
	if (opts.plus || opts.space)
		len = 1;
	len += ft_unsigned_intlen(u);
	if (opts.zero)
		len += opts.width;
	return (len);
}

size_t	print_u(t_opt opts, va_list *ap)
{
	unsigned int	u;

	u = va_arg(*ap, unsigned int);
	if (!opts.minus)
		print_c_i(' ', opts.width - max(calc_u_size(u, opts), opts.dot));
	if (opts.zero)
		print_c_i('0', opts.width - ft_unsigned_intlen(u));
	if (opts.dot != -1)
		print_c_i('0', opts.dot - ft_unsigned_intlen(u));
	print_u_num(u);
	if (opts.minus)
		print_c_i(' ', opts.width - max(calc_u_size(u, opts), opts.dot));
	return (get_unsigned_int_size(opts, u));
}
