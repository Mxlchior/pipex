/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrelli <melchior.grellier42@gmail.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 08:42:06 by megrelli          #+#    #+#             */
/*   Updated: 2026/03/12 04:49:06 by megrelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static int	countwords(const char *s, char c)
{
	int		words;
	char	quote;
	size_t	i;

	words = 0;
	i = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			words++;
		while ((s[i] != c || quote != 0) && s[i])
		{
			if ((s[i] == '\'' || s[i] == '"') && quote == 0)
					quote = s[i];
			else if (quote == s[i])
				quote = 0;
			i++;
		}
	}
	return (words);
}

static size_t	get_word_len(const char *s, char c)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (s[len] && (s[len] != c || quote != 0))
	{
		if ((s[len] == '\'' || s[len] == '"') && quote == 0)
			quote = s[len];
		else if (quote == s[len])
			quote = 0;
		len++;
	}
	return (len);
}

static int	fillwords(char **tab, const char *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		len = get_word_len(s, c);
		if (ft_safemalloc(tab, i, len) == 1)
			return (1);
		ft_strlcpy(tab[i], s, len + 1);
		s += len;
		i++;
	}
	return (0);
}

static void	clean_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

char	**split(const char *s, char c)
{
	char	**tab;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = countwords(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab[words] = NULL;
	if (fillwords(tab, s, c) == 1)
		return (NULL);
	i = 0;
	while (tab[i])
		clean_quotes(tab[i++]);
	return (tab);
}
