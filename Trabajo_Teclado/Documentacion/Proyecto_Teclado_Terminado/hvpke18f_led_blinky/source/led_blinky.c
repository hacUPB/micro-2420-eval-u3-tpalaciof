#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include <stdio.h>

/***************************
 * Definitions
 **************************/
#define BOARD_LED_GPIO     BOARD_INITPINS_LED_RED_GPIO // GPIOE

// LED ---> Salida
#define BOARD_LED_GPIO_PIN BOARD_INITPINS_LED_RED_PIN  // E2
// Filas ---> Salidas
#define BOARD_FIL1_GPIO_PIN BOARD_INITPINS_FIL1_PIN    // E3
#define BOARD_FIL2_GPIO_PIN BOARD_INITPINS_FIL2_PIN    // E4
#define BOARD_FIL3_GPIO_PIN BOARD_INITPINS_FIL3_PIN    // E5
#define BOARD_FIL4_GPIO_PIN BOARD_INITPINS_FIL4_PIN    // E6

// Columnas ---> Entradas
#define BOARD_COL1_GPIO_PIN BOARD_INITPINS_COL1_PIN    // E9
#define BOARD_COL2_GPIO_PIN BOARD_INITPINS_COL2_PIN    // E10
#define BOARD_COL3_GPIO_PIN BOARD_INITPINS_COL3_PIN    // E11
#define BOARD_COL4_GPIO_PIN BOARD_INITPINS_COL4_PIN    // E12

//Estados
int col = 0, fil = 0;
int cont = 1;
int DutyCycle, Dmax,Ton,Toff;
int NUM, DEC;
int check_col1, check_col2, check_col3, check_col4;

enum Estados {INICIO, PWM, DUTYCYCLE};

/***************************
 * Variables
 **************************/
volatile uint32_t g_systickCounter;

/***************************
 * Code
 **************************/
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

void Teclado(void)
{

	int* c = &col;
	int* f = &fil;
	for (int fila = 1; fila <= 4; fila++)
	{
		// Apagar todas las filas
	    GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_FIL1_GPIO_PIN);
	    GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_FIL2_GPIO_PIN);
	    GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_FIL3_GPIO_PIN);
	    GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_FIL4_GPIO_PIN);

	    // Activar la fila actual
	    if (fila == 1) GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_FIL1_GPIO_PIN);
	    if (fila == 2) GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_FIL2_GPIO_PIN);
	    if (fila == 3) GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_FIL3_GPIO_PIN);
	    if (fila == 4) GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_FIL4_GPIO_PIN);

	    // Leer el estado de todas las columnas
	    check_col1 = GPIO_PinRead(BOARD_LED_GPIO,BOARD_COL1_GPIO_PIN);
	    check_col2 = GPIO_PinRead(BOARD_LED_GPIO,BOARD_COL2_GPIO_PIN);
	    check_col3 = GPIO_PinRead(BOARD_LED_GPIO,BOARD_COL3_GPIO_PIN);
	    check_col4 = GPIO_PinRead(BOARD_LED_GPIO,BOARD_COL4_GPIO_PIN);

	    // Si alguna columna tiene nivel bajo (botón presionado en esta fila)
	    if (check_col1 == 0 || check_col2 == 0 || check_col3 == 0 || check_col4 == 0)
	    {
	    	if (check_col1 ==0)
	        {
	    		*c =1;
	        	*f = fila;
	        }
	        else if (check_col2 ==0)
	        {
	            *c = 2;
		        *f = fila;
	        }
	        else if (check_col3 ==0)
	        {
	            *c = 3;
	            *f = fila;
	        }
	        else if (check_col4 ==0)
	        {
	            *c =4;
	            *f = fila;
	        }
	     }
	 }
}

int main(void)
{


int* dmax = &Dmax;
int* ton = &Ton;
int* toff = &Toff;
int* dc = &DutyCycle;

int* dec = &DEC;
int* num = &NUM;

/* Board pin init */
BOARD_InitPins();
BOARD_InitBootClocks();

// Condiciones Iniciales PWM
*dc = 99; // De 0 a 99
*dmax = 100U; // Periodo máximo con D = 100%
*ton = (*dmax * *dc) / 100;
*toff = *dmax - *ton;

/* Set systick reload value to generate 1ms interrupt */
if (SysTick_Config(SystemCoreClock / 100000U))
	{
		while (1){}
	}

//GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN); //Apaga led
enum Estados Estado_actual = INICIO;


while(1){
	switch (Estado_actual){
		case INICIO:
			Teclado();
			if(col == 4 && fil == 4) //A
				{
				Estado_actual = PWM;
				GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN); //Apaga led
				}
			else{
				Estado_actual = INICIO;
				GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN); //Apaga led
			}
			col = 0, fil = 0;
			break;

		case PWM:
			Teclado();
			if(col == 4 && fil == 3){ //B
				Estado_actual = INICIO;
				GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN); //Apaga led
			}
			else if(col < 4 && col != 0 )
			{
				if ((col == 1 || col == 3) && fil == 1) // * o #
				{
				Estado_actual = PWM;
				GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
				GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
				}
				else if (col ==2 && fil ==1) // si es 0
				{
					*dec = 0;
					col = 0, fil = 0;
					while(col == 0 && fil ==0)
					{
						GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
						GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
						Teclado();
					}
					if(col ==2 && fil ==1) //si vuelve a ser 0
					{
						*num = 0;
						GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
						GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
						Estado_actual = DUTYCYCLE;
					}
					else{
					*num = col -3*(fil-4);
					GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
					SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
					GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
					SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
					Estado_actual = DUTYCYCLE;
					}
				}
				else // si no es cero
				{

					*dec = col -3*(fil-4);
					col = 0, fil = 0;
					while(col == 0 && fil ==0)
					{
						Teclado();
					}
					if (col ==2 && fil ==1) // si es cero
					{
						*num = 0;
						GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
						GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
						Estado_actual = DUTYCYCLE;
					}
					else
					{
						*num = col -3*(fil-4);
						GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
						GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
						SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
						Estado_actual = DUTYCYCLE;
					}
				}
			}
			else{ // A, C, D o nada
				Estado_actual = PWM;
				GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
				GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
			}
			col = 0, fil = 0;
			break;

		case DUTYCYCLE:
			Teclado();
			if(col == 4 && fil == 3){ //B
				Estado_actual = INICIO;
				GPIO_PortSet(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN); //Apaga led
			}
			else if(col == 4 && fil == 2){ //C

				GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
				GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
				Estado_actual = PWM;
			}
			else if(col == 4 && fil == 1){ // D

				*dc = (*dec*10)+*num; // De 0 a 99
				*ton = (*dmax * *dc) / 100;
				*toff = *dmax - *ton;
				Estado_actual = PWM;
			}
			else{

				GPIO_PortClear(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks((*dmax * *dc) / 100); // Tiempo encendido
				GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
				SysTick_DelayTicks(*dmax - (*dmax * *dc) / 100); // Tiempo apagado
				Estado_actual = DUTYCYCLE;
			}
			col = 0, fil = 0;
			break;
	}
}
return 0;
}

