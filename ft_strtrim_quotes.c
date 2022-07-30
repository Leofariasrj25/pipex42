/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:36:21 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/29 14:12:27 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	**ft_strtrim_quotes(char **args)
{
	int		i;
	int		args_len;
	char	*aux;

	if (!args)
		return (NULL);
	i = 0;
	while (args[i] != NULL)
	{
		aux = args[i];
		args_len = ft_strlen(args[i]);
		if (args_len <= 1)
		{
			i++;
			continue ;
		}
		if (args[i][0] == args[i][args_len - 1]
			&& (args[i][0] == '\'' || args[i][0] == '"'))
		{
			args[i] = ft_substr(args[i], 1, args_len - 2);
			free(aux);
		}
		i++;
	}
	return (args);
}
