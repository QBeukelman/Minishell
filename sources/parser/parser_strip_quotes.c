/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_strip_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/24 09:51:56 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/06 14:13:54 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int next_quote_char(char *arg, int i, int quote_char)
// {
// 	int		len;

// 	i++;
// 	len = ft_strlen(arg);
// 	while (i < len)
// 	{
// 		if (arg[i] == quote_char)
// 			return (i);
// 		i++;
// 	}
// 	return (i);
// }

// static char *strip_quotes(char *arg)
// {
//     int i;
//     int len;
//     int quote_type;
//     char *new_arg;

// 	i = 0;
//     len = ft_strlen(arg);
//     while (i < len)
//     {
//         if (is_quote(arg[i]))
//         {
//             quote_type = is_quote(arg[i]);
//             new_arg = ft_str_remove_char(arg, i, quote_type);
//             if (new_arg == NULL)
//                 return (NULL);
//             arg = new_arg;
//             i--;
//             i = next_quote_char(arg, i, quote_type);
//             if (is_quote(arg[i]) == quote_type)
//             {
//                 new_arg = ft_str_remove_char(arg, i, quote_type);
//                 if (new_arg == NULL)
//                     return (NULL);
//                 free(arg);
//                 arg = new_arg;
//             }
//             i--;
//             len = ft_strlen(arg);
//         }
//         i++;
//     }
//     return (arg);
// }

static int	count_quotes(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;

	while (arg[i])
	{
		if (is_quote(arg[i]))
			count++;
		i++;
	}
	return (count);
}

static char	*strip_quotes(char *arg)
{
	int	len;
	int	i;
	int	j;
	int	count;
	char	*new_arg;

	count = count_quotes(arg);
	len = ft_strlen(arg);
	i = 0;
	j = 0;
	new_arg = safe_malloc(len - count + 1);
	while (i < len)
	{
		if (!is_quote(arg[i]))
		{
			new_arg[j] = arg[i];
			j++;
		}
		i++;
	}
	new_arg[j] = '\0';
	free(arg);
	arg = new_arg;
	return (new_arg);
}

char	*strip_quote_for_type(char *arg)
{
	char	*new_arg;	

	new_arg = strip_quotes(arg);
	return (new_arg);
}
