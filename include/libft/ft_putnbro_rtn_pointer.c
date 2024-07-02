/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbro_rtn_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:50:23 by pirichar          #+#    #+#             */
/*   Updated: 2022/02/02 09:51:56 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbro_rtn_ptr(size_t num, size_t b_len, char *base, int *sum)
{
	char	c;

	ft_putchar('0');
	ft_putchar('x');
	(*sum) += 2;
	if (num >= base_len)
		ft_putnbro_rtn(num / base_len, base_len, base, sum);
	c = base[(num % base_len)];
	write(1, &c, 1);
	(*sum)++;
}
