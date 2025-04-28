/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:53:38 by alejandj          #+#    #+#             */
/*   Updated: 2025/04/28 18:45:46 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

int	main(int argc, char *argv[])
{
	int	fd_in;
	
	if (argc == 5)
	{
		fd_in = open(argv[1], O_RDONLY);
		if (fd_in < 0)
			perror("fAIL IN FD_IN\n");
	}
	else
		perror("Error\n");
}