/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:15:38 by geymat            #+#    #+#             */
/*   Updated: 2024/04/02 12:11:26 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	only_char_until_space(char *line, char c)
{
	size_t	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != ' ')
	{
		if (line[i] != c)
			return (0);
		i++;
	}
	return (i);
}

static int	parameters_nl(char *line)
{
	size_t	n;
	int		res;

	if (!*line)
		return (0);
	n = only_char_until_space(line + 1, 'n');
	res = (n != 0);
	while (line[0] == '-' && n)
	{
		ft_strcpy(line, line + n + 1);
		while (*line == ' ')
			line++;
		n = only_char_until_space(line + 1, 'n');
	}
	return (res);
}

void	replace_chars_in_str(char *str, char c1, char c2)
{
	while (*str)
	{
		if (*str == c1)
			*str = c2;
		str++;
	}
}

void	replace_chars_in_argv(char **argv, char c1, char c2)
{
	while (*argv)
	{
		replace_chars_in_str(*argv, c1, c2);
		argv++;
	}
}

int	bi_echo(char *line)
{
	short	b00l;
	int		fd[2];

	if (!redirect_before_bi(line, fd))
		return (the_return_value(1));
	while (*line == ' ')
		line++;
	line += 4;
	while (*line == ' ')
		line++;
	b00l = parameters_nl(line);
	while (*line == ' ')
		line++;
	rm_useless_quotes(line);
	line = ft_strdup(line);
	if (!b00l)
		line = ft_strjoin_free_first(line, "\n");
	if (!line)
		return (the_return_value(1));
	replace_chars_in_str(line, -1, ' ');
	write(1, line, ft_strlen(line));
	the_return_value(0);
	f_free(line);
	restaure_redirections_bi(fd);
	return (0);
}
