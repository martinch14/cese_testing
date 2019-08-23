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

//Posibles operaciones { OPERACION_ESCRITURA, OPERACION_LECTURA} trinamicOperacion_t;
//Segun la operacion seleccionada, devuelve un valor uint8_t que es el que representa a la operacion

uint8_t trinamicSetOperacion(trinamicOperacion_t operacion){
    switch (operacion){
        case OPERACION_ESCRITURA:
            return 0x80;
        case OPERACION_LECTURA:
            return 0x00;
        default:
            break;
    }
}

//posibles registros {TMC4671_PID_FLUX_P_FLUX_I,TMC4671_PID_TORQUE_P_TORQUE_I,TMC4671_PID_VELOCITY_P_VELOCITY_I,TMC4671_PID_POSITION_P_POSITION_I}trinamicRegistro_t;
//Segun el registro recibido devuelve un valor que representa al registro

uint8_t trinamicSetRegistro(trinamicRegistro_t registro){
    switch (registro){
        case TMC4671_PID_FLUX_P_FLUX_I:
            return 0x54;
    	case TMC4671_PID_TORQUE_P_TORQUE_I:
            return 0x56;
    	case TMC4671_PID_VELOCITY_P_VELOCITY_I:
            return 0x58;
    	case TMC4671_PID_POSITION_P_POSITION_I:
            return 0x5A;
        default:
            return 0;
    }
}

//Devuelve un valor uint8_t que contiene el registro sobre el cual se quiere operar y el tipo de operacion a realizar
// La cantidad de registros sobre los que se pueden operar son 120, se usa del uint8_t solamente los primerios 7 bits
// La operacion de escritura queda definida con un 1 en el bits mas significativo.
// Por lo tanto en un byte se pueden representar todos los registros y el tipo de operacion a realizar

uint8_t trinamicsetOperacionRegistroEscritura(trinamicOperacion_t operacion,trinamicRegistro_t registro){
        return trinamicSetOperacion(operacion)  + trinamicSetRegistro(registro);
}

//Esta funciona arma un datagrama de 40 bits con la operacion y el registro ya definido, y el valor que se le quiere setear

void trinamicArmarDatagrama(uint8_t * datagrama, uint8_t operacionregistro, uint32_t valor ){

    datagrama[0]= operacionregistro;
    datagrama[1]=(uint8_t)((valor & 0xFF000000) >> 24);
    datagrama[2]=(uint8_t)((valor & 0x00FF0000) >> 16);
    datagrama[3]=(uint8_t)((valor & 0x0000FF00) >> 8);
    datagrama[4]=(uint8_t)((valor & 0x000000FF));
}

/** @} Final de la definición del modulo para doxygen */
