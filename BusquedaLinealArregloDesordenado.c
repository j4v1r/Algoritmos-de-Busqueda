/*
BusquedaLinealArregloDesordenado.c
V 1.0 Marzo 2024
Grupo: 2CM2
Autores: Colunga Aguilar Javier Alejandro
		
Programa que lee una n cantidad de números y los escribe en un arreglo dinámico A,
después se manda a llamar la función "busLinealDes" y busca el número solicitado al 
inicio del programa, usando el algoritmo de Búsqueda Lineal O(n).

Compilación:
En el script.bat: 
gcc BusquedaLinealArregloDesordenado.c -o busLinealDesor
busLinealDesor n<archivo.txt> nombrearchivosalida.txt					

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0

void busLinealDes(int *arr, int n, int valor, int resp[]);

int main(int nums, char* argv[]){
	
	
	int* A; //Guarda la dirección del bloque creado
	int n, i, j , p, r, arrRes[2], valor=10393545;
	
	//Recibir por argumento el tamaÃ±o de n y el valor a buscar
	if (nums!=2) 
	{
		printf("\nIndique el tamanio de n - Ejemplo: [user@equipo]$ %s 100\n",argv[0]);
		exit(1);
	} 
	
	//Tomar el argumento del main
	n=atoi(argv[1]); //n
	
	
	//Asigna memoria dinamica usando malloc()
	A = malloc(n*sizeof(int));
		  //(int*) Cambio de una variable perteneciente a un tipo de dato a otro.
	
	if(A == NULL) {
		//Comprueba que la memoria sí fue asignada
        printf("Memoria no asignada\n");
        exit(0);
        
    }else{
    	
		//Leer de la entrada estandar los n valores y colocarlos en el arreglo de nÃºmeros
		for(i=0;i<n;i++){
			scanf("%d",&A[i]);
		}
	
		//Llamar al algoritmo de búsqueda
		busLinealDes(A, n, valor, arrRes);
		
		if(arrRes[0]>=0){
			/*Envia a la salida la posición del número buscado y el número de comparaciones que fueron
			necesarias para determinarlo*/
			printf("\n\nLa posicion de %d en el arreglo es %d y tomo %d de comparaciones para encontarlo", valor, arrRes[0], arrRes[1]);
		
		}else{
			/*Envia a la salida que el número buscado no es encuentra y el número de comparaciones que fueron
			necesarias para determinarlo*/
			printf("\n\nEl número %d no fue encontrado en el arreglo y tomo %d de comparaciones para determinarlo", valor, arrRes[1]);
			
		}
		
	}
	
	return 0;
}

/*
void busLinealDes(int *arr, int n, int valor, int resp[])

Recibe: int *arr, dirección del arreglo ordenado A de memoria dinámica
		int n, cantidad de números en los que debe buscar
		int valor, número que debe encontrar en el arreglo
		int resp[], arreglo estático que almacena la posición del número
		buscado en la posición [0] y el número de comparaciones que
		tomó en la posición [1]
		
Devuelve: void (No retorna valor explicito)

Observaciones: busLineal se encarga de encontrar la posición ("res") en el arreglo 
"A" del número "valor" y de contabilizar el número de comparaciones que fueron 
necesarias ("comps"). 
Para esto, recorre todo el arreglo mientras el indice "i" sea menor o igual al de 
la última posición del arreglo (n-1), pues de lo contrario significa que el número 
no se encuentra en el arreglo. Cada que se repite el ciclo la variable "comps" 
aumenta en 1 su valor, pues se ha necesitado de otra comparación para buscar el
número. Cuando se ha encontrado el número, el indice "i" toma el valor de n, para 
detener el ciclo de comparaciones y evitar comparar con los demás números.
Finalmente, se coloca en la posición 0 del arreglo "resp" la posición del número 
buscado (-1 si no existe) y en la posición 1 el número de comparaciones que tomó. 
*/
void busLinealDes(int *arr, int n, int valor, int resp[]){
	
	int res=-1, comps=0;
	
	/*Ciclo iterativo que continua la comparación mientras el indice sea menor o 
	igual al del final del arreglo (n-1)*/
	for(int i=0;i<=(n-1); i++){
	
		//Se aumenta "comps" al haber una comparación
		comps++;
		
		/*Si el número en la posición "i" es igual al número buscado entonces "res" 
		toma el valor de "i" e "i" el valor de "n" para detener el ciclo*/
		if(arr[i]==valor){
			res=i;
			i=n;
		}
			
	}	
	
	/*Se envían los valores de la posición del número buscado y la cantidad de 
	comparaciones en el indice 0 y 1 del arreglo "resp" respectivamente*/
	resp[0]=res;
	resp[1]=comps;
	
	return;
}
