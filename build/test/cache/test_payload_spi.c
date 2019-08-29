#include "build/temp/_test_payload_spi.c"
#include "payload_spi.h"
#include "unity.h"




static datagrama_t datagrama;





void test_datagramaCrear(void){



    datagramaCrear(&datagrama);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.operacion)), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaCargar(void){

    uint8_t reg=0xED;

    uint32_t val=0x0000FF00;



    datagramaCargar(reg,val,&datagrama);

    UnityAssertEqualNumber((UNITY_INT)((0xED)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x0000FF00)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaEnviar(void){



    uint8_t reg=0x40;

    uint32_t val=0x0000FFFF;

    uint8_t *datos;



    datagramaCargar(reg,val,&datagrama);

    datos = datagramaEnviar(&datagrama);



    UnityAssertEqualNumber((UNITY_INT)((0x40)), (UNITY_INT)((datos[0])), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x0000FFFF)), (UNITY_INT)(((datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]))), (

   ((void *)0)

   ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);



}



void test_datagramaRecibir(void){

    uint8_t datorecibido[5]={0x21,0x21,0x21,0x11,0x21};



    datagramaRecibir(datorecibido,&datagrama);



    UnityAssertEqualNumber((UNITY_INT)((0x21)), (UNITY_INT)((datagrama.registro)), (

   ((void *)0)

   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x21211121)), (UNITY_INT)((datagrama.valor)), (

   ((void *)0)

   ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_INT);

}







void test_datagramaFlujo(void){



    uint8_t reg=0x56;

    uint32_t val=0x00EEFFFF;

    uint8_t *datos;



    datagramaCargar(reg,val,&datagrama);

    datos = datagramaEnviar(&datagrama);

    datagramaRecibir(datos,&datagrama);



    UnityAssertEqualNumber((UNITY_INT)((0x56)), (UNITY_INT)((datos[0])), (

   ((void *)0)

   ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0x00EEFFFF)), (UNITY_INT)(((datos[1] << 24) + (datos[2] << 16) + (datos[3] << 8) + (datos[4]))), (

   ((void *)0)

   ), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_INT);

}
