/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:31:26 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/11 19:43:08 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

// TO-DO: Implement command passing via cmd line
void	run_comm(char *cmd[], int *pipe_fd, unsigned int op)
{
	pid_t child_p;
	int	in;
	int out;
	
	child_p = fork();
	in = pipe_fd[0];
	out = pipe_fd[1];
	if (child_p != 0)
	{
		if (op == 0)
		{
			close(out);
			dup2(in, 0);
		}
		else if (op == 1)
		{
			close(in);
			dup2(out, 1);
		}
		execve(cmd[0], cmd, NULL);
	}
	else
		wait(&child_p);
}

void	run_in_comm(char *cmd[], int *pipe_fd)
{
	run_comm(cmd, pipe_fd, 1);
}

void	run_out_comm(char *cmd[], int *pipe_fd)
{
	run_comm(cmd, pipe_fd, 0);
}

int	main(int argc, char *argv[])
{
	int		pipe_fd[2] = {0};
	int		std_stream[2] = {0};

	pipe(pipe_fd);
	char *cmd1[] = {"/bin/ls", ".", NULL};
	char *cmd2[] = {"/usr/bin/wc", "-c", NULL};

	std_stream[0] = dup(0);
	std_stream[1] = dup(1);
	run_in_comm(cmd1, pipe_fd);
	run_out_comm(cmd2, pipe_fd);
}
