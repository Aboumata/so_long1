/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 00:03:17 by aboumata          #+#    #+#             */
/*   Updated: 2025/04/21 00:03:18 by aboumata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strchr(const char *string, int c)
{
    int				i;
    unsigned char	c_char;

    c_char = (unsigned char)c;
    i = 0;
    while (string[i] != '\0')
    {
        if ((unsigned char)string[i] == c_char)
            return ((char *)string + i);
        i++;
    }
    if (c_char == '\0')
        return ((char *)string + i);
    return (NULL);
}
