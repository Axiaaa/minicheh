/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:43:06 by lcamerly          #+#    #+#             */
/*   Updated: 2024/04/15 23:39:42 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	startwithnbr(char *s)
{
	size_t i;

	i = 0;
	while (s[i] == '"' || s[i] == 39)
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		return (1);
	return (0);
}

int	do_export(char *temp, t_env **env)
{
	char	**key_value;
	t_env	*new_lst;

	key_value = sep_in_two(temp);
	if (!key_value)
		return (free_ret_1(temp));
	if (key_value[1])
	{
		replace_chars_in_str(key_value[1], -1, ' ');
		rm_useless_quotes(key_value[1]);
	}
	rm_useless_quotes(key_value[0]);
	new_lst = ft_envlstnew_frees(key_value);
	if (!new_lst)
		return (free_ret_1(temp));
	ft_envlstadd_until_sorted(env, new_lst);
	return (0);
}
