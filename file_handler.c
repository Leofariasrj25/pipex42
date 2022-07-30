/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:30:16 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/28 19:03:40 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include "file_handler.h"
#include "error_handler.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	handle_read_error(int *bytes_read, char *file_cont, char *read_bf)
{
	if (*bytes_read == -1)
	{
		perror("pipex");
		free(file_cont);
		free(read_bf);
		return (-1);
	}
	else
		return (0);
}

char	*read_file(int fd)
{
	int		bytes_read;
	char	*read_bf;
	char	*file_cont;
	char	*aux;

	bytes_read = -1;
	read_bf = ft_calloc(BUFFER_SIZE, 1);
	file_cont = NULL;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, read_bf, BUFFER_SIZE);
		if (handle_read_error(&bytes_read, file_cont, read_bf) == -1)
			return (NULL);
		read_bf[bytes_read] = '\0';
		if (!file_cont)
			file_cont = ft_strdup(read_bf);
		else
		{
			aux = file_cont;
			file_cont = ft_strjoin(file_cont, read_bf);
			free(aux);
		}
	}
	free(read_bf);
	return (file_cont);
}

int	write_to_outfile(char *outfile_path, int outpipe_fd)
{
	char	*outpipe_cont;
	int		outfile_fd;
	int		bytes_written;

	if (check_outfile_error(outfile_path) == -1)
		return (-1);
	outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	outpipe_cont = read_file(outpipe_fd);
	bytes_written = write(outfile_fd, outpipe_cont, ft_strlen(outpipe_cont));
	close(outfile_fd);
	close(outpipe_fd);
	free(outpipe_cont);
	if (bytes_written != -1)
		return (0);
	else
		return (-1);
}
/*char	*get_file_cont(char *infile_path)
{
	char	*file_cont;
	int		fd;
	
	if (check_infile_error(infile_path) == -1)
		return (NULL);
	fd = open(infile_path, O_RDONLY);
	file_cont = read_file(fd);
	return (file_cont);
}*/
