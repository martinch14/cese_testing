/**************************************************************************************************
 ** (c) Copyright 2019: Martin Abel Gambarotta <magambarotta@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/
/** @file 	payload_spi.h
 ** @brief 	Proceso SerialService
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2019.08.23 | magambarotta    | Version inicial 									      |
 ** @addtogroup aplicacion
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */
#include <stdint.h>
#include "spi.h"

/* === Definicion y Macros ===================================================================== */
#define TAMANIO_DATAGRAMA 5

typedef enum { OPERACION_LECTURA = 0x00, OPERACION_ESCRITURA = 0x80 } trinamicOperacion_t;
//typedef enum {TMC4671_PID_FLUX_P_FLUX_I,TMC4671_PID_TORQUE_P_TORQUE_I,TMC4671_PID_VELOCITY_P_VELOCITY_I,TMC4671_PID_POSITION_P_POSITION_I}trinamicRegistro_t;
typedef enum {DATAGRAMA_CORRECTO, DATAGRAMA_INCORRECTO}validacion_t;


validacion_t setearRegistro(uint8_t operacion,uint8_t registro, uint32_t valor, spiEnviarHandler_t enviar);
validacion_t leerRegistro(uint8_t registro,spiRecibirHandler_t recibir);


/** @} Final de la definición del modulo para doxygen */
