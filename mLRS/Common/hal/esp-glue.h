//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
//*******************************************************
// ESP Glue
//*******************************************************
#ifndef ESP_GLUE_H
#define ESP_GLUE_H
#pragma once


#include <Arduino.h>

#define __NOP() _NOP()


#undef IRQHANDLER
#define IRQHANDLER(__Declaration__)  extern "C" {IRAM_ATTR __Declaration__}


void __disable_irq(void) {}
void __enable_irq(void) {}


typedef enum {
    DISABLE = 0,
    ENABLE = !DISABLE
} FunctionalState;


#define __REV16(x)  __builtin_bswap16(x)
#define __REVSH(x)  __builtin_bswap16(x)
#define __REV(x)    __builtin_bswap32(x)


// setup(), loop() streamlining between Arduino/STM code
static uint8_t restart_controller = 0;
void setup() {}
void main_loop(void);
void loop() { main_loop(); }

#define INITCONTROLLER_ONCE \
    if(restart_controller <= 1){ \
    if(restart_controller == 0){
#define RESTARTCONTROLLER \
    }
#define INITCONTROLLER_END \
    restart_controller = UINT8_MAX; \
    }
#define GOTO_RESTARTCONTROLLER \
    restart_controller = 1; \
    return;


#endif // ESP_GLUE_H

