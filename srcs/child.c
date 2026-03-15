/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrelli <melchior.grellier42@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 01:52:42 by megrelli          #+#    #+#             */
/*   Updated: 2026/03/13 18:45:41 by megrelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	first_child(int infile, int *pipefd, char *cmd, char **envp)
{
	if (infile == -1)
		exit(1);
	close(pipefd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(infile);
	close(pipefd[1]);
	exec_cmd(cmd, envp);
}

void	second_child(int outfile, int *pipefd, char *cmd, char **envp)
{
	if (outfile == -1)
		exit(1);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[0]);
	close(outfile);
	exec_cmd(cmd, envp);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	cmd_args = split(cmd, ' ');
	if (!cmd_args)
		error_exit("Malloc failed\n");
	if (!cmd_args[0])
		cmd_not_found(cmd, cmd_args);
	if (ft_strchr(cmd_args[0], '/'))
		path = cmd_args[0];
	else
		path = get_cmd_path(cmd_args[0], envp);
	if (!path)
		cmd_not_found(cmd_args[0], cmd_args);
	execve(path, cmd_args, envp);
	perror(cmd_args[0]);
	if (path != cmd_args[0])
		free(path);
	free_tab(cmd_args);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else
		exit(1);
}
