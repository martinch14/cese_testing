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


uint8_t datagrama[TAMANIO_DATAGRAMA];

void setUp(void){
}

void tearDown(void){

}

 void test_setOperacionEscritura(){

     uint8_t operacion;
     operacion = trinamicSetOperacion(OPERACION_ESCRITURA);
     TEST_ASSERT_EQUAL(0x80,operacion);
 }

 void test_setOperacionLectura(){
     uint8_t operacion;
     operacion = trinamicSetOperacion(OPERACION_LECTURA);
     TEST_ASSERT_EQUAL(0x00,operacion);
 }

/*Eligo para el este Test solo un registro*/
 void test_setRegistro (){
     uint8_t registro;
     registro = trinamicSetRegistro(TMC4671_PID_VELOCITY_P_VELOCITY_I);
     //TEST_ASSERT_EQUAL(0x58,registro);
     TEST_ASSERT_EQUAL_MESSAGE(0x58,registro, "Test sobre el registro TMC4671_PID_VELOCITY_P_VELOCITY_I");
 }


void test_setOperacionRegistroEscritura(){
    uint8_t operacionregistro;
    operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);
    TEST_ASSERT_EQUAL(0xD8,operacionregistro);
}



void test_DatagramaCompleto(){
    uint8_t  operacionregistro;
    uint32_t valor=5000;
    uint32_t result=0;

    operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);
    trinamicArmarDatagrama(datagrama,operacionregistro,valor);

    result = (datagrama[1] << 24) + (datagrama[2] << 16) + (datagrama[3] << 8) + (datagrama[4]);

    TEST_ASSERT_EQUAL(0xD8,datagrama[0]);
    TEST_ASSERT_EQUAL(5000,result);

}

/** @} Final de la definición del modulo para doxygen */
