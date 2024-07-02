/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 09:42:52 by pirichar          #+#    #+#             */
/*   Updated: 2022/02/02 09:44:56 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbro(size_t num, size_t base_len, char *base)
{
	char	c;

	if (num >= base_len)
		ft_putnbro(num / base_len, base_len, base);
	c = base[(num % base_len)];
	write(1, &c, 1);
}
