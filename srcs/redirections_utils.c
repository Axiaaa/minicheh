/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:59:18 by geymat            #+#    #+#             */
/*   Updated: 2024/03/29 08:49:48 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	path_len(char *line)
{
	size_t	i;
	short	delimiter;

	i = 0;
	delimiter = 0;
	while (line[i])
	{
		if ((delimiter == 1 && line[i] == '\"')
			|| (delimiter == 2 && line[i] == '\''))
			delimiter = 0;
		else if ((line[i] == '\"' || line[i] == '\'') && !delimiter)
			delimiter = 1 + (line[i] == '\'');
		else if (!ft_isalnum(line[i]) && line[i] != '_' && line[i] != '/'
			&& line[i] != '-' && line[i] != '.' && line[i] != '\''
			&& line[i] != '\"' && !delimiter)
			return (i);
		i++;
	}
	return (i);
}

static char	*get_file(char *line, size_t len)
{
	char	*file;

	file = ft_substr(line, 0, len);
	if (!file)
		return (NULL);
	replace_chars_in_str(file, -1, ' ');
	rm_useless_quotes(file);
	return (file);
}

int	open_dup2(char *line, size_t len, int flag)
{
	char	*file;
	int		fd_temp;
	int		res;

	fd_temp = -3;
	file = get_file(line, len);
	if (!file)
		return (-1);
	if (flag == 0 || (flag == 1 && *file != 'E'))
		fd_temp = open(file, O_RDONLY);
	if (flag == 1 && *file != 'E')
		unlink(file);
	else if (flag == 1)
		fd_temp = -1;
	else if (flag == 2)
		fd_temp = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (flag == 3)
		fd_temp = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd_temp == -1 && flag != 1)
		perror(file);
	f_free(file);
	if (fd_temp == -3 || fd_temp == -2 || fd_temp == -1)
		return (-fd_temp - 3);
	res = dup2(fd_temp, flag / 2);
	return ((close(fd_temp) || 1) * res);
}
