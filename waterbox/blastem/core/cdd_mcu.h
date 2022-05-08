#ifndef CDD_MCU_H_
#define CDD_MCU_H_
#include "system.h"
#include "lc8951.h"
#include "cdd_fader.h"

typedef enum {
	SF_ABSOLUTE,
	SF_RELATIVE,
	SF_TRACK,
	SF_TOCO,
	SF_TOCT,
	SF_TOCN,
	SF_E,
	SF_NOTREADY = 0xF
} status_format;

typedef enum {
	CMD_NOP,
	CMD_STOP,
	CMD_REPORT_REQUEST,
	CMD_READ,
	CMD_SEEK,
	CMD_INVALID,
	CMD_PAUSE,
	CMD_PLAY,
	CMD_FFWD,
	CMD_RWD,
	CMD_TRACK_SKIP,
	CMD_TRACK_CUE,
	CMD_DOOR_CLOSE,
	CMD_DOOR_OPEN
} host_cmd;

typedef enum {
	DS_STOP,
	DS_PLAY,
	DS_SEEK,
	DS_SCAN,
	DS_PAUSE,
	DS_DOOR_OPEN,
	DS_SUM_ERROR,
	DS_CMD_ERROR,
	DS_FUNC_ERROR,
	DS_TOC_READ,
	DS_TRACKING,
	DS_NO_DISC,
	DS_DISC_LEADOUT,
	DS_DISC_LEADIN,
	DS_TRAY_MOVING,
} drive_status;


typedef struct {
	uint8_t status;
	uint8_t format;
	union {
		struct {
			uint8_t min_high;
			uint8_t min_low;
			uint8_t sec_high;
			uint8_t sec_low;
			uint8_t frame_high;
			uint8_t frame_low;
			uint8_t flags;
		} time;
		struct {
			uint8_t track_high;
			uint8_t track_low;
			uint8_t padding0;
			uint8_t padding1;
			uint8_t control;
			uint8_t adr;
			uint8_t flags;
		} track;
		struct {
			uint8_t first_track_high;
			uint8_t first_track_low;
			uint8_t last_track_high;
			uint8_t last_track_low;
			uint8_t version;
			uint8_t padding;
			uint8_t flags;
		} toct;
		struct {
			uint8_t min_high;
			uint8_t min_low;
			uint8_t sec_high;
			uint8_t sec_low;
			uint8_t frame_high;
			uint8_t frame_low;
			uint8_t track_low;
		} tocn;
		struct {
		} error;
	} b;
	uint8_t checksum;
} cdd_status;

typedef struct {
	uint8_t cmd_type;
	uint8_t must_be_zero;
	union {
		struct {
			uint8_t min_high;
			uint8_t min_low;
			uint8_t sec_high;
			uint8_t sec_low;
			uint8_t frame_high;
			uint8_t frame_low;
		} time;
		struct {
			uint8_t padding;
			uint8_t status_type;
			uint8_t track_high;
			uint8_t track_low;
		} format;
		struct {
			uint8_t padding;
			uint8_t direction;
			uint8_t tracks_highest;
			uint8_t tracks_midhigh;
			uint8_t tracks_midlow;
			uint8_t tracks_lowest;
		} skip;
		struct {
			uint8_t track_high;
			uint8_t track_low;
		} track;
	} b;
	uint8_t padding;
	uint8_t checksum;
} cdd_cmd;

typedef struct {
	system_media  *media;
	uint32_t      cycle;          //this is in CD block CLKS
	uint32_t      next_int_cycle; //this is in SCD MCLKS
	uint32_t      next_subcode_int_cycle;
	uint32_t      last_sector_cycle;
	uint32_t      last_nibble_cycle;
	uint32_t      next_byte_cycle;
	uint32_t      next_subcode_cycle;
	int           current_status_nibble;
	int           current_cmd_nibble;
	int           current_sector_byte;
	int           current_subcode_byte;
	int           current_subcode_dest;
	uint32_t      head_pba;
	uint32_t      seek_pba;
	uint32_t      pause_pba;
	uint32_t      coarse_seek;
	cdd_status    status_buffer;
	cdd_cmd       cmd_buffer;
	status_format requested_format;
	drive_status  status;
	drive_status  error_status;
	uint8_t       requested_track;
	uint8_t       cmd_recv_wait;
	uint8_t       cmd_recv_pending;
	uint8_t       int_pending;
	uint8_t       subcode_int_pending;
	uint8_t       toc_valid;
	uint8_t       first_cmd_received;
	uint8_t       seeking;
	uint8_t       in_fake_pregap;
} cdd_mcu;

void cdd_mcu_init(cdd_mcu *context, system_media *media);
void cdd_mcu_run(cdd_mcu *context, uint32_t cycle, uint16_t *gate_array, lc8951 *cdc, cdd_fader *fader);
void cdd_hock_enabled(cdd_mcu *context);
void cdd_hock_disabled(cdd_mcu *context);
void cdd_mcu_start_cmd_recv(cdd_mcu *context, uint16_t *gate_array);
void cdd_mcu_adjust_cycle(cdd_mcu *context, uint32_t deduction);

#endif //CD_MCU_H_
