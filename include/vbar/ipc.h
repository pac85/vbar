#ifndef __VBAR_IPC_H__
#define __VBAR_IPC_H__

#include <vbar/type.h>
#include <sys/sysinfo.h>

#define ATTRIBUTE_ICONS_SIZE 8
#define ATTRIBUTE_FORMAT_MAX 6
#define ATTRIBUTE_SPAWN_MAX 1024
#define ATTRIBUTE_TEXT_MAX 126

#ifndef IPC_CALLBACK_MAX 
	#define IPC_CALLBACK_MAX 32
#endif

typedef void(*ipcCallBack_f)(void*);

typedef enum {ALIGN_CENTER, ALIGN_RIGHT, ALIGN_LEFT} align_e;
typedef enum {BLINK_DISABLE, BLINK_URGENT, BLINK_BACKGROUND, BLINK_FOREGROUND} blink_e;

typedef struct attribute{
	char longformat[ATTRIBUTE_TEXT_MAX];
	char shortformat[ATTRIBUTE_TEXT_MAX]; //is unused can remove
	char longunformat[ATTRIBUTE_TEXT_MAX];
	char shortunformat[ATTRIBUTE_TEXT_MAX];
	char scrollformat[ATTRIBUTE_TEXT_MAX];
	int useshort;
		
	int color;
	int border;
	int background;
	int min_width;

	align_e align;
	
	char name[ATTRIBUTE_TEXT_MAX];
	char instance[ATTRIBUTE_TEXT_MAX];

	int urgent;
	int separator;
	int separator_block_width;
	int markup;

	long blinktime;
	blink_e blink;
	int blinkstatus;
	int blinkcolor;
	int blinktoggle;
	int blinkold;

	char* scrollch;
	int scrollsize;
	long scrolltime;

	long reftime;
	long tick;
	long doubletick;
	
	char** icons;
	size_t iconcount;
	size_t icoindex;
	
	char** format;
	size_t formatcount;
	
	char onevent[ATTRIBUTE_SPAWN_MAX];
	int hide;
}attribute_s;


#define IPC_TIMEOUT 0x01
#define IPC_EVENT   0x02

typedef struct event{
	char name[ATTRIBUTE_TEXT_MAX];
	char instance[ATTRIBUTE_TEXT_MAX];
	int x;
	int y;
	int button;
	int relative_x;
	int relative_y;
	int width;
	int height;
}event_s;

int ipc_register_callback(int fd, ipcCallBack_f cbk, void* arg);
int ipc_register_inotify(char* fname, int flags, ipcCallBack_f cbk, void* arg);
void ipc_init(bool_t clickevents);
void ipc_custom_init(bool_t clickevents);
void ipc_write_element(attribute_s* el, bool_t next);
void ipc_event_reset(event_s* ev);
int ipc_wait(event_s* ev, long timeend);
int ipc_onstdin(event_s* ev);
void ipc_begin_elements();
void ipc_end_elements();

void ipc_reg_swap(size_t nra, size_t nrb);
void ipc_reg_store(size_t nr, char* val, size_t lenV);
char* ipc_reg_load(size_t nr);
void ipc_set_attribute_byname(attribute_s* att, char* name, char* value);
void ipc_set_attribute_byreg(attribute_s* att, char* name, size_t reg);
void ipc_reg_store_attribute_byname(attribute_s* att, char* name, size_t reg);
void ipc_toggle_attribute_byname(attribute_s* att, char* name);
void ipc_set_blink_mode(attribute_s* att);
void ipc_store_blink_mode(attribute_s* att);
void ipc_set_scroll(attribute_s* att);

#endif
