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
#include "error.h"

/* === Definicion y Macros ===================================================================== */
#define TAMANIO_DATAGRAMA 5

typedef enum { OPERACION_LECTURA = 0x00, OPERACION_ESCRITURA = 0x80 } operacion_t;
//typedef enum {DATAGRAMA_CORRECTO, DATAGRAMA_INCORRECTO}validacion_t;

typedef struct {
    operacion_t operacion;
    uint8_t registro;
    uint32_t valor;
}datagrama_t;
static datagrama_t datagrama;
static uint8_t data[TAMANIO_DATAGRAMA];


void datagramaCrear(datagrama_t * datagrama,handler_t error);
void datagramaCargar(uint8_t reg, uint32_t val, datagrama_t * datagrama);
uint8_t* datagramaEnviar (datagrama_t*  datagrama, operacion_t operacion);
void datagramaRecibir ( uint8_t * dato_recibido,datagrama_t*  datagrama);


/** @} Final de la definición del modulo para doxygen */
