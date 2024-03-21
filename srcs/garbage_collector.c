/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:30:03 by geymat            #+#    #+#             */
/*   Updated: 2024/03/21 03:38:35 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/collector.h"

static	t_alloc	*new_alloc(void *alloc)
{
	t_alloc	*temp;

	temp = f_malloc(sizeof(t_alloc));
	if (!temp)
		return (NULL);
	temp->alloc = alloc;
	temp->next = NULL;
	return (temp);
}

static void	full_destruction(t_alloc *first)
{
	t_alloc		*actual;
	t_alloc		*temp;

	actual = first;
	while (actual)
	{
		if (actual->alloc)
			free(actual->alloc);
		temp = actual->next;
		free(actual);
		actual = temp;
	}
}

static void	one_single_free(void *alloc, t_alloc *actual)
{
	while (actual && actual->alloc != alloc)
		actual = actual->next;
	if (actual)
	{
		free(actual->alloc);
		actual->alloc = NULL;
	}
	return ;
}

void	add_del_everything(void *alloc, short delete)
{
	static t_alloc	*first = NULL;
	t_alloc		*temp;

	if (delete == 1)
	{
		full_destruction(first);
		return ;
	}
	if (delete == 2)
	{
		one_single_free(alloc, first);
		return ;
	}
	if (!first)
	{
		first = new_alloc(alloc);
		return ;
	}
	temp = first;
	while (temp)
		temp = temp->next;
	temp->next = new_alloc(alloc);
}
