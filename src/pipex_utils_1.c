/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:52:47 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/29 13:08:02 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_errors(char *error, char **cmd1, char **cmd2)
{
	if (error)
	{
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
	}
	free_arr(cmd1);
	free_arr(cmd2);
	exit(EXIT_FAILURE);
}

void	print_cmd_error(char *error, char *cmd)
{
	char	*temp1;
	char	*temp2;
	char	*final;

	temp1 = ft_strjoin(cmd, ": ");
	temp2 = ft_strjoin(temp1, error);
	final = ft_strjoin(temp2, "\n");
	write(2, final, ft_strlen(final));
	free(temp1);
	free(temp2);
	free(final);
}

void	fail_args(void)
{
	ft_putstr_fd("\033[1;31mERROR ARGUMENTS\033[0m\n", 2);
	ft_putstr_fd("\033[1;33m", 2);
	ft_putstr_fd("ARGS FORMAT: ./pipex infile 'cmd1' 'cmd2' outfile", 2);
	ft_putstr_fd("\033[0m\n", 2);
}

char	**get_path_cmd(char *env[])
{
	int		i;
	char	**arr_path;

	if (!env)
		return (NULL);
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
