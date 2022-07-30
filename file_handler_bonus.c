/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:02:11 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 10:26:43 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex_bonus.h"
#include "file_handler_bonus.h"
#include "error_handler_bonus.h"
#include "get_next_line/get_next_line.h"
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

int	write_to_outfile(char *outfile_path, int outpipe_fd, int here_doc)
{
	char	*outpipe_cont;
	int		outfile_fd;
	int		bytes_written;

	if (check_outfile_error(outfile_path) == -1)
		return (-1);
	if (here_doc == 3)
		outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

int	re_open(int fd, char *filename)
{
	int	new_fd;

	close(fd);
	new_fd = open(filename, O_RDONLY);
	unlink(filename);
	return (new_fd);
}

int	here_doc_parser(char **argv)
{
	char	*temp;
	char	*delim;
	int		hd_fd;

	if (ft_strncmp("here_doc", argv[1], ft_strlen("here_doc")) == 0)
	{
		temp = NULL;
		hd_fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		delim = argv[2];
		while (1)
		{
			ft_putchar_fd('>', 1);
			temp = get_next_line(0);
			if (ft_strncmp(delim, temp, ft_strlen(delim)) == 0
				&& ft_strlen(temp) - 1 == ft_strlen(delim))
				break ;
			else
				write(hd_fd, temp, ft_strlen(temp));
			free(temp);
		}
		free(temp);
		return (re_open(hd_fd, ".here_doc"));
	}
	return (-1);
}
