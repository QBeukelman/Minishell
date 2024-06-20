/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_strip_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/24 09:51:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/20 15:43:38 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft/lib_vector/vector.h"

char	*new_strip_quotes(char *arg)
{
	int		i;
	int		len;
	t_vec	v;

	i = 0;
	len = ft_strlen(arg);
	if (ft_vec_init(&v, len) == false)
		return (false);
	if (arg[i] == is_quote(arg[i]))
		i++;
	while (arg[i])
	{
		if (arg[i] != is_quote(arg[i]))
			if (ft_vec_push(&v, arg[i]) == false)
			{
				show_error_message("vec_push", C_RED, "", X_FAILURE);
				return (NULL);
			}
		i++;
	}
	i++;
	return (free(arg), ft_vec_to_str(&v));
}
