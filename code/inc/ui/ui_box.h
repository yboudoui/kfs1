#ifndef UI_BOX_H
#define UI_BOX_H

#include "vectors.h"
#include "vga.h"
/*
typedef enum {
    SIMPLE,
    DOUBLE,
} t_kind;

typedef enum {
    VERTICAL,
    HORIZONTAL,
    CORNER,
    CROSS,
    T,
} t_orientation;

typedef enum {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    DOWN,
    UP,
} t_position;



typedef enum {
    // Mixed T-shapes (Transitions)
    T_DOWN_SINGLE_TOP_DOUBLE = 0xCA,    // ╨
    T_UP_SINGLE_BOTTOM_DOUBLE = 0xCB,   // ╥
    T_LEFT_SINGLE_RIGHT_DOUBLE = 0xCC,  // ╞
    T_RIGHT_SINGLE_LEFT_DOUBLE = 0xB5,  // ╡

    // Transition corners
    CORNER_TOP_LEFT_SINGLE_BOTTOM_DOUBLE = 0xD5,    // ╓
    CORNER_TOP_RIGHT_SINGLE_BOTTOM_DOUBLE = 0xD6,   // ╒
    CORNER_BOTTOM_LEFT_SINGLE_TOP_DOUBLE = 0xD4,    // ╘
    CORNER_BOTTOM_RIGHT_SINGLE_TOP_DOUBLE = 0xD3,   // ╙
    CORNER_TOP_RIGHT_DOUBLE_BOTTOM_SINGLE = 0xB6,   // ╖
    CORNER_TOP_LEFT_DOUBLE_BOTTOM_SINGLE = 0xB7,    // ╕

    // Crosses with mixed lines
    CROSS_VERTICAL_DOUBLE_HORIZONTAL_SINGLE = 0xC6, // ╢
    CROSS_VERTICAL_SINGLE_HORIZONTAL_DOUBLE = 0xB5, // ╟

    // Horizontal transitions
    HORIZONTAL_SINGLE_VERTICAL_DOUBLE_LEFT = 0xCA,  // ╥
    HORIZONTAL_SINGLE_VERTICAL_DOUBLE_RIGHT = 0xCB, // ╧

    // Vertical transitions
    VERTICAL_SINGLE_HORIZONTAL_DOUBLE_TOP = 0xC6,   // ╤
    VERTICAL_SINGLE_HORIZONTAL_DOUBLE_BOTTOM = 0xB5 // ╧
} LineBlockCP437;

static int t[] = {
    [VERTICAL | SIMPLE] = 0xB3,                     // │  
    [VERTICAL | DOUBLE] = 0xBA,                     // ║

    [HORIZONTAL | SIMPLE] = 0xC4,                   // ─          
    [HORIZONTAL | DOUBLE] = 0xCD,                   // ═

    [CORNER | TOP | LEFT | SIMPLE] = 0xDA,     
    [CORNER | TOP | RIGHT | SIMPLE] = 0xBF,    
    [CORNER | BOTTOM | LEFT | SIMPLE] = 0xC0,  
    [CORNER | BOTTOM | RIGHT | SIMPLE] = 0xD9, 

    [CORNER | TOP | LEFT | DOUBLE] = 0xC9,     
    [CORNER | TOP | RIGHT | DOUBLE] = 0xBB,    
    [CORNER | BOTTOM | LEFT | DOUBLE] = 0xC8,  
    [CORNER | BOTTOM | RIGHT | DOUBLE] = 0xBC,

    [CROSS | SIMPLE] = 0xC5,               
    [CROSS | DOUBLE] = 0xCE,

    // Simple T-shapes
    [T | DOWN | SIMPLE] = 0xC1,                     // ┴              
    [T | UP | SIMPLE] = 0xC2,                       // ┬                
    [T | LEFT | SIMPLE] = 0xC3,                     // ├              
    [T | RIGHT | SIMPLE] = 0xB4,                    // ┤

    // Double T-shapes
    [T | DOWN | DOUBLE] = 0xCF,                     // ╩ 
    [T | UP | DOUBLE] = 0xCB,                       // ╦ 
    [T | LEFT | DOUBLE] = 0xCC,                     // ╠ 
    [T | RIGHT | DOUBLE] = 0xB9,                    // ╣

    [T_DOWN_SINGLE_TOP_DOUBLE] = 0xCA,   
    [T_UP_SINGLE_BOTTOM_DOUBLE] = 0xCB,  
    [T_LEFT_SINGLE_RIGHT_DOUBLE] = 0xCC, 
    [T_RIGHT_SINGLE_LEFT_DOUBLE] = 0xB5, 

    [CORNER_TOP_LEFT_SINGLE_BOTTOM_DOUBLE] = 0xD5,   
    [CORNER_TOP_RIGHT_SINGLE_BOTTOM_DOUBLE] = 0xD6,  
    [CORNER_BOTTOM_LEFT_SINGLE_TOP_DOUBLE] = 0xD4,   
    [CORNER_BOTTOM_RIGHT_SINGLE_TOP_DOUBLE] = 0xD3,  
    [CORNER_TOP_RIGHT_DOUBLE_BOTTOM_SINGLE] = 0xB6,  
    [CORNER_TOP_LEFT_DOUBLE_BOTTOM_SINGLE] = 0xB7,   
    [CROSS_VERTICAL_DOUBLE_HORIZONTAL_SINGLE] = 0xC6,
    [CROSS_VERTICAL_SINGLE_HORIZONTAL_DOUBLE] = 0xB5,
    [HORIZONTAL_SINGLE_VERTICAL_DOUBLE_LEFT] = 0xCA, 
    [HORIZONTAL_SINGLE_VERTICAL_DOUBLE_RIGHT] = 0xCB,
    [VERTICAL_SINGLE_HORIZONTAL_DOUBLE_TOP] = 0xC6,  
    [VERTICAL_SINGLE_HORIZONTAL_DOUBLE_BOTTOM] = 0xB5
};


typedef enum {
    // Vertical lines
    VERTICAL_SIMPLE = 0xB3,             // │
    VERTICAL_DOUBLE = 0xBA,             // ║

    // Horizontal lines
    HORIZONTAL_SIMPLE = 0xC4,           // ─
    HORIZONTAL_DOUBLE = 0xCD,           // ═

    // Simple corners
    CORNER_TOP_LEFT_SIMPLE = 0xDA,      // ┌
    CORNER_TOP_RIGHT_SIMPLE = 0xBF,     // ┐
    CORNER_BOTTOM_LEFT_SIMPLE = 0xC0,   // └
    CORNER_BOTTOM_RIGHT_SIMPLE = 0xD9,  // ┘

    // Double corners
    CORNER_TOP_LEFT_DOUBLE = 0xC9,      // ╔
    CORNER_TOP_RIGHT_DOUBLE = 0xBB,     // ╗
    CORNER_BOTTOM_LEFT_DOUBLE = 0xC8,   // ╚
    CORNER_BOTTOM_RIGHT_DOUBLE = 0xBC,  // ╝

    // Horizontal and vertical crosses
    CROSS_SIMPLE = 0xC5,                // ┼
    CROSS_DOUBLE = 0xCE,                // ╬

    // Simple T-shapes
    T_DOWN_SIMPLE = 0xC1,               // ┴
    T_UP_SIMPLE = 0xC2,                 // ┬
    T_LEFT_SIMPLE = 0xC3,               // ├
    T_RIGHT_SIMPLE = 0xB4,              // ┤

    // Double T-shapes
    T_DOWN_DOUBLE = 0xCF,               // ╩
    T_UP_DOUBLE = 0xCB,                 // ╦
    T_LEFT_DOUBLE = 0xCC,               // ╠
    T_RIGHT_DOUBLE = 0xB9,              // ╣

    // Mixed T-shapes (Transitions)
    T_DOWN_SINGLE_TOP_DOUBLE = 0xCA,    // ╨
    T_UP_SINGLE_BOTTOM_DOUBLE = 0xCB,   // ╥
    T_LEFT_SINGLE_RIGHT_DOUBLE = 0xCC,  // ╞
    T_RIGHT_SINGLE_LEFT_DOUBLE = 0xB5,  // ╡

    // Transition corners
    CORNER_TOP_LEFT_SINGLE_BOTTOM_DOUBLE = 0xD5,    // ╓
    CORNER_TOP_RIGHT_SINGLE_BOTTOM_DOUBLE = 0xD6,   // ╒
    CORNER_BOTTOM_LEFT_SINGLE_TOP_DOUBLE = 0xD4,    // ╘
    CORNER_BOTTOM_RIGHT_SINGLE_TOP_DOUBLE = 0xD3,   // ╙
    CORNER_TOP_RIGHT_DOUBLE_BOTTOM_SINGLE = 0xB6,   // ╖
    CORNER_TOP_LEFT_DOUBLE_BOTTOM_SINGLE = 0xB7,    // ╕

    // Crosses with mixed lines
    CROSS_VERTICAL_DOUBLE_HORIZONTAL_SINGLE = 0xC6, // ╢
    CROSS_VERTICAL_SINGLE_HORIZONTAL_DOUBLE = 0xB5, // ╟

    // Horizontal transitions
    HORIZONTAL_SINGLE_VERTICAL_DOUBLE_LEFT = 0xCA,  // ╥
    HORIZONTAL_SINGLE_VERTICAL_DOUBLE_RIGHT = 0xCB, // ╧

    // Vertical transitions
    VERTICAL_SINGLE_HORIZONTAL_DOUBLE_TOP = 0xC6,   // ╤
    VERTICAL_SINGLE_HORIZONTAL_DOUBLE_BOTTOM = 0xB5 // ╧
} LineBlockCP437;

*/

typedef struct {
    t_vec2      position;
    t_vec2      outer_size;
    t_vec2      inner_size;
} t_ui_box;

void print_ui_box(t_ui_box ui_box);

#endif