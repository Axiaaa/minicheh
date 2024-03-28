/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:13:05 by geymat            #+#    #+#             */
/*   Updated: 2024/03/28 16:53:11 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	quotes(char *str)
{
	size_t	i;
	int		delimiter;

	delimiter = 0;
	i = 0;
	while (str[i])
	{
		if (delimiter == 1 && str[i] == '\"')
			delimiter = 0;
		else if (delimiter == 2 && str[i] == '\'')
			delimiter = 0;
		else if (str[i] == '\"' && !delimiter)
			delimiter = 1;
		else if (str[i] == '\'' && !delimiter)
			delimiter = 2;
		i++;
	}
	return (delimiter);
}

static void	remove_dobble_spaces(char *line)
{
	size_t	i;
	short	delimiter;

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
		if (!delimiter && line[i] == ' ' && line[i + 1] == ' ')
		{
			ft_strcpy(line + i, line + i + 1);
			i--;
		}
		i++;
	}
}

static void	replace_tabs_with_space(char *line)
{
	size_t	i;
	short	delimiter;

	if (!line)
		return ;
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
		if (!delimiter && line[i] >= 9 && line[i] <= 13)
			line[i] = ' ';
		i++;
	}
	remove_dobble_spaces(line);
}

char	*get_a_new_line(t_env *env)
{
	char	*str;
	char	*temp;

	str = readline(RED"MiniCheh"M" -> "RST);
	if (!str)
		return ((void *)(write(1, "exit\n", 5) * 0));
	while (quotes(str))
	{
		str = ft_strjoin_free_first(str, "\n");
		if (!str)
			return (NULL);
		temp = readline(">");
		if (!temp)
		{
			write(2, "\nsyntax error: unexpected end of file\n", 39);
			return (ft_strdup(""));
		}
		str = ft_strjoin_free_first(str, temp);
		f_free(temp);
	}
	str = ft_strjoin_free_first(str, "");
	if (str && *str)
		add_history(str);
	replace_tabs_with_space(str);
	return (replace_env(str, env));
}
