/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:41:00 by jnivala           #+#    #+#             */
/*   Updated: 2021/01/21 15:46:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"


void	data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
	ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
	if (pDecoder == NULL) {
		return;
	}
	ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount);
	(void)pInput;
}

int		setup_music(const char *audio_file, t_home *home)
{
	ma_result result;
	ma_decoder decoder;
	ma_device_config device_config;
	ma_device device;

	result = ma_decoder_init_file(audio_file, NULL, &decoder);
	if (result != MA_SUCCESS)
		return -2;
	device_config = ma_device_config_init(ma_device_type_playback);
	device_config.playback.format   = decoder.outputFormat;
	device_config.playback.channels = decoder.outputChannels;
	device_config.sampleRate        = decoder.outputSampleRate;
	device_config.dataCallback      = data_callback;
	device_config.pUserData         = &decoder;
	if (init_audiodevice(&device, &decoder, &device_config, home))
		return (-1);
	if (device_start(&device, &decoder, home) < 0)
		return (-1);
	return (0);
}

int		init_audiodevice(ma_device *device, ma_decoder *decoder, ma_device_config *device_config, t_home *home)
{
	if (ma_device_init(NULL, device_config, device) != MA_SUCCESS) {
		error_output_sdl("Failed to open playback device.", home);
		ma_decoder_uninit(decoder);
		return (-3);
	}
	return (0);
}

int		device_start(ma_device *device, ma_decoder *decoder, t_home *home)
{
	if (ma_device_start(device) != MA_SUCCESS) {
		error_output_sdl("Failed to start playback device.", home);
		ma_device_uninit(device);
		ma_decoder_uninit(decoder);
		return (-4);
	}
	return (0);
}

int		unmount_audiodevice(ma_device *device, ma_decoder *decoder)
{
	ma_device_uninit(device);
	ma_decoder_uninit(decoder);
	return (0);
}
