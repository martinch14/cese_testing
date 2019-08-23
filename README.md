#cese_testing

Se utilizo TDD para la escritura de este código, el mismo sirve para armar un datagrama ajustandose
al protocolo definido por el fabricante TRINAMIC MOTION CONTROL para la comunicación con el 
circuito integrado TMC4671 a través del protocolo SPI.

Para el diseño del datagrama se cumple con las siguientes especificaciones:


TMC4671A uses 40 bit SPITM (Serial Peripheral Interface, SPI is Trademark of Motorola) datagrams
for communication with a microcontroller. Microcontrollers which are equipped with hardware SPI are
typically able to communicate using integer multiples of 8 bit. The NCS line of the device must be
handled in a way, that it stays active (low) for the complete duration of the datagram transmission.
Each datagram sent to the device is composed of an address byte followed by four data bytes. This
allows direct 32 bit data word communication with the register set. Each register is accessed via 32
data bits even if it uses less than 32 data bits.
For simplification, each register is specified by a one byte address:
- For a read access the most significant bit of the address byte is 0.
- For a write access the most significant bit of the address byte is 1.
Most registers are write only registers, some can be read additionally, and there are also some read
only registers.



Los registros sobre los que se realizaran los test son los siguientes:

TMC4671_PID_FLUX_P_FLUX_I                  0x54
TMC4671_PID_TORQUE_P_TORQUE_I              0x56
TMC4671_PID_VELOCITY_P_VELOCITY_I          0x58
TMC4671_PID_POSITION_P_POSITION_I          0x5A
