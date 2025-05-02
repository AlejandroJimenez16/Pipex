/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:53:38 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/02 20:16:36 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

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

int	main(int argc, char *argv[], char *env[])
{
	int		fd_in;
	int		fd_out;
	
	char	**cmd1;
	char	**cmd2;
	
	int		pipe_status;
	int		pipefd[2];

	pid_t	process1;
	pid_t	process2;
	
	if (argc == 5)
	{
		// Comprobar los fds
		fd_in = open(argv[1], O_RDONLY);
		fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_in < 0)
		{
			perror("Error opening infile");
			exit(EXIT_FAILURE);
		}	
		if (fd_out < 0)
		{
			perror("Error opening outfile");
			exit(EXIT_FAILURE);
		}
		
		// Parsear los comandos
		cmd1 = ft_split(argv[2], ' ');
		cmd2 = ft_split(argv[3], ' ');

		// Crear la pipe
		pipe_status = pipe(pipefd);
		if (pipe_status == -1)
		{
			perror("Error creating pipe");
			exit(EXIT_FAILURE);
		}

		// Crear procesos
		process1 = fork();
		if (process1 == -1)
		{
			perror("Error creating process1");
			exit(EXIT_FAILURE);
		}
		else if (process1 == 0)
		{
			ft_printf("Soy un proceso hijo %d\n", process1);
			exit(0);
		}
		process2 = fork();
		if (process2 == -1)
		{
			perror("Error creating process2");
			exit(EXIT_FAILURE);
		}
		else if (process2 == 0)
		{
			ft_printf("Soy un proceso hijo %d\n", process2);
			exit(0);
		}

		// Liberar
		free_arr(cmd1);
		free_arr(cmd2);
	}
	else
	{
		ft_putstr_fd("\033[1;31mError passing arguments\033[0m\n", 2);
		ft_putstr_fd("\033[0;33mARGS FORMAT: ./pipex infile 'cmd1' 'cmd2' outfile\033[0m\n", 2);
		return (1);
	}
}
