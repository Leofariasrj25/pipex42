/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleaner.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:23:38 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/29 16:39:21 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_CLEANER_H
# define RESOURCE_CLEANER_H

void	free_char_matrix(char **matrix);
void	free_pipes(int **pipes);
void	close_pipe_fds(int i, int size, int **pipes);
#endif
