/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:27:31 by geymat            #+#    #+#             */
/*   Updated: 2024/04/15 18:01:40 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	loops_minishell(t_env **env)
{
	char	*line;

	line = f_malloc(1);
	if (line)
		line[0] = 0;
	while (line && ft_strncmp(line, "exit", 42))
	{
		f_free(line);
		signal(SIGINT, &sahandler_true);
		signal(SIGQUIT, SIG_IGN);
		line = get_a_new_line(*env);
		signal(SIGINT, &sahandler_fake);
		signal(SIGQUIT, &sahandler_fake);
		if (!line)
			return ;
		executions(&line, env);
	}
	if (line)
		f_free(line);
}
