/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrelli <melchior.grellier42@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:02:32 by megrelli          #+#    #+#             */
/*   Updated: 2026/03/13 18:49:56 by megrelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*get_env_path(char **envp)
{
	int	i;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*part;
	char	*full;
	int		i;

	paths = split(get_env_path(envp), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part = ft_strjoin(paths[i], "/");
		full = ft_strjoin(part, cmd);
		free(part);
		if (full && access(full, F_OK) == 0)
		{
			free_tab(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_tab(paths);
	return (NULL);
}
