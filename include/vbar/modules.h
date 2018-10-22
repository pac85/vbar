#ifndef __VBAR_MODULES_H__
#define __VBAR_MODULES_H__

#include <vbar/type.h>
#include <vbar/memory.h>
#include <vbar/string.h>
#include <vbar/delay.h>
#include <vbar/config.h>
#include <vbar/ipc.h>
#include <vbar/spawn.h>
#include <vbar/file.h>
#include <sys/sysinfo.h>

#include <hash_mods.h>

/*** modules.c ***/
#ifndef MODULES_MAX
	#define MODULES_MAX 32
#endif

typedef struct module module_s;

typedef int (*modself_f)(module_s*);
typedef int (*modselfds_f)(module_s*,int,char*);

typedef struct modules modules_s;

typedef struct module{
	modules_s* parent;
	struct module* next;
	struct module* hnext;
	attribute_s att;
	void* data;
	modself_f refresh;
	modself_f free;
	modselfds_f getenv;
}module_s;

typedef struct modules{
	void* generic;
	module_s* rmod;
	size_t used;
	module_s* mod[MODULES_MAX];
	size_t count;
	module_s* hmod[HMODS_MAX_HASH_VALUE + 1];
	attribute_s def;
}modules_s;

int file_exists(char* fname);

void module_time_set(module_s* mod);
module_s* modules_pop(modules_s* mods);
void modules_insert(modules_s* mods, module_s* mod);
void modules_refresh_tick(modules_s* mods, long ellapsems);
void modules_load(modules_s* mod, char* config);
long modules_next_tick(modules_s* mods);
void modules_reformatting(module_s* mod);
void modules_refresh_output(modules_s* mods);
void modules_default_config(module_s* mod, config_s* conf);
void modules_icons_init(module_s* mod, size_t count);
void modules_icons_set(module_s* mod, size_t id, char* ico);
void modules_icons_select(module_s* mod, size_t id);
void modules_dispatch(modules_s* mods, event_s* ev);
void module_set_urgent(module_s* mod, int enable);
void modules_format_init(module_s* mod, size_t count);
void modules_format_set(module_s* mod, size_t id, char* format);
char* modules_format_get(module_s* mod, size_t id, char* type);
void module_scroll_init(module_s* mod);

size_t os_read_lu(char* fname);

#endif
