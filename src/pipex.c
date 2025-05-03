/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:53:38 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/03 19:01:59 by alejandj         ###   ########.fr       */
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

char	**get_path_cmd(char *env[])
{
	int		i;
	char	**arr_path;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			arr_path = ft_split(env[i] + 5, ':');
			break;
		}
		i++;
	}
	return (arr_path);
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
			perror("ERROR: opening infile");
			exit(EXIT_FAILURE);
		}	
		if (fd_out < 0)
		{
			perror("ERROR: opening outfile");
			exit(EXIT_FAILURE);
		}
		
		// Parsear los comandos
		cmd1 = ft_split(argv[2], ' ');
		cmd2 = ft_split(argv[3], ' ');

		// Crear la pipe
		pipe_status = pipe(pipefd);
		if (pipe_status == -1)
		{
			perror("ERROR: creating pipe");
			exit(EXIT_FAILURE);
		}

		// Crear procesos
		process1 = fork();
		if (process1 == -1)
		{
			perror("ERROR: creating process1");
			exit(EXIT_FAILURE);
		}
		else if (process1 == 0)
		{
			close(pipefd[0]);
			
			// Ahora el programa en vez de leer de la entrada estandard lee desde el archivo
			if (dup2(fd_in, STDIN_FILENO) == -1)
			{
				perror("ERROR: dup2 process1 (stdin)");
				exit(EXIT_FAILURE);
			}
			// En vez de escribir en la salida estandard escribe en el extremo de escritura de la pipe
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			{
				perror("ERROR: dup2 process1 (stdout)");
				exit(EXIT_FAILURE);
			}
			// Se ejecuta el primer comando (Tengo que hacerlo dinamico para cualquiera)
			if (execve("/bin/grep", cmd1, env) == -1)
			{
				perror("ERROR: execve process1");
				exit(EXIT_FAILURE);
			}
		}
		process2 = fork();
		if (process2 == -1)
		{
			perror("Error creating process2");
			exit(EXIT_FAILURE);
		}
		else if (process2 == 0)
		{
			close(pipefd[1]);

			// El programa lee en vez de la salida estandard lee de la pipe
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
			{
				perror("ERROR: dup2 process2 (stdin)");
				exit(EXIT_FAILURE);
			}
			// Envia la salida al archivo
			if (dup2(fd_out, STDOUT_FILENO) == -1)
			{
				perror("ERROR: dup2 process2 (stdout)");
				exit(EXIT_FAILURE);
			}
			// Se ejecuta el segundo comando
			if (execve("/bin/wc", cmd2, env) == -1)
			{
				perror("ERROR: execve process2");
				exit(EXIT_FAILURE);
			}
		}

		// Cerrar pipe
		close(pipefd[0]);
		close(pipefd[1]);
		
		// Espera a que los hijos acaben
		waitpid(process1, NULL, 0);
		waitpid(process2, NULL, 0);

		// Liberar
		free_arr(cmd1);
		free_arr(cmd2);
	}
	else
	{
		ft_putstr_fd("\033[1;31mERROR ARGUMENTS\033[0m\n", 2);
		ft_putstr_fd("\033[1;33mARGS FORMAT: ./pipex infile 'cmd1' 'cmd2' outfile\033[0m\n", 2);
		return (1);
	}
}

/*
int main(int argc, char *argv[], char *env[])
{
	ft_printf("%d\n", argc);
	ft_printf("%s\n", argv[1]);

	int i = 0;
	char **arr;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			arr = ft_split(env[i] + 5, ':');
			int j = 0;
			while (arr[j])
			{
				ft_printf("%s%s%d\n", arr[j], " ", j);
				j++;
			}
			break;
		}
		i++;
	}
	return 0;
}
*/
