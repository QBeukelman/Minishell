/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 15:20:08 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/06 18:34:26 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_vector(t_vec *v)
{
	if (v)
	{
		if (v->data)
		{
			free(v->data);
			v->data = NULL;
		}
		free(v);	
	}
}

// * init
bool	vec_init(t_vec *v, unsigned int size) 
{
	v->data = malloc(sizeof(char) * size);
	if (!v->data)
		return (false);
	v->len = 0;
	v->capacity = size;
	return (true);
}

// * vergroot huidige memory x2
bool	vec_resize(t_vec *v) 
{
	char *tmp;

	tmp = malloc(sizeof(char) * (v->capacity * 2));
	if (!tmp) 
		return (false);
	ft_memcpy(tmp, v->data,  v->len);
	free(v->data);
	v->data = tmp;
	v->capacity *= 2;
	return (true);
}

// * elke keer wanneer geen char in vec
// * pusht de character naar de vector
// * if env variable -> directly push
// * if NULL, do niks
bool	vec_push(t_vec *v, char c) 
{
	if (v->len == v->capacity) 
	{
		if (!vec_resize(v))
			return (false);
	}
	v->data[v->len] = c;
	v->len++;
	return (true);
}

// * geeft een string terug van de data in de vector
// * haalt string naar vector (only at end)
// * 
char	*get_str(t_vec *v) 
{
	char	*tmp;

	if (!vec_push(v, '\0')) 
		return (NULL);
	tmp = malloc(sizeof(char) * v->len);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, v->data, v->len);
	free(v->data);
	v->data = tmp;
	return (tmp);
}
