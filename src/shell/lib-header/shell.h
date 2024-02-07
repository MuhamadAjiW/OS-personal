

#ifndef _USER_SHELL
#define _USER_SHELL

#define INPUT_BUFFER_SIZE 1024

#define ROOT_CLUSTER_NUMBER 65

#include "window_manager.h"
#include "font.h"

//TODO: Document

//----Structs
typedef struct shell_reader {
    char* buffer_addr;
    uint32_t buffer_size;
    uint32_t max_idx;
    uint32_t current_idx;
} shell_reader;

typedef struct directory_info {
    char* path;
    uint32_t cluster_number;
}__attribute__((packed)) directory_info;

typedef struct text_grid{
    char* char_map;
    char* char_color_map;
    uint16_t xlen;
    uint16_t ylen;
} text_grid;

typedef struct shell_app
{    
    uint8_t default_font_color;
    uint8_t default_background_color;
    uint8_t default_cursor_color;
    
    uint16_t cursor_x;
    uint16_t cursor_x_limit;
    uint16_t cursor_y;
    uint16_t cursor_y_limit;
    uint8_t cursor_on;
    uint8_t cursor_show;
    uint8_t* cursor_background_buffer;
    uint16_t cursor_counter;
    uint8_t cursor_blocked_1;
    uint8_t cursor_blocked_2;

    
    window_info winfo;
    font_info finfo;
    shell_reader reader;
    directory_info dir;
    text_grid grid;

    // TODO: Switch to a better background structure
    uint8_t* background;

} shell_app;



//----App
void app_initialize();
void app_load_background();
void app_draw_background();

//----Grid
void grid_initialize();
void grid_write();

//----Cursor
void cursor_initialize();
void cursor_hide();
void cursor_show();
uint16_t cursor_get_y();
uint16_t cursor_get_x();
void cursor_on();
void cursor_off();
void cursor_limit(uint8_t x, uint8_t y);
void cursor_set(uint8_t x, uint8_t y);
uint16_t cursor_find_edge(uint16_t y);
int32_t cursor_move(int8_t direction);
void cursor_blinking();

//----Reader
void reader_initialize();
void reader_clear();
void reader_insert(char c);
void reader_move(int8_t direction);


//----Shell functionalities
void shell_clear();
void shell_backspace();
void shell_newline();
void shell_evaluate();

#endif