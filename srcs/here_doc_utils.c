/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:22:42 by geymat            #+#    #+#             */
/*   Updated: 2024/04/16 14:45:18 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_a_name(void)
{
	char		*name;
	struct stat	buffer;
	int			i;

	name = ft_strdup(".here_doc000000000");
	if (!name)
		return (NULL);
	i = 9;
	while (!stat(name, &buffer))
	{
		name[i] += 1;
		if (name[i] == 9)
			i++;
		if (name[17] == '9')
			return (NULL);
	}
	return (name);
}

static int	limiter_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
		i++;
	return (i);
}

int	replace_all_here_docs(char **line, t_env *env)
{
	size_t	i;
	char	*name;

	i = 0;
	while (*line && i < ft_strlen(*line))
	{
		if ((*line)[i] == '<' && (*line)[i + 1] == '<')
		{
			name = get_a_name();
			if (!name)
				return (-1);
			if (!get_heredoc(*line + i + 2, env, name))
				replace_inside(line, i + 2,
					limiter_size(*line + 2 + i) + i + 2, name);
			else
			{
				replace_inside(line, i + 2,
					limiter_size((*line) + 2 + i) + i + 2, "E");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
