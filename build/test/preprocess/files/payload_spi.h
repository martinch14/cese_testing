









typedef enum { OPERACION_ESCRITURA, OPERACION_LECTURA} trinamicOperacion_t;

typedef enum {TMC4671_PID_FLUX_P_FLUX_I,TMC4671_PID_TORQUE_P_TORQUE_I,TMC4671_PID_VELOCITY_P_VELOCITY_I,TMC4671_PID_POSITION_P_POSITION_I}trinamicRegistro_t;







uint8_t trinamicSetOperacion(trinamicOperacion_t operacion);

uint8_t trinamicSetRegistro(trinamicRegistro_t registro);

uint8_t trinamicsetOperacionRegistroEscritura(trinamicOperacion_t operacion,trinamicRegistro_t registro);

void trinamicArmarDatagrama(uint8_t * datagrama, uint8_t operacionregistro, uint32_t valor );
