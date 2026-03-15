/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrelli <melchior.grellier42@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 02:06:45 by megrelli          #+#    #+#             */
/*   Updated: 2026/03/13 18:35:14 by megrelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	wait_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	int		infile;
	int		outfile;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		error_exit("Invalid format: ./pipex infile cmd1 cmd2 outfile");
	open_files(&infile, &outfile, av);
	if (pipe(pipefd) == -1)
		error_exit("pipe");
	pid1 = fork();
	if (pid1 == -1)
		error_exit("fork");
	if (pid1 == 0)
		first_child(infile, pipefd, av[2], envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("fork");
	if (pid2 == 0)
		second_child(outfile, pipefd, av[3], envp);
	close_all_fds(infile, outfile, pipefd);
	waitpid(pid1, NULL, 0);
	return (wait_status(pid2));
}
