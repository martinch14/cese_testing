#include "build/temp/_test_payload_spi.c"
#include "payload_spi.h"
#include "unity.h"




static datagrama_t datagrama;



void setUp(void){

}



void tearDown(void){



}



void test_datagramaCrear(void){



    datagramaCrear(&datagrama);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.operacion)), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaCargar(void){

    uint8_t reg=0xED;

    uint32_t val=0x0000FF00;



    datagramaCargar(reg,val,&datagrama);

    UnityAssertEqualNumber((UNITY_INT)((0xED)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x0000FF00)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaEnviar(void){



    uint8_t reg=0x40;

    uint32_t val=0x0000FFFF;

    uint8_t *datos;



    datagramaCargar(reg,val,&datagrama);

    datos = datagramaEnviar(&datagrama);



    UnityAssertEqualNumber((UNITY_INT)((0x40)), (UNITY_INT)((datos[0])), (

   ((void *)0)

   ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x0000FFFF)), (UNITY_INT)(((datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]))), (

   ((void *)0)

   ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaRecibir(void){

    uint8_t datorecibido[5]={0x21,0x21,0x21,0x11,0x21};

    datagramaRecibir(datorecibido,&datagrama);

    UnityAssertEqualNumber((UNITY_INT)((0x21)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x21211121)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);

}
