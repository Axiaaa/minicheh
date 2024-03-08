/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:13:05 by geymat            #+#    #+#             */
/*   Updated: 2024/03/07 05:04:36 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

extern int sig;

static int	quotes(char     *str)
{
	size_t	i;
	int		delimiter;

	delimiter = 0;
	i = 0;

	while (str[i])
	{
		if (delimiter == 1 && (!i || str[i - 1] != '\\') && (str[i] == '\"'))
			delimiter = 0;
		else if ((delimiter == 2) && (!i || str[i - 1] != '\\')
			&& str[i] == '\'')
			delimiter = 0;
		else if ((str[i] == '\"') && (!i || str[i - 1] != '\\') && !delimiter)
			delimiter = 1;
		else if ((str[i] == '\'') && (!i || str[i - 1] != '\\') && !delimiter)
			delimiter = 2;
		i++;
	}
	return (delimiter);
}

char	*get_a_new_line(t_env *env)
{
	char	*str;
	char	*temp;

	str = readline("MiniCheh -> ");
	if (!str)
		return(write(1, "exit\n", 5), free(str), NULL);
	if (sig == 1)
	{
		sig = 0;
		return(free(str), ft_strdup(""));
	}
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
		free(temp);
	}
	add_history(str);
	return (replace_env(str, env));
}