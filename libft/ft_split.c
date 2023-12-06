/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:25:48 by damachad          #+#    #+#             */
/*   Updated: 2023/11/23 10:29:54 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_word(const char *str, char c)
{
	int	n_letters;

	n_letters = 0;
	while (str[n_letters] != '\0' && str[n_letters] != c)
	{
		n_letters++;
	}
	return (n_letters);
}

static int	count_words(const char *s, char delim)
{
	int		n;
	int		i;
	size_t	len;

	n = 0;
	i = 0;
	len = ft_strlen(s);
	if (len == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == delim && s[i + 1] != delim)
			n++;
		i++;
	}
	if (s[0] == delim)
		n--;
	if (s[len - 1] != delim)
		n++;
	return (n);
}

static char	*word_cpy(const char *s, char c)
{
	int		i;
	int		l;
	char	*ptr;

	i = 0;
	l = 0;
	while (s[l] != '\0' && s[l] != c)
	{
		l++;
	}
	ptr = (char *)malloc((l + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (i < l)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	words = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!words)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			words[j++] = word_cpy(s + i, c);
			i += skip_word(s + i, c);
		}
	}
	words[j] = 0;
	return (words);
}
