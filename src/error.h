
//Las funciones de callback, son punteros a funciones!
typedef enum {
	INFO,
	WARNING,
	ERROR,
}tipo_error_t;

//Funcion de callback,
//es un puntero a un prototipo de funcion.
typedef void(* handler_t) (tipo_error_t nivel, const char * archivo,const char * funcion , int linea , const char * mensaje);
