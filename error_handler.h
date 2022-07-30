/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:05:14 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/28 16:11:35 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

char	*fmt_error_msg(int err_num, char *custom_msg);
void	print_cmderr_msg(char *custom_msg);
int		check_infile_error(char *infile_path);
int		check_outfile_error(char *outfile_path);
#endif
