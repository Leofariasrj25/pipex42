/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 22:41:39 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 14:57:07 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"
#include "error_handler.h"
#include "file_handler.h"
#include "path_builder.h"
#include "args_parser.h"
#include "resource_cleaner.h"
#include <fcntl.h>
#include <stdio.h>

int	run_proc_p(char **program_args, int i, int size, int **pipes_fd)
{
	int	child_pid;
	int	dup2_in;
	int	dup2_out;

	child_pid = fork();
	if (child_pid == 0)
	{
		close_pipe_fds(i, size, pipes_fd);
		dup2_in = dup2(pipes_fd[i][0], 0);
		dup2_out = dup2(pipes_fd[i + 1][1], 1);
		close(pipes_fd[i][0]);
		close(pipes_fd[i + 1][1]);
		if (dup2_in != -1 && dup2_out != -1)
		{
			if (execve(program_args[0], program_args, NULL) == -1)
				print_cmderr_msg(program_args[0]);
			return (-1);
		}
		else
			return (-1);
	}
	else
		waitpid(child_pid, NULL, 0);
	return (1);
}

int	**create_pipes(int quantity)
{
	int	**pipes_fd;
	int	i;

	pipes_fd = NULL;
	pipes_fd = ft_calloc(quantity + 1, sizeof(int *));
	if (!pipes_fd)
		return (NULL);
	i = 0;
	while (i < quantity)
	{
		pipes_fd[i] = ft_calloc(2, sizeof(int));
		pipe(pipes_fd[i]);
		i++;
	}
	return (pipes_fd);
}

void	exec_pipe_node(int i, int size, char **cmd, int **pipes)
{
	close(pipes[i][1]);
	if (run_proc_p(cmd, i, size, pipes) == -1)
	{
		free_char_matrix(cmd);
		free_pipes(pipes);
		exit(-1);
	}
	free_char_matrix(cmd);
	close(pipes[i][0]);
	close(pipes[i + 1][1]);
}

void	exec_cmd_chain(int **pipes, char **args_list, char **env, int size)
{
	int		i;
	int		pipe_id;
	char	**cmd;
	char	*aux;

	i = 2;
	pipe_id = 0;
	while (pipe_id < size)
	{
		cmd = ft_split_quotes(args_list[i], ' ');
		aux = cmd[0];
		cmd[0] = get_cmd_path(cmd[0], env);
		if (aux != cmd[0])
			free(aux);
		cmd = ft_strtrim_quotes(cmd);
		exec_pipe_node(pipe_id, size, cmd, pipes);
		i++;
		pipe_id++;
	}
}

int	main(int argc, char *argv[])
{
	int			**pipes_fd;
	int			fd_infile;
	extern char	**environ;

	if (argc == 1)
		return (0);
	pipes_fd = create_pipes(argc - 2);
	fd_infile = open(argv[1], O_RDONLY);
	if (check_infile_error(argv[1]) == 0)
	{
		dup2(fd_infile, pipes_fd[0][0]);
		close(fd_infile);
		close(pipes_fd[0][1]);
	}
	else
	{
		argc--;
		argv++;
	}
	exec_cmd_chain(pipes_fd, argv, environ, argc - 3);
	close(pipes_fd[argc - 3][1]);
	write_to_outfile(argv[argc - 1], pipes_fd[argc - 3][0]);
	close(pipes_fd[argc - 3][0]);
	free_pipes(pipes_fd);
	exit(0);
}
