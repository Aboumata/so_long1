/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 00:02:54 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/21 00:02:56 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
    size_t			i;
    unsigned char	*p;

    p = (unsigned char *)ptr;
    i = 0;
    while (i < num)
    {
        p[i] = (unsigned char)value;
        i++;
    }
    return (ptr);
}
