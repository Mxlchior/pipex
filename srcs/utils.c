/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrelli <melchior.grellier42@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 03:47:31 by megrelli          #+#    #+#             */
/*   Updated: 2026/03/12 00:41:39 by megrelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	cmd_not_found(char *cmd, char **cmd_args)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	free_tab(cmd_args);
	exit(127);
}

void	error_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	open_files(int *infile, int *outfile, char **av)
{
	*infile = open(av[1], O_RDONLY);
	if (*infile == -1)
		perror(av[1]);
	*outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
		perror(av[4]);
}

void	close_all_fds(int infile, int outfile, int *pipefd)
{
	if (infile != -1)
		close(infile);
	if (outfile != -1)
		close(outfile);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
