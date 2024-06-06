/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 08:50:40 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/06/06 18:32:54 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// The memcpy function copies n bytes from memory area src to
// memory area dst.
//
// Assignment: Recreate Standard C library function memcpy(3).
// Paramaters: 
// Return Value: Memcpy is a void function. However it returns the orignal
// value of dst, copied to the source, src.
//
// Notes:
// We need to type cast src and dst addresses to (char *).
// The memcpy is useful in forwarding copy but memmove is useful in case of 
// overlapping scenarios.

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*i_src;
	char		*i_dst;
	size_t		i;

	i_src = (char *)src;
	i_dst = (char *)dst;
	if (!n || src == dst)
		return (dst);
	i = 0;
	while (i < n)
	{
		i_dst[i] = i_src[i];
		i++;
	}
	// i_dst[i] = 0;
	return (dst);
}
