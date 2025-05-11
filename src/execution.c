/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:37:27 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/11 21:53:11 by alejandj         ###   ########.fr       */
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

void	execute_commands(char *env[], char **cmd, char *outfile)
{
	char	**arr_path;
	int		arr_path_id;
	char	*path;
	char	*temp;

	path = ft_strdup("");
	arr_path = get_path_cmd(env);
	arr_path_id = 0;
	while (arr_path[arr_path_id] != NULL)
	{
		temp = ft_strjoin(arr_path[arr_path_id], "/");
		path = ft_strjoin(temp, cmd[0]);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, cmd, env) == -1)
				print_errors("ERROR: execve process1", outfile);
		}
		else
			arr_path_id++;
	}
	print_cmd_error("ERROR: Incorrect command: ", cmd[0], outfile);
}
