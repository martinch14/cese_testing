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
#include <string.h>

static datagrama_t datagrama;

struct {
	tipo_error_t nivel;
	char archivo [64];
	char funcion [64];
	int linea;
	char mensaje[64];
}error;

void RegistrarError(tipo_error_t nivel, const char * archivo, const char * funcion ,const  int linea ,const char * mensaje){
	error.nivel = nivel;
	error.linea = linea;
	strcpy(error.archivo, archivo);
	strcpy(error.funcion, funcion);
	strcpy(error.mensaje, mensaje);
}

void setUp(void){

	datagramaCrear(&datagrama,RegistrarError);

}

void test_datagramaCrear(void){

    datagramaCrear(&datagrama,RegistrarError);
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

    uint8_t reg=0x08;
    uint32_t val=0x0000FFFF;
    uint8_t *datos;
    operacion_t operacion=OPERACION_ESCRITURA;

    datagramaCargar(reg,val,&datagrama);
    datos = datagramaEnviar(&datagrama,operacion);

    TEST_ASSERT_EQUAL(0x88,datos[0]);
    TEST_ASSERT_EQUAL(0x0000FFFF, (uint32_t)(datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]));

}

void test_datagramaRecibir(void){
    uint8_t datorecibido[5]={0x21,0x21,0x21,0x11,0x21};

    datagramaRecibir(datorecibido,&datagrama);

    TEST_ASSERT_EQUAL(0x21,datagrama.registro);
    TEST_ASSERT_EQUAL(0x21211121,datagrama.valor);
}

void test_datagramaFlujoEnvioRecepcion(void){

    uint8_t reg=0x06;
    uint32_t val=0x00EEFFFF;
    uint8_t *datos;
    operacion_t operacion = OPERACION_ESCRITURA;

    datagramaCargar(reg,val,&datagrama);
    datos = datagramaEnviar(&datagrama,operacion);
    datagramaRecibir(datos,&datagrama);

    /*Comparo datos[0]  con 0x86 porque defini una operacion de escritura */
    TEST_ASSERT_EQUAL(0x86,datos[0]);
    TEST_ASSERT_EQUAL(0x00EEFFFF,(uint32_t)(datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]));
}


void test_datagramaCargarRegistroInvalido(void){
    uint8_t reg=0xFF;
    uint32_t val=0x0000FF00;

    datagramaCargar(reg,val,&datagrama);
    TEST_ASSERT_EQUAL(WARNING,error.nivel);
    TEST_ASSERT_EQUAL_STRING("Valor de registro ingresado invalido", error.mensaje);
}

/** @} Final de la definición del modulo para doxygen */
