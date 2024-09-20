Como experimento, voy hacer que otro LED, como por ejemplo el verde, se prenda y apague a la misma frecuencia de la del LED rojo. 

Primero especifiqué las anteriores definiciones, como unicamente las del LED rojo. Esto tanto en el archivo base de led_blinky, como en el pin_mux.
![alt text](image-1.png)
![alt text](image.png)

Luego definí lo necesario para el led verde en pin_mux.h: 
![alt text](image-2.png)

y en el código base: 
![](image-3.png)

y activé el GPIO en pin_mux.c
![alt text](image-5.png)

y el mux del pin verde nuevo: 
![alt text](image-6.png)

y por lo tanto el bucle quedó de la siguiente manera: ![alt text](image-7.png)

comentando las lineas de código que apagaban nuevamente los leds