#include <stdio.h>

int main() {
    int i;
    int num = 10;
    int array[5] = {1, 2, 3, 4, 5};
    int contador = 0;

    for (i = 1; i < 10; i--) { //no debe ser con -- sino con ++ para que no sea infinito
        printf("Valor de i: %d\n", i);
    }

    for (i = 0; i <= 5; i++) {  //deberia ser solo hasta 4, o sin el igual, pues el array empieza en la posicion 0
        printf("Elemento del array: %d\n", array[i]);
    }

    while (num != 0) { // num siempre es diferente de cero, entonces da un bucle infinito
        printf("Valor de num: %d\n", num);
        num = num + 1;  
    }

    while (contador < 5) { //se queda ahi infinitamente pues contador vale 0
        printf("Valor de contador: %d\n", contador);
    }     

    return 0;
}