/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:40:54 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 04:31:45 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>
#include "libft/libft.h"

char	*fmt_error_msg(int err_num, char *custom_msg)
{
	char	*error_msg;
	char	*aux;

	error_msg = strerror(err_num);
	error_msg = ft_strjoin("pipex: ", error_msg);
	aux = error_msg;
	if (!custom_msg)
		custom_msg = "";
	error_msg = ft_strjoin(error_msg, custom_msg);
	free(aux);
	return (error_msg);
}

void	print_cmderr_msg(char *custom_msg)
{
	char	*err_msg;
	char	*aux;

	err_msg = NULL;
	if (errno == ENOENT)
		err_msg = ft_strjoin("pipex: command not found: ", custom_msg);
	else if (errno == EACCES)
	{
		aux = ft_strjoin(": ", custom_msg);
		err_msg = fmt_error_msg(errno, aux);
		free(aux);
	}
	else
		perror("pipex");
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	free(err_msg);
}

int	check_infile_error(char *infile_path)
{
	char	*error_msg;

	if (access(infile_path, F_OK) == -1 || access(infile_path, R_OK) == -1)
	{
		infile_path = ft_strjoin(": ", infile_path);
		error_msg = fmt_error_msg(errno, infile_path);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
		free(error_msg);
		return (-1);
	}
	return (0);
}

int	check_outfile_error(char *outfile_path)
{
	char	*aux;
	char	*error_msg;

	if (access(outfile_path, F_OK) == 0 && access(outfile_path, W_OK) == -1)
	{
		aux = ft_strdup(outfile_path);
		outfile_path = ft_strjoin(": ", outfile_path);
		free(aux);
		error_msg = fmt_error_msg(errno, outfile_path);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
		free(error_msg);
		return (-1);
	}
	return (1);
}
