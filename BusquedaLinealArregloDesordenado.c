/*
BusquedaLinealArregloDesordenado.c
V 1.0 Marzo 2024
Grupo: 2CM2
Autores: Colunga Aguilar Javier Alejandro
		
Programa que lee una n cantidad de n�meros y los escribe en un arreglo din�mico A,
despu�s se manda a llamar la funci�n "busLinealDes" y busca el n�mero solicitado al 
inicio del programa, usando el algoritmo de B�squeda Lineal O(n).

Compilaci�n:
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
	
	
	int* A; //Guarda la direcci�n del bloque creado
	int n, i, j , p, r, arrRes[2], valor=10393545;
	
	//Recibir por argumento el tamaño de n y el valor a buscar
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
		//Comprueba que la memoria s� fue asignada
        printf("Memoria no asignada\n");
        exit(0);
        
    }else{
    	
		//Leer de la entrada estandar los n valores y colocarlos en el arreglo de números
		for(i=0;i<n;i++){
			scanf("%d",&A[i]);
		}
	
		//Llamar al algoritmo de b�squeda
		busLinealDes(A, n, valor, arrRes);
		
		if(arrRes[0]>=0){
			/*Envia a la salida la posici�n del n�mero buscado y el n�mero de comparaciones que fueron
			necesarias para determinarlo*/
			printf("\n\nLa posicion de %d en el arreglo es %d y tomo %d de comparaciones para encontarlo", valor, arrRes[0], arrRes[1]);
		
		}else{
			/*Envia a la salida que el n�mero buscado no es encuentra y el n�mero de comparaciones que fueron
			necesarias para determinarlo*/
			printf("\n\nEl n�mero %d no fue encontrado en el arreglo y tomo %d de comparaciones para determinarlo", valor, arrRes[1]);
			
		}
		
	}
	
	return 0;
}

/*
void busLinealDes(int *arr, int n, int valor, int resp[])

Recibe: int *arr, direcci�n del arreglo ordenado A de memoria din�mica
		int n, cantidad de n�meros en los que debe buscar
		int valor, n�mero que debe encontrar en el arreglo
		int resp[], arreglo est�tico que almacena la posici�n del n�mero
		buscado en la posici�n [0] y el n�mero de comparaciones que
		tom� en la posici�n [1]
		
Devuelve: void (No retorna valor explicito)

Observaciones: busLineal se encarga de encontrar la posici�n ("res") en el arreglo 
"A" del n�mero "valor" y de contabilizar el n�mero de comparaciones que fueron 
necesarias ("comps"). 
Para esto, recorre todo el arreglo mientras el indice "i" sea menor o igual al de 
la �ltima posici�n del arreglo (n-1), pues de lo contrario significa que el n�mero 
no se encuentra en el arreglo. Cada que se repite el ciclo la variable "comps" 
aumenta en 1 su valor, pues se ha necesitado de otra comparaci�n para buscar el
n�mero. Cuando se ha encontrado el n�mero, el indice "i" toma el valor de n, para 
detener el ciclo de comparaciones y evitar comparar con los dem�s n�meros.
Finalmente, se coloca en la posici�n 0 del arreglo "resp" la posici�n del n�mero 
buscado (-1 si no existe) y en la posici�n 1 el n�mero de comparaciones que tom�. 
*/
void busLinealDes(int *arr, int n, int valor, int resp[]){
	
	int res=-1, comps=0;
	
	/*Ciclo iterativo que continua la comparaci�n mientras el indice sea menor o 
	igual al del final del arreglo (n-1)*/
	for(int i=0;i<=(n-1); i++){
	
		//Se aumenta "comps" al haber una comparaci�n
		comps++;
		
		/*Si el n�mero en la posici�n "i" es igual al n�mero buscado entonces "res" 
		toma el valor de "i" e "i" el valor de "n" para detener el ciclo*/
		if(arr[i]==valor){
			res=i;
			i=n;
		}
			
	}	
	
	/*Se env�an los valores de la posici�n del n�mero buscado y la cantidad de 
	comparaciones en el indice 0 y 1 del arreglo "resp" respectivamente*/
	resp[0]=res;
	resp[1]=comps;
	
	return;
}
