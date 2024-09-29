//#include <stdio.h>
//#include <string.h>

int main() {
    // Datos enteros
    int entero = 10.5;                              //debe ser un foat  //casting implícito: int entero = 10.5
                                                                       //casting explícito: enterio = (int)(var)
    printf("El valor del entero es: %d\n", entero);  

    // Datos float
    float decimal = 3 / 2;  
    printf("El valor del decimal es: %f\n", decimal);  // division entre 2 enterios -->un entero: 3/2 = 1  ;para evitar esto: float decimal= (float) 3/2 o 3.0/2
    float decimal_1 = 12.5 * 5;  
    printf("El valor del decimal es: %d\n", decimal_1);  //tiene que ser con %f

    // Caracteres
    char letra = "A";  //tiene que ser con ''
    printf("El valor del caracter es: %c\n", letra);  // "A"!='A' el primero es una cadena, el otro no. La cadena tiene el \0 nulo al final

    // Cadenas de caracteres
    char nombre[5];  //char nombre[5]    //nombre es un puntero: a un puntero solo se le pueden asignar direcciones de memoria, no datos --->apunta a la direccion de memoria del primer elemento del arreglo
    strcpy(nombre, "Henry");             //strpcy(nombre, "Henry")   está malo, pues con el \0 es de 6 bits
    printf("El nombre es: %s\n", nombre);

    return 0;
}