#include "build/temp/_test_payload_spi.c"
#include "payload_spi.h"
#include "unity.h"




typedef struct {

    trinamicOperacion_t operacion;

    uint8_t registro;

    uint32_t valor;

}datagrama_t;

datagrama_t datagrama;



datagrama_t datagrama_recibido;













void enviarDatagrama(uint8_t * data){

    datagrama.operacion = data[0] & 0x80;

    datagrama.registro= data[0] & 0x7F;

    datagrama.valor= (data[1] << 24) + (data[2] << 16) + (data[3] << 8) + (data[4]);

}



void leerDatagrama(uint8_t * data){

   datagrama_recibido.operacion = data[0] & 0x80;

   datagrama_recibido.registro= data[0] & 0x7F;

   datagrama_recibido.valor= (data[1] << 24) + (data[2] << 16) + (data[3] << 8) + (data[4]);

}



void setUp(void){

}



void tearDown(void){



}



void test_validacion_escritura(void){

    validacion_t validacion;

    uint8_t operacion = OPERACION_ESCRITURA;

    uint8_t registro = 0x58;

    uint32_t valor = 0x000000FF;



    validacion = setearRegistro(operacion,registro,valor,enviarDatagrama);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((validacion)), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_INT);



}



void test_setRegistro(void){



    validacion_t validacion;

    uint8_t operacion = OPERACION_ESCRITURA;

    uint8_t registro = 0x60;

    uint32_t valor = 0x00FF00FF;



    validacion = setearRegistro(operacion,registro,valor,enviarDatagrama);

    if ( validacion == DATAGRAMA_CORRECTO){

        UnityAssertEqualNumber((UNITY_INT)((0x80)), (UNITY_INT)((datagrama.operacion)), (

       ((void *)0)

       ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((0x60)), (UNITY_INT)((datagrama.registro)), (

       ((void *)0)

       ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);

        UnityAssertEqualNumber((UNITY_INT)((0x00FF00FF)), (UNITY_INT)((datagrama.valor)), (

       ((void *)0)

       ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_transmitirDatagramaRegistroInvalido(){



    validacion_t validacion;

    uint8_t operacion = OPERACION_ESCRITURA;

    uint8_t registro = 0xFF;

    uint32_t valor = 0x000000FF;



    validacion = setearRegistro(operacion,registro,valor,enviarDatagrama);

    UnityAssertEqualNumber((UNITY_INT)((DATAGRAMA_INCORRECTO)), (UNITY_INT)((validacion)), (

   ((void *)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_INT);



}



void test_validacion_lectura(void){

    uint8_t registro = 0x50;

    validacion_t validacion;

    validacion = leerRegistro(registro, leerDatagrama);

    UnityAssertEqualNumber((UNITY_INT)((DATAGRAMA_CORRECTO)), (UNITY_INT)((validacion)), (

   ((void *)0)

   ), (UNITY_UINT)(94), UNITY_DISPLAY_STYLE_INT);

}



void test_leerRegistro(void){

    uint8_t registro = 0x50;

    validacion_t validacion;

    validacion = leerRegistro(registro, leerDatagrama);

    UnityAssertEqualNumber((UNITY_INT)((DATAGRAMA_CORRECTO)), (UNITY_INT)((validacion)), (

   ((void *)0)

   ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x50)), (UNITY_INT)((datagrama_recibido.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00000FFF)), (UNITY_INT)((datagrama_recibido.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_INT);

}
