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
     TEST_ASSERT_EQUAL(0x58,registro);
 }


void test_setOperacionRegistroEscritura(){
    uint8_t operacionregistro;
    operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);
    TEST_ASSERT_EQUAL(0xD8,operacionregistro);
}



void test_DatagramaCompleto(){
uint8_t  operacionregistro;
uint32_t valor=5000;

operacionregistro= trinamicsetOperacionRegistroEscritura(OPERACION_ESCRITURA,TMC4671_PID_VELOCITY_P_VELOCITY_I);
trinamicArmarDatagrama(datagrama,operacionregistro,valor);

TEST_ASSERT_EQUAL(0xD8,datagrama[0]);

}
