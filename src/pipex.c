/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:53:38 by alejandj          #+#    #+#             */
/*   Updated: 2025/05/28 19:33:41 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process_1(t_pipex *pipex)
{
	int	exit_code;

	pipex->process1 = fork();
	if (pipex->process1 == -1)
		print_errors("ERROR: creating process1", pipex->cmd1, pipex->cmd2);
	else if (pipex->process1 == 0)
	{
		close(pipex->pipefd[0]);
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			print_errors(NULL, pipex->cmd1, pipex->cmd2);
		if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			print_errors(NULL, pipex->cmd1, pipex->cmd2);
		exit_code = execute_commands(pipex->env, pipex->cmd1);
		free_arr(pipex->cmd2);
		exit(exit_code);
	}
}

void	child_process_2(t_pipex *pipex)
{
	int	exit_code;

	pipex->process2 = fork();
	if (pipex->process2 == -1)
		print_errors("Error creating process2", pipex->cmd1, pipex->cmd2);
	else if (pipex->process2 == 0)
	{
		close(pipex->pipefd[1]);
		if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
			print_errors(NULL, pipex->cmd1, pipex->cmd2);
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			print_errors(NULL, pipex->cmd1, pipex->cmd2);
		exit_code = execute_commands(pipex->env, pipex->cmd2);
		free_arr(pipex->cmd1);
		exit(exit_code);
	}
}

void	cleanup(t_pipex *pipex)
{
	int	status2;

	close(pipex->fd_in);
	close(pipex->fd_out);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->process1, NULL, 0);
	waitpid(pipex->process2, &status2, 0);
	free_arr(pipex->cmd1);
	free_arr(pipex->cmd2);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
}

void	init_fds(int *fd_in, int *fd_out, char *infile, char *outfile)
{
	*fd_in = open(infile, O_RDONLY);
	*fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd_in < 0)
	{
		ft_putstr_fd("\033[1;31m", 2);
		ft_putstr_fd("ERROR: opening infile", 2);
		ft_putstr_fd("\033[0m\n", 2);
	}
	if (*fd_out < 0)
	{
		ft_putstr_fd("\033[1;31m", 2);
		ft_putstr_fd("ERROR: opening outfile", 2);
		ft_putstr_fd("\033[0m\n", 2);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	int		pipe_status;

	if (argc == 5)
	{
		pipex.env = env;
		init_fds(&pipex.fd_in, &pipex.fd_out, argv[1], argv[4]);
		pipex.cmd1 = ft_split(argv[2], ' ');
		if (!pipex.cmd1)
			print_errors("ERROR: parsing command 1", NULL, NULL);
		pipex.cmd2 = ft_split(argv[3], ' ');
		if (!pipex.cmd2)
			print_errors("ERROR: parsing command 2", pipex.cmd1, NULL);
		pipe_status = pipe(pipex.pipefd);
		if (pipe_status == -1)
			print_errors("ERROR: creating pipe", pipex.cmd1, pipex.cmd2);
		child_process_1(&pipex);
		child_process_2(&pipex);
		cleanup(&pipex);
	}
	else
		fail_args();
}
