/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play_sound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlevko <vlevko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 18:31:42 by vlevko            #+#    #+#             */
/*   Updated: 2018/09/24 00:53:27 by vlevko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_visual.h"

Uint32		g_len;
Uint8		*g_buf;

static int	ft_init_sdl(char *src, SDL_AudioSpec *spec, Uint32 *len, \
	Uint8 **buf)
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		return (1);
	if (SDL_LoadWAV(src, spec, buf, len) == NULL)
	{
		SDL_Quit();
		return (1);
	}
	return (0);
}

static void	ft_play_callback(void *udata, Uint8 *stream, int len)
{
	Uint32	tmp;

	tmp = len;
	if (g_len == 0)
		return ;
	else if (tmp > g_len)
		len = g_len;
	if (udata)
		udata = NULL;
	SDL_memset(stream, 0, len);
	SDL_memcpy(stream, g_buf, len);
	SDL_MixAudio(stream, g_buf, len, SDL_MIX_MAXVOLUME / 2);
	g_len -= len;
	g_buf += len;
}

void		ft_play_sound(char *src)
{
	SDL_AudioSpec	spec;
	Uint32			len;
	Uint8			*buf;

	if (ft_init_sdl(src, &spec, &len, &buf))
		return ;
	spec.callback = ft_play_callback;
	spec.userdata = NULL;
	if (SDL_OpenAudio(&spec, NULL) < 0)
		return ;
	g_len = len;
	g_buf = buf;
	SDL_PauseAudio(0);
	while (g_len > 0)
		SDL_Delay(500);
	SDL_CloseAudio();
	SDL_FreeWAV(buf);
	SDL_Quit();
}
