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


static spiEnviarHandler_t enviarDatagrama;
static spiRecibirHandler_t recibirDatagrama;


validacion_t setearRegistro(uint8_t operacion,uint8_t registro, uint32_t valor, spiEnviarHandler_t enviar){

    uint8_t  data[5];
    validacion_t validacion;
    enviarDatagrama= enviar;

    /*chequeo datagrama*/
    if (operacion != OPERACION_ESCRITURA){
        validacion = DATAGRAMA_INCORRECTO;
        return validacion;
    }
    /* 0x7D es el ultimo registro sobre el que se puede operar*/
    else if (registro > 0x7D ){
        validacion = DATAGRAMA_INCORRECTO;
        return validacion;
    }
    else {
        validacion = DATAGRAMA_CORRECTO;
        /*armo datagrama*/
        data[0]= operacion + registro;
        data[1]=(uint8_t)((valor & 0xFF000000) >> 24);
        data[2]=(uint8_t)((valor & 0x00FF0000) >> 16);
        data[3]=(uint8_t)((valor & 0x0000FF00) >> 8);
        data[4]=(uint8_t)((valor & 0x000000FF));
        /*lo envio*/
         enviarDatagrama(data);
         return validacion;
     }
}


validacion_t leerRegistro(uint8_t registro,spiRecibirHandler_t recibir){
    validacion_t validacion;
    uint8_t  data[5] = { registro,0x00,0x00,0x0F,0xFF };
    recibirDatagrama= recibir;
    if(registro < 0x7D){
    recibirDatagrama(data);
    return validacion = DATAGRAMA_CORRECTO;
    }
}



//posibles registros {TMC4671_PID_FLUX_P_FLUX_I,TMC4671_PID_TORQUE_P_TORQUE_I,TMC4671_PID_VELOCITY_P_VELOCITY_I,TMC4671_PID_POSITION_P_POSITION_I}trinamicRegistro_t;
//Segun el registro recibido devuelve un valor que representa al registro


// uint8_t trinamicSetRegistro(trinamicRegistro_t registro){
//     switch (registro){
//         case TMC4671_PID_FLUX_P_FLUX_I:
//             return 0x54;
//     	case TMC4671_PID_TORQUE_P_TORQUE_I:
//             return 0x56;
//     	case TMC4671_PID_VELOCITY_P_VELOCITY_I:
//             return 0x58;
//     	case TMC4671_PID_POSITION_P_POSITION_I:
//             return 0x5A;
//         default:
//             return 0;
//     }
// }



//Devuelve un valor uint8_t que contiene el registro sobre el cual se quiere operar y el tipo de operacion a realizar
// La cantidad de registros sobre los que se pueden operar son 120, se usa del uint8_t solamente los primerios 7 bits
// La operacion de escritura queda definida con un 1 en el bits mas significativo.
// Por lo tanto en un byte se pueden representar todos los registros y el tipo de operacion a realizar

// uint8_t trinamicsetOperacionRegistroEscritura(trinamicOperacion_t operacion,trinamicRegistro_t registro){
//         return trinamicSetOperacion(operacion)  + trinamicSetRegistro(registro);
// }

//Esta funcion arma un datagrama de 40 bits con la operacion y el registro ya definido, y el valor que se le quiere setear
//Este datagrama luego sera enviado a traves del protocolo SPI

// void trinamicArmarDatagrama(uint8_t * datagrama, uint8_t operacionregistro, uint32_t valor ){
//
//     datagrama[0]= operacionregistro;
//     datagrama[1]=(uint8_t)((valor & 0xFF000000) >> 24);
//     datagrama[2]=(uint8_t)((valor & 0x00FF0000) >> 16);
//     datagrama[3]=(uint8_t)((valor & 0x0000FF00) >> 8);
//     datagrama[4]=(uint8_t)((valor & 0x000000FF));
// }




// void trinamicInformarRespuesta(uint8_t * datagrama){
//
//     uint8_t * datagramaRespuesta;
//     uint8_t operacion;
//     uint8_t registro;
//     uint32_t valor;
//
//     operacion = datagramaRespuesta[0];
//     operacion = operacion >> 7;
//     switch (operacion){
//         case 0:
//
//         case 1:
//     }
//
//
//
// }
/** @} Final de la definición del modulo para doxygen */
