/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:52:47 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/05 16:55:09 by alejandj         ###   ########.fr       */
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

void	print_errors(char *error, char *outfile)
{
	ft_putstr_fd("\033[1;31m", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\033[0m\n", 2);
	unlink(outfile);
	exit(EXIT_FAILURE);
}

void	fail_args(void)
{
	ft_putstr_fd("\033[1;31mERROR ARGUMENTS\033[0m\n", 2);
	ft_putstr_fd("\033[1;33m", 2);
	ft_putstr_fd("ARGS FORMAT: ./pipex infile 'cmd1' 'cmd2' outfile", 2);
	ft_putstr_fd("\033[0m\n", 2);
}
