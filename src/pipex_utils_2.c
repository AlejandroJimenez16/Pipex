/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:18:56 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/29 17:15:49 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	manage_exit_execution(int permissions, char **cmd)
{
	if (permissions)
	{
		print_cmd_error("permission denied", cmd[0]);
		free_arr(cmd);
		return (126);
	}
	else
	{
		print_cmd_error("command not found", cmd[0]);
		free_arr(cmd);
		return (127);
	}
}
