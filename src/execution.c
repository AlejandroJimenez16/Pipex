/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:37:27 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/26 15:42:57 by alejandj         ###   ########.fr       */
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

void	manage_execve_error(char *path, char **arr_path)
{
	free(path);
	free_arr(arr_path);
	print_errors("ERROR: execve process1");
}

void	execute_absolute_path(char **cmd, char *env[])
{
	if (access(cmd[0], F_OK) != 0)
	{
		print_cmd_error("ERROR: Command not found: ", cmd[0]);
		free_arr(cmd);
	}
	else if (access(cmd[0], X_OK) != 0)
	{
		print_cmd_error("ERROR: Permission denied: ", cmd[0]);
		free_arr(cmd);
	}
	else
		execve(cmd[0], cmd, env);
}

void	execute_commands(char *env[], char **cmd)
{
	char	**arr_path;
	int		arr_path_id;
	char	*path;

	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		execute_absolute_path(cmd, env);
	else
	{
		arr_path = get_path_cmd(env);
		arr_path_id = 0;
		while (arr_path[arr_path_id] != NULL)
		{
			path = create_path(arr_path[arr_path_id++], cmd[0]);
			if (access(path, X_OK) == 0)
			{
				if (execve(path, cmd, env) == -1)
					manage_execve_error(path, arr_path);
			}
			else
				free(path);
		}
		free_arr(arr_path);
		print_cmd_error("ERROR: Command not found: ", cmd[0]);
		free_arr(cmd);
	}
}
