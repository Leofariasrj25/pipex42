/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:41:56 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/29 23:04:06 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resource_cleaner.h"
#include <stdlib.h>
#include <unistd.h>

void	free_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_pipe_fds(int i, int size, int **pipes)
{
	int	j;

	j = 0;
	while (j < size)
	{
		if (j != i)
			close(pipes[j][0]);
		if (j != i + 1)
			close(pipes[j][1]);
		j++;
	}
}
