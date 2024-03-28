/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:58:32 by geymat            #+#    #+#             */
/*   Updated: 2024/03/28 17:00:08 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	line_shortener(char *line, int flag)
{
	int		spaces;
	size_t	len;
	int		returned;

	returned = -1;
	spaces = 0;
	if (line[1] == '>' && flag == 0)
		write(2, "we can't handle that redirection\n", 34);
	while (*(line + (flag == 1 || flag == 3) + spaces + 1) == ' ')
		spaces++;
	len = path_len(line + (flag == 1 || flag == 3) + spaces + 1);
	if (len != 0)
		returned = open_dup2(line + (flag == 1 || flag == 3) \
				+ spaces + 1, len, flag);
	else
		write(2, "minishell: syntax error near unexpected token\n", 47);
	ft_strcpy(line, line + (flag == 1 || flag == 3) + spaces + 1 + len);
	return (returned);
}

static int	directions_hub(char *line, size_t *i, int delimiter)
{
	int	res;

	if (line[*i] == '<' && !delimiter)
	{
		res = line_shortener(line + *i, 0 + (line[*i + 1] == '<'));
		if (res < 0)
			return (res);
		(*i)--;
	}
	if (line[*i] == '>' && !delimiter)
	{
		res = line_shortener(line + *i, 2 + (line[*i + 1] == '>'));
		if (res < 0)
			return (res);
		(*i)--;
	}
	return (0);
}

int	redirections(char *line)
{
	size_t	i;
	int		delimiter;
	int		res;

	i = 0;
	delimiter = 0;
	while (line[i])
	{
		if (delimiter == 1 && line[i] == '\"')
			delimiter = 0;
		else if (delimiter == 2 && line[i] == '\'')
			delimiter = 0;
		else if (line[i] == '\"' && !delimiter)
			delimiter = 1;
		else if (line[i] == '\'' && !delimiter)
			delimiter = 2;
		res = directions_hub(line, &i, delimiter);
		if (res < 0)
			return (res);
		i++;
	}
	return (0);
}
