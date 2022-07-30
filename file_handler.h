/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:12:23 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/28 19:12:10 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HANDLER_H
# define FILE_HANDLER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		handle_read_error(int *bytes_read, char *file_cont, char *read_bf);
char	*read_file(int fd);
int		write_to_outfile(char *outfile_path, int outpipe_fd);
#endif
