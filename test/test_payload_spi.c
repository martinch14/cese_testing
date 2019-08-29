/**************************************************************************************************
 ** (c) Copyright 2019: Martin Abel Gambarotta <magambarotta@gmail.com>
 ** ALL RIGHTS RESERVED, DON'T USE OR PUBLISH THIS FILE WITHOUT AUTORIZATION
 *************************************************************************************************/
/** @file 	test_payload_spi.c
 ** @brief 	Proceso SerialService
 **
 **| REV | YYYY.MM.DD | Autor           | Descripción de los cambios                              |
 **|-----|------------|-----------------|---------------------------------------------------------|
 **|   1 | 2019.08.23 | magambarotta    | Version inicial 									      |
 ** @addtogroup aplicacion
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */
#include "unity.h"
#include "payload_spi.h"


static datagrama_t datagrama;


void test_datagramaCrear(void){

    datagramaCrear(&datagrama);
    TEST_ASSERT_EQUAL(0x00,datagrama.operacion);
    TEST_ASSERT_EQUAL(0x00,datagrama.registro);
    TEST_ASSERT_EQUAL(0x00,datagrama.valor);

}

void test_datagramaCargar(void){
    uint8_t reg=0xED;
    uint32_t val=0x0000FF00;

    datagramaCargar(reg,val,&datagrama);
    TEST_ASSERT_EQUAL(0xED,datagrama.registro);
    TEST_ASSERT_EQUAL(0x0000FF00,datagrama.valor);

}

void test_datagramaEnviar(void){

    uint8_t reg=0x40;
    uint32_t val=0x0000FFFF;
    uint8_t *datos;

    datagramaCargar(reg,val,&datagrama);
    datos = datagramaEnviar(&datagrama);

    TEST_ASSERT_EQUAL(0x40,datos[0]);
    TEST_ASSERT_EQUAL(0x0000FFFF, (datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]));

}

void test_datagramaRecibir(void){
    uint8_t datorecibido[5]={0x21,0x21,0x21,0x11,0x21};

    datagramaRecibir(datorecibido,&datagrama);

    TEST_ASSERT_EQUAL(0x21,datagrama.registro);
    TEST_ASSERT_EQUAL(0x21211121,datagrama.valor);
}



void test_datagramaFlujo(void){

    uint8_t reg=0x56;
    uint32_t val=0x00EEFFFF;
    uint8_t *datos;

    datagramaCargar(reg,val,&datagrama);
    datos = datagramaEnviar(&datagrama);
    datagramaRecibir(datos,&datagrama);

    TEST_ASSERT_EQUAL(0x56,datos[0]);
    TEST_ASSERT_EQUAL(0x00EEFFFF, (datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]));
}






















// datagrama_t datagrama_recibido;
// // {
// //         .operacion= OPERACION_LECTURA;
// //         .registro= 0x40;
// //         .valor= 0x0000FF0F;
// // };
//
//
// /*Funciones callback para simular el envio y recepcion del datagrama */
// void enviarDatagrama(uint8_t * data){
//     datagrama.operacion = data[0] & 0x80;
//     datagrama.registro= data[0] & 0x7F;
//     datagrama.valor= (data[1] << 24) + (data[2] << 16) + (data[3] << 8) + (data[4]);
// }
//
// void leerDatagrama(uint8_t * data){
//    datagrama_recibido.operacion = data[0] & 0x80;
//    datagrama_recibido.registro= data[0] & 0x7F;
//    datagrama_recibido.valor= (data[1] << 24) + (data[2] << 16) + (data[3] << 8) + (data[4]);
// }


// /*test para validar los datos que voy a transmitir*/
// void test_validacion_escritura(void){
//     validacion_t validacion;
//     uint8_t operacion = OPERACION_ESCRITURA;
//     uint8_t registro  = 0x58;
//     uint32_t valor    = 0x000000FF;
//
//     validacion = setearRegistro(operacion,registro,valor,enviarDatagrama);
//     TEST_ASSERT_EQUAL(0x00,validacion);
//
// }
// /*test para verificar que los datos se enviaron correctamente*/
// void test_setRegistro(void){
//
//     validacion_t validacion;
//     uint8_t operacion = OPERACION_ESCRITURA;
//     uint8_t registro  = 0x60;
//     uint32_t valor    = 0x00FF00FF;
//
//     validacion = setearRegistro(operacion,registro,valor,enviarDatagrama);
//     if ( validacion == DATAGRAMA_CORRECTO){
//         TEST_ASSERT_EQUAL(0x80,datagrama.operacion);
//         TEST_ASSERT_EQUAL(0x60,datagrama.registro);
//         TEST_ASSERT_EQUAL(0x00FF00FF,datagrama.valor);
//     }
// }
//
// void test_transmitirDatagramaRegistroInvalido(){
//
//     validacion_t validacion;
//     uint8_t operacion = OPERACION_ESCRITURA;
//     uint8_t registro  = 0xFF;
//     uint32_t valor    = 0x000000FF;
//
//     validacion = setearRegistro(operacion,registro,valor,enviarDatagrama);
//     TEST_ASSERT_EQUAL(DATAGRAMA_INCORRECTO,validacion);
//
// }
//
// void test_validacion_lectura(void){
//     uint8_t registro = 0x50;
//     validacion_t validacion;
//     validacion = leerRegistro(registro, leerDatagrama);
//     TEST_ASSERT_EQUAL(DATAGRAMA_CORRECTO,validacion);
// }
//
// void test_leerRegistro(void){
//     uint8_t registro = 0x50;
//     validacion_t validacion;
//     validacion = leerRegistro(registro, leerDatagrama);
//     TEST_ASSERT_EQUAL(DATAGRAMA_CORRECTO,validacion);
//     TEST_ASSERT_EQUAL(0x50,datagrama_recibido.registro);
//     TEST_ASSERT_EQUAL(0x00000FFF,datagrama_recibido.valor);
// }
//
//














// void test_setOperacionEscritura(){
//      uint8_t operacion;
//      operacion = trinamicSetOperacion(OPERACION_ESCRITURA);
//      TEST_ASSERT_EQUAL(0x80,operacion);
//  }
//
//
// void test_setOperacionLectura(){
//      uint8_t operacion;
//      operacion = trinamicSetOperacion(OPERACION_LECTURA);
//      TEST_ASSERT_EQUAL(0x00,operacion);
//  }
//
//
// /*Eligo para el este Test solo un registro*/
// void test_setRegistro (){
//      uint8_t registro;
//      registro = trinamicSetRegistro(TMC4671_PID_VELOCITY_P_VELOCITY_I);
//      //TEST_ASSERT_EQUAL(0x58,registro);
//      //TEST_ASSERT_EQUAL_MESSAGE(0x58,registro, "Test sobre el registro TMC4671_PID_VELOCITY_P_VELOCITY_I");
//  }






// void test_setOperacionRegistroEscritura(){
//     uint8_t operacionregistro;
//     operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);
//     TEST_ASSERT_EQUAL(0xD8,operacionregistro);
// }
//
//
//
// void test_DatagramaCompleto(){
//     uint8_t  operacionregistro;
//     uint32_t valor=5000;
//     uint32_t result=0;
//
//     operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);
//     trinamicArmarDatagrama(datagrama,operacionregistro,valor);
//
//     result = (datagrama[1] << 24) + (datagrama[2] << 16) + (datagrama[3] << 8) + (datagrama[4]);
//
//     TEST_ASSERT_EQUAL(0xD8,datagrama[0]);
//     TEST_ASSERT_EQUAL(5000,result);
//
// }

// void test_InformarRespuesta(){
//     datagramaRespuesta=trinamicObtenerDatagrama();
// }

/** @} Final de la definición del modulo para doxygen */
