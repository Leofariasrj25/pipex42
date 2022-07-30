/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_builder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:03:43 by lfarias-          #+#    #+#             */
/*   Updated: 2022/07/30 04:26:46 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_builder_bonus.h"

char	*build_path(char **paths, char *cmd_name)
{
	int		i;
	char	*fullpath;
	char	*aux;

	i = 0;
	fullpath = NULL;
	aux = NULL;
	while (paths[i] != NULL)
	{
		fullpath = ft_strjoin(paths[i], "/");
		aux = fullpath;
		fullpath = ft_strjoin(fullpath, cmd_name);
		free(aux);
		if (access(fullpath, F_OK) == 0 && access(fullpath, X_OK) == 0)
			return (fullpath);
		free(fullpath);
		i++;
	}
	return (cmd_name);
}

char	*get_cmd_path(char *cmd_name, char **environ)
{
	char	**paths;
	char	*fullpath;
	int		i;

	fullpath = NULL;
	if (access(cmd_name, F_OK | X_OK) == 0)
		return (cmd_name);
	if (ft_strncmp(cmd_name, "./", 2) == 0 && (access(cmd_name, F_OK) == 0
			|| access(cmd_name, X_OK) == 0))
		return (cmd_name);
	i = 0;
	while (environ[i] != NULL && ft_strncmp("PATH=", environ[i], 5) != 0)
		i++;
	if (!environ[i])
		return (NULL);
	paths = ft_split(environ[i], ':');
	fullpath = build_path(paths, cmd_name);
	i = 0;
	while (paths && paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	return (fullpath);
}
