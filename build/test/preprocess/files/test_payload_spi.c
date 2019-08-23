#include "build/temp/_test_payload_spi.c"
#include "payload_spi.h"
#include "unity.h"




uint8_t datagrama[5];



void setUp(void){

}



void tearDown(void){



}



 void test_setOperacionEscritura(){



     uint8_t operacion;

     operacion = trinamicSetOperacion(OPERACION_ESCRITURA);

     UnityAssertEqualNumber((UNITY_INT)((0x80)), (UNITY_INT)((operacion)), (

    ((void *)0)

    ), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_INT);

 }



 void test_setOperacionLectura(){

     uint8_t operacion;

     operacion = trinamicSetOperacion(OPERACION_LECTURA);

     UnityAssertEqualNumber((UNITY_INT)((0x00)), (UNITY_INT)((operacion)), (

    ((void *)0)

    ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

 }





 void test_setRegistro (){

     uint8_t registro;

     registro = trinamicSetRegistro(TMC4671_PID_VELOCITY_P_VELOCITY_I);

     UnityAssertEqualNumber((UNITY_INT)((0x58)), (UNITY_INT)((registro)), (

    ((void *)0)

    ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

 }





void test_setOperacionRegistroEscritura(){

    uint8_t operacionregistro;

    operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);

    UnityAssertEqualNumber((UNITY_INT)((0xD8)), (UNITY_INT)((operacionregistro)), (

   ((void *)0)

   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);

}







void test_DatagramaCompleto(){

uint8_t operacionregistro;

uint32_t valor=5000;



operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);

trinamicArmarDatagrama(datagrama,operacionregistro,valor);



UnityAssertEqualNumber((UNITY_INT)((0xD8)), (UNITY_INT)((datagrama[0])), (

((void *)0)

), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_INT);



}
