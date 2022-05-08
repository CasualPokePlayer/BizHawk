#include "cdd_fader.h"
#include <stdio.h>

void cdd_fader_init(cdd_fader *fader)
{
	fader->audio = render_audio_source("CDDA", 16934400, 384, 2);
	fader->cur_attenuation = 0x4000;
	fader->dst_attenuation = 0x4000;
	fader->attenuation_step = 0;
}
void cdd_fader_attenuation_write(cdd_fader *fader, uint16_t attenuation)
{
	fader->dst_attenuation = attenuation & 0xFFF0;
	fader->flags = attenuation & 0xE;
	if (fader->dst_attenuation > fader->cur_attenuation) {
		fader->attenuation_step = (fader->dst_attenuation - fader->cur_attenuation) >> 4;
	} else if (fader->dst_attenuation < fader->cur_attenuation) {
		fader->attenuation_step = (fader->cur_attenuation - fader->dst_attenuation) >> 4;
	} else {
		fader->attenuation_step = 0;
	}
}

void cdd_fader_data(cdd_fader *fader, uint8_t byte)
{
	fader->bytes[fader->byte_counter++] = byte;
	if (fader->byte_counter == sizeof(fader->bytes)) {
		fader->byte_counter = 0;
		int32_t left = (fader->bytes[1] << 8) | fader->bytes[0];
		int32_t right = (fader->bytes[3] << 8) | fader->bytes[2];
		if (left & 0x8000) {
			left |= 0xFFFF0000;
		}
		if (right & 0x8000) {
			right |= 0xFFFF0000;
		}
		if (!fader->cur_attenuation) {
			left = right = 0;
		} else if (fader->cur_attenuation >= 4) {
			left *= fader->cur_attenuation & 0x7FF0;
			right *= fader->cur_attenuation & 0x7FF0;
			left >>= 14;
			right >>= 14;
		} else {
			//TODO: FIXME
			left = right = 0;
		}
		render_put_stereo_sample(fader->audio, left, right);
		if (fader->attenuation_step) {
			if (fader->dst_attenuation > fader->cur_attenuation) {
				fader->cur_attenuation += fader->attenuation_step;
				if (fader->cur_attenuation >= fader->dst_attenuation) {
					fader->cur_attenuation = fader->dst_attenuation;
					fader->attenuation_step = 0;
				}
			} else {
				fader->cur_attenuation -= fader->attenuation_step;
				if (fader->cur_attenuation <= fader->dst_attenuation) {
					fader->cur_attenuation = fader->dst_attenuation;
					fader->attenuation_step = 0;
				}
			}
		}
	}
}
