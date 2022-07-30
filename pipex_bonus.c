/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:00:44 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 13:47:03 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex_bonus.h"
#include "error_handler_bonus.h"
#include "file_handler_bonus.h"
#include "path_builder_bonus.h"
#include "args_parser_bonus.h"
#include "resource_cleaner_bonus.h"
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

	i = 0;
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
	int			arg_i;
	int			fd_infile;
	extern char	**environ;

	if (argc == 1)
		return (0);
	fd_infile = here_doc_parser(argv);
	arg_i = 3;
	if (fd_infile != -1)
		arg_i++;
	if (fd_infile == -1 && check_infile_error(argv[1]) == 0)
		fd_infile = open(argv[1], O_RDONLY);
	pipes_fd = create_pipes((argc - arg_i) + 1);
	dup2(fd_infile, pipes_fd[0][0]);
	close(pipes_fd[0][1]);
	exec_cmd_chain(pipes_fd, &argv[arg_i - 1], environ, argc - arg_i);
	close(pipes_fd[argc - arg_i][1]);
	write_to_outfile(argv[argc - 1], pipes_fd[argc - arg_i][0], arg_i);
	close(pipes_fd[argc - arg_i][0]);
	free_pipes(pipes_fd);
	close(fd_infile);
	exit(0);
}
