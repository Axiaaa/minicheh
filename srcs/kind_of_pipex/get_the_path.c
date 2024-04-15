/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:36:38 by geymat            #+#    #+#             */
/*   Updated: 2024/04/15 17:04:49 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*shorten_command(char *command)
{
	size_t	i;

	i = 0;
	while (*command == ' ')
		command++;
	while (command[i] && command[i] != ' ')
		i++;
	command = ft_substr(command, 0, i);
	if (!command)
		return (NULL);
	replace_chars_in_str(command, -1, ' ');
	rm_useless_quotes(command);
	return (command);
}

static char	*find_command(char **paths, char *command)
{
	char	*path;
	ssize_t	i;

	i = 0;
	path = ft_strjoinwithslash(paths[i++], command);
	while (path && access(path, X_OK) && paths[i])
	{
		f_free(path);
		path = ft_strjoinwithslash(paths[i++], command);
	}
	if (!path)
		return (NULL);
	if (access(path, X_OK))
	{
		print_error("minishell", "command not found", command);
		f_free(path);
		return (NULL);
	}
	return (path);
}

char	*get_path(char **paths, char *line)
{
	char	*command;
	char	*res;

	if (!paths)
		return (NULL);
	command = shorten_command(line);
	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK))
		{
			perror("minishell");
			f_free(command);
			return (NULL);
		}
		return (command);
	}
	res = find_command(paths, command);
	f_free(command);
	return (res);
}
