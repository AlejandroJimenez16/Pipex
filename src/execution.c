/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:37:27 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/29 17:17:09 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	*create_path(char *base, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(base, "/");
	full = ft_strjoin(temp, cmd);
	free(temp);
	return (full);
}

int	manage_execve_error(char **arr_path, char *path, char **cmd)
{
	free_arr(arr_path);
	free(path);
	free_arr(cmd);
	return (127);
}

int	execute_absolute_path(char **cmd, char *env[])
{
	if (access(cmd[0], F_OK) != 0)
	{
		print_cmd_error("Command not found", cmd[0]);
		free_arr(cmd);
		return (127);
	}
	else if (access(cmd[0], X_OK) != 0)
	{
		print_cmd_error("permission denied", cmd[0]);
		free_arr(cmd);
		return (126);
	}
	else
	{
		execve(cmd[0], cmd, env);
		free_arr(cmd);
		return (127);
	}
}

int	execute_normal_command(char *env[], char **cmd)
{
	char	**arr_path;
	int		arr_path_id;
	char	*path;
	int		permissions;

	permissions = 0;
	arr_path = get_path_cmd(env);
	arr_path_id = 0;
	while (arr_path && arr_path[arr_path_id] != NULL)
	{
		path = create_path(arr_path[arr_path_id++], cmd[0]);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				if (execve(path, cmd, env) == -1)
					return (manage_execve_error(arr_path, path, cmd));
			}
			else
				permissions = 1;
		}
		free(path);
	}
	free_arr(arr_path);
	return (manage_exit_execution(permissions, cmd));
}

int	execute_commands(char *env[], char **cmd)
{
	int	exit_code;

	if (!cmd || !cmd[0] || !cmd[0][0])
	{
		print_cmd_error("command not found", "");
		free_arr(cmd);
		return (127);
	}
	else if (cmd[0][0] == '.' || cmd[0][0] == '/')
		exit_code = execute_absolute_path(cmd, env);
	else
		exit_code = execute_normal_command(env, cmd);
	return (exit_code);
}
