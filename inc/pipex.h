/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrelli <melchior.grellier42@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 04:33:39 by megrelli          #+#    #+#             */
/*   Updated: 2026/03/13 16:08:51 by megrelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "../libft/libft.h"

/*UTILS*/
void	close_all_fds(int infile, int outfile, int *pipefd);
void	open_files(int *infile, int *outfile, char **av);
void	error_exit(char *msg);
void	cmd_not_found(char *cmd, char **cmd_args);
void	free_tab(char **tab);
char	**split(const char *s, char c);

/*CHILD*/
void	first_child(int infile, int *pipefd, char *cmd, char **envp);
void	second_child(int outfile, int *pipefd, char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);

/*PATH*/
char	*get_env_path(char **envp);
char	*get_cmd_path(char *cmd, char **envp);

#endif