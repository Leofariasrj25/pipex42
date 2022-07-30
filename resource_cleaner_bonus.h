/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_cleaner_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:23:00 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 04:23:15 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_CLEANER_BONUS_H
# define RESOURCE_CLEANER_BONUS_H

void	free_char_matrix(char **matrix);
void	free_pipes(int **pipes);
void	close_pipe_fds(int i, int size, int **pipes);
#endif
