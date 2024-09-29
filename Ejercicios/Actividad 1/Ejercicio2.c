// Ejercicio 2

//1. 
//#include <stdint.h>
// char : en micro suelen usarse para variables de 8 bits
#define PORTA_DATA_REG *(volatile unsigned char *)(0x400FF000)  /// primer*:crea el puntero;  segundo*: desreferenciando el puntero: solo quiero el contenido

// la verdadera forma correcta utilizando la biblioteca

#define PORTA_DATA_REG *(volatile unsigned uint_8 *)(0x400FF000)
#define SET_BIT(reg, bit) ((reg) |= (1 << (bit)))       //hace una or, en el bit del registro: obliga a un 1
#define CLEAR_BIT(reg, bit) ((reg) &= ~(1 << (bit)))    //obliga a un 0



//2
#define CHECK_PER(reg)((reg)&(1 << (31)))      //si el bit 31 está en 1, el periferico está presente en este dispositivo
                                              // 0 si no existe, 1 sí existe
//3
#define TOGGLE_BIT(reg, bit) ((reg) ^= (1 << (bit))) 