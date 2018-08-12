/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:38:46 by amalkevy          #+#    #+#             */
/*   Updated: 2017/11/09 18:09:17 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countwords(char const *s, char c)
{
	int		i;
	int		m;

	m = 0;
	i = 0;
	while (*s)
	{
		m = 1;
		while (*s == c && *s)
			s++;
		while (*s != c && *s != '\0')
		{
			if (m)
			{
				i++;
				m = 0;
			}
			s++;
		}
	}
	return (i);
}

static int		ft_wordlen(char const *s, char c)
{
	int		i;

	i = 0;
	while (*s != c && *s)
	{
		s++;
		i++;
	}
	return (i);
}

static int		ft_meccpy(char *dst, char const *src, int c)
{
	int			i;

	i = 0;
	while (src[i] != (unsigned char)c && src[i])
	{
		*dst = src[i];
		dst++;
		i++;
	}
	*dst = '\0';
	return (i);
}

static	void	ft_free(char ***s, int i)
{
	while (--i)
	{
		ft_strdel(&(*s[i]));
	}
	free(*s);
	*s = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char		**new_masiv;
	int			words;
	int			i;
	int			j;

	if (!s)
		return (0);
	i = -1;
	j = 0;
	words = ft_countwords(s, c);
	if ((new_masiv = (char**)malloc(sizeof(char*) * (words + 1))) == NULL)
		return (0);
	while (++i < words && s[j])
	{
		while (s[j] == c)
			j++;
		if ((new_masiv[i] = (char*)malloc(ft_wordlen(&s[j], c) + 1)) == NULL)
		{
			ft_free(&new_masiv, i);
			return (0);
		}
		j += ft_meccpy(new_masiv[i], &s[j], c);
	}
	new_masiv[i] = NULL;
	return (new_masiv);
}
