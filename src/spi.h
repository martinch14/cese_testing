

/*Funciones Callback para la transmision y recepcion de datos para comunicarse con el integrado*/
//typedef void(*spiEnviarHandler_t) (uint8_t operacion, uint8_t registro ,uint32_t valor);
//typedef void(*spiRecibirHandler_t)(uint8_t operacion, uint8_t registro ,uint32_t valor);

typedef void(*spiEnviarHandler_t) (uint8_t *data);
typedef void(*spiRecibirHandler_t) (uint8_t *data);

/*
Desde estas funciones voy a enviar los datos desde la biblioteca de la sapi de SPI
*/
