/**************************************************************************************************
 ** (c) Copyright 2019: Martin Abel Gambarotta <magambarotta@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/
/** @file 	payload_spi.c
 ** @brief 	Proceso SerialService
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2019.08.23 | magambarotta    | Version inicial 									      |
 ** @addtogroup aplicacion
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */
#include "payload_spi.h"
#include "TMC4671_Register.h"

static handler_t RegistrarError;

void datagramaCrear(datagrama_t*  datagrama,handler_t error){
    datagrama->operacion=0x00;
    datagrama->registro=0x00;
    datagrama->valor=0x00000000;
    RegistrarError=error;

}

void datagramaCargar(uint8_t registro , uint32_t valor , datagrama_t*  datagrama){
    /*0x7D Maximo numero de registro posible*/
    if (registro > 0x7D ){
        RegistrarError(WARNING, __FILE__, __FUNCTION__,__LINE__, "Valor de registro ingresado invalido" );
    }
    datagrama->registro= registro;
    datagrama->valor =  valor;
}

uint8_t*  datagramaEnviar (datagrama_t*  datagrama, operacion_t operacion){
    if (operacion == OPERACION_ESCRITURA){
        data[0]= datagrama->registro + OPERACION_ESCRITURA;
        data[1]=(uint8_t)((datagrama->valor & 0xFF000000) >> 24);
        data[2]=(uint8_t)((datagrama->valor & 0x00FF0000) >> 16);
        data[3]=(uint8_t)((datagrama->valor & 0x0000FF00) >> 8);
        data[4]=(uint8_t)((datagrama->valor & 0x000000FF));
        return  data;
    }
    else if (operacion == OPERACION_LECTURA) {
        data[0]= datagrama->registro + OPERACION_LECTURA;
        data[1]=(uint8_t)((datagrama->valor & 0xFF000000) >> 24);
        data[2]=(uint8_t)((datagrama->valor & 0x00FF0000) >> 16);
        data[3]=(uint8_t)((datagrama->valor & 0x0000FF00) >> 8);
        data[4]=(uint8_t)((datagrama->valor & 0x000000FF));
        return  data;
    }
}

void datagramaRecibir ( uint8_t * dato_recibido,datagrama_t*  datagrama){

    datagrama->registro=dato_recibido[0];
    datagrama->valor=(uint32_t)(dato_recibido[1] << 24) + (dato_recibido[2] << 16) + (dato_recibido[3] << 8) + (dato_recibido[4]);

}

/** @} Final de la definición del modulo para doxygen */
