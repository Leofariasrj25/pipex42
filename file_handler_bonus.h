/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:21:45 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 05:58:55 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HANDLER_BONUS_H
# define FILE_HANDLER_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		handle_read_error(int *bytes_read, char *file_cont, char *read_bf);
char	*read_file(int fd);
int		write_to_outfile(char *outfile_path, int outpipe_fd, int here_doc);
int		here_doc_parser(char **argv);
#endif
