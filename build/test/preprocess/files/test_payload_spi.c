#include "build/temp/_test_payload_spi.c"
#include "payload_spi.h"
#include "unity.h"




static datagrama_t datagrama;



struct {

 tipo_error_t nivel;

 char archivo [64];

 char funcion [64];

 int linea;

 char mensaje[64];

}error;



void RegistrarError(tipo_error_t nivel, const char * archivo, const char * funcion ,const int linea ,const char * mensaje){

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

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.operacion)), (

   ((void *)0)

   ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaCargar(void){

    uint8_t reg=0xED;

    uint32_t val=0x0000FF00;



    datagramaCargar(reg,val,&datagrama);

    UnityAssertEqualNumber((UNITY_INT)((0xED)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x0000FF00)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaEnviar(void){



    uint8_t reg=0x08;

    uint32_t val=0x0000FFFF;

    uint8_t *datos;

    operacion_t operacion=OPERACION_ESCRITURA;



    datagramaCargar(reg,val,&datagrama);

    datos = datagramaEnviar(&datagrama,operacion);



    UnityAssertEqualNumber((UNITY_INT)((0x88)), (UNITY_INT)((datos[0])), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x0000FFFF)), (UNITY_INT)(((uint32_t)(datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]))), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaRecibir(void){

    uint8_t datorecibido[5]={0x21,0x21,0x21,0x11,0x21};



    datagramaRecibir(datorecibido,&datagrama);



    UnityAssertEqualNumber((UNITY_INT)((0x21)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(82), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x21211121)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(83), UNITY_DISPLAY_STYLE_INT);

}



void test_datagramaFlujoEnvioRecepcion(void){



    uint8_t reg=0x06;

    uint32_t val=0x00EEFFFF;

    uint8_t *datos;

    operacion_t operacion = OPERACION_ESCRITURA;



    datagramaCargar(reg,val,&datagrama);

    datos = datagramaEnviar(&datagrama,operacion);

    datagramaRecibir(datos,&datagrama);





    UnityAssertEqualNumber((UNITY_INT)((0x86)), (UNITY_INT)((datos[0])), (

   ((void *)0)

   ), (UNITY_UINT)(98), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00EEFFFF)), (UNITY_INT)(((uint32_t)(datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]))), (

   ((void *)0)

   ), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_INT);

}





void test_datagramaCargarRegistroInvalido(void){

    uint8_t reg=0xFF;

    uint32_t val=0x0000FF00;



    datagramaCargar(reg,val,&datagrama);

    UnityAssertEqualNumber((UNITY_INT)((WARNING)), (UNITY_INT)((error.nivel)), (

   ((void *)0)

   ), (UNITY_UINT)(108), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualString((const char*)(("Valor de registro ingresado invalido")), (const char*)((error.mensaje)), (

   ((void *)0)

   ), (UNITY_UINT)(109));

}
