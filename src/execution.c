/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:37:27 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/22 00:14:32 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_path_cmd(char *env[])
{
	int		i;
	char	**arr_path;

	i = 0;
	arr_path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			arr_path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (arr_path);
}

void	*create_path(char *base, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(base, "/");
	full = ft_strjoin(temp, cmd);
	free(temp);
	return (full);
}

void	manage_execve_error(char *path, char **arr_path, char *outfile)
{
	free(path);
	free_arr(arr_path);
	print_errors("ERROR: execve process1", outfile);
}

void	execute_commands(char *env[], char **cmd, char *outfile)
{
	char	**arr_path;
	int		arr_path_id;
	char	*path;

	arr_path = get_path_cmd(env);
	arr_path_id = 0;
	while (arr_path[arr_path_id] != NULL)
	{
		path = create_path(arr_path[arr_path_id], cmd[0]);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, cmd, env) == -1)
				manage_execve_error(path, arr_path, outfile);
		}
		else
			free(path);
		arr_path_id++;
	}
	free_arr(arr_path);
	print_cmd_error("ERROR: Incorrect command: ", cmd[0], outfile);
	free_arr(cmd);
}
