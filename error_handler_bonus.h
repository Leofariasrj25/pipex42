/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:21:19 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 04:21:32 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_BONUS_H
# define ERROR_HANDLER_BONUS_H

char	*fmt_error_msg(int err_num, char *custom_msg);
void	print_cmderr_msg(char *custom_msg);
int		check_infile_error(char *infile_path);
int		check_outfile_error(char *outfile_path);
#endif
