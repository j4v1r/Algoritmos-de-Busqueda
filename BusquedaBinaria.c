/*
BusquedaBinaria.c
V 1.0 Marzo 2024
Grupo: 2CM2
Autores: Colunga Aguilar Javier Alejandro
		
Programa que lee una n cantidad de números y los escribe en un arreglo dinámico A,
después ejecuta el algoritmo de ordenamiento Rápido O(n logn) que ordena estos 
números de menor a mayor. 
Teniendo el arreglo ordenado el programa manda a llamar la función "busBinaria" y busca
el número solicitado al inicio del programa, usando el algoritmo de Búsqueda Binaria O(log n).

Compilación:
En el script.bat: 
gcc BusquedaBinaria.c -o busBinar
busBinar n<archivo.txt> nombrearchivosalida.txt					

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0

void rapido(int *arr, int p, int r);
int pivote(int *arr, int p, int r);
void intercambiar(int *arr, int i, int j);
void busBinaria(int *arr, int valor, int inicio, int final, int resp[], int comps);

int main(int nums, char* argv[]){
	
	
	int* A; //Guarda la dirección del bloque creado
	int n, i, arrRes[2], valor=10393545, comps;
	
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
		
		//Llamar el algoritmo de ordenamiento "rápido" para ordenar el arreglo
		rapido(A, 0, n-1);
	
		//Llamar al algoritmo de búsqueda
		busBinaria(A, valor, 0, n-1, arrRes, 0);
		
		if(arrRes[0]>=0){
			/*Envia a la salida la posición del número buscado y el número de comparaciones que fueron
			necesarias para determinarlo*/
			printf("\n\nLa posicion de %d en el arreglo es %d y tomo %d comparaciones para encontarlo", valor, arrRes[0], arrRes[1]);
		
		}else{
			/*Envia a la salida que el número buscado no es encuentra y el número de comparaciones que fueron
			necesarias para determinarlo*/
			printf("\n\nEl número %d no fue encontrado en el arreglo y tomo %d comparaciones para determinarlo", valor, arrRes[1]);
			
		}
		
	}
	
	return 0;
}

/*
void rapido(int *arr,int p, int r)

Recibe: int *arr, dirección del arreglo ptr de memoria dinámica
		int p, inicio del arreglo recibido
		int r, final del arreglo recibido
		
Devuelve: void (No retorna valor explicito)

Observaciones: Si la primera posición del arreglo es menor que la última se manda a llamar
la función "pivote" para obtener un número pivote ("j") que "divida" el arreglo en dos partes.
Después, se vuelve a llamar la función "rapido", enviando el arreglo, y la posición "p" como el 
inicio y "j-1" como el final para los números a la derecha del pivote y la posición "j+1" como 
el inicio y "r" como el final para los números a la izquierda del pivote. 
*/
void rapido(int *arr, int p, int r){
	 
	if(p<r){
		//Se obtiene el número que divide el arreglo con la función "pivote"
		int j=pivote(arr, p, r);
		//Se mandan a llamar nuevamente la función para repetir el mismo proceso
		rapido(arr, p, j-1);
		rapido(arr, j+1, r);
	}
	
	return;	
}


/*
void pivote(int *arr, int p, int r)

Recibe: int *arr, dirección del arreglo ptr de memoria dinámica
		int p, posición incial en el arreglo de los números a la izquierda del pivote
		int r, posición final en el arreglo de los números a la derecha del pivote
		
Devuelve: int j, la posición en el arreglo donde se encuentra el pivote seleccionado

Observaciones: La función "pivote" se encarga de seleccionar el número en la posición "p"
del arreglo (que llamaremos pivote) y compararlo con los demás números del arreglo, de 
izquierda a derecha lo hace con el indice "i" (excluyendo el número en la posición 0, 
es decir, el pivote) y de derecha a izquierda con el indice "j".

Si un número a la izquierda es mayor o igual que el pivote se guarda la posición de este ("i"), 
de lo contrario el ciclo continua, avanzando una posición, hasta encontrar un número mayor o igual.
Lo mismo sucede con los números a la derecha, si hay un número menor que el pivote se guarda
su posición ("j"), de lo contrario el ciclo continua, retrocediendo una posición, hasta
encontar un número menor.

Una vez se ha encontrado un número mayor y un número menor al pivote se manda a llamar la 
función "intercambiar", enviando el arreglo y la posición de estos en el mismo para 
ser intercambiados entre ellos.
Este ciclo se repite mientras el indice que va de izquierda derecha ("i") sea menor al 
indice de los que va de derecha a izquierda ("j"), pues cuando "i" es mayor que "j" significa
que se han recorrido y ordenado todos los números del arreglo.

Después, el pivote se coloca en su posición correcta en el arreglo mandando a llamar nuevamente
la función "intercambiar" y enviando la posición original del pivote ("p") y la posición donde debe
colocarse ("j").

Finalmente, la función regresa la posición en el arreglo donde se encuentra el pivote seleccionado ("j").
*/
int pivote(int *arr, int p, int r){
	
	int piv=arr[p], i=p+1, j=r;
	
	//Mientras el indice "i" esté a la derecha del indice "j" el ciclo continua
	while(i<j){
		
		//Ciclo que recorre los números de izquierda a derecha hasta encontrar uno mayor o igual al pivote
		while(arr[i]<=piv && i<r){
			i++;
		}
		
		//Ciclo que recorre los números de izquierda a derecha hasta encontrar uno menor al pivote
		while(arr[j]>piv){
			j--;
		}
		
		//Condicional que indica intercambiar la posición de los números mientras el indice "i" sea menor al "j"
		if(i<j){
			intercambiar(arr, i, j);
		}
	}
	
	//Al finalizar de ordenar los números mayores, menore e iguales al pivote, se coloca este en su posición correcta
	intercambiar(arr, p, j);
	
	return j;	
}


/*
void intercambiar(int *arr, int i, int j)

Recibe: int *arr, dirección del arreglo ptr de memoria dinámica
		int i, posición en el arreglo de un número a intercambiar
		int j, posición en el arreglo de un número a intercambiar
		
Devuelve: void (No retorna valor explicito)

Observaciones: Haciendo uso de la variable "aux", la función intercambia los
números en la posición "i" y "j" del arreglo, asignando a la variable "aux" 
el valor del número en la posición "j", después a la posición "j" el número
en la posición "i" y finalmente a la posición "i" el valor de "aux".
*/
void intercambiar(int *arr, int i, int j){
	
	int aux;
	
	aux=arr[j];
	arr[j]=arr[i];
	arr[i]=aux;
	
	return;
}


/*
void busBinaria(int *arr, int valor, int incio, int final, int resp[], int comps)

Recibe: int *arr, dirección del arreglo ordenado A de memoria dinámica
		int valor, número que debe encontrar en el arreglo
		int inicio, indice que marca el inicio de la división del arreglo recibida
		int final, indice que marca el inicio de la división del arreglo recibida
		int resp[], arreglo estático que almacena la posición del número
		buscado en la posición [0] y el número de comparaciones que
		tomó en la posición [1]
		int comps, conteo de las comparaciones que se han llevado a cambo
		
Devuelve: void (No retorna valor explicito)

Observaciones: El algoritmo revisa primero que el incicio del arreglo sea menor que el
final, de lo contrario no hay nada más que comparar y el número no se encuentra.

De no ser así, se encarga de recibir un arreglo ordenado y encontrar el número que se 
encuentra justo a la mitad y compararlo con el valor que se busca, de esta comparación 
hay tres posibles resultados: que este valor medio sea igual al número buscado y se 
envíe el indice; que el número buscado sea menor al valor medio, lo que manda a llamar 
la función mandando la mitad de la "izquierda"; que el número buscado sea mayor al 
valor medio, lo que manda a llamar la función mandando la mitad de la "derecha". En 
cada caso, la variable "comps" aumenta su valor en uno para contabilizar las 
comparaciones llevadas a cabo. 
*/
void busBinaria(int *arr, int valor, int inicio, int final, int resp[], int comps){
		
	int mitad;
	
	//Condicional que revisa si hay aún números que revisar
	if(inicio>final){
		
		/*Si no hay significa que el número no está en el arreglo y se marca con un -1, además, se envía
		el número de comparaciones necesarias para llegar a esta conclusión*/
		resp[0]=-1;
		resp[1]=comps;
	}else{	
		//Se determina el valor medio del arreglo actual
		mitad=(inicio+final)/2;
		
		if(valor==arr[mitad]){
			/*Si el valor a la mitad es igual al buscado el algoritmo termina y se envía la posición y
			la cantidad de comparaciones necesarias al arreglo "resp"*/	
			comps++;
			resp[0]=mitad;
			resp[1]=comps;
		}else if(valor>arr[mitad]){
			/*Si el valor buscado es mayor al valor medio entonces se llama a la propia función de nuevo y 
			se envía la mitad de la derecha, el contador de comparaciones aumenta en 1*/
			comps++;
			return busBinaria(arr, valor, mitad+1, final, resp, comps);
			
		}else{
			/*Si el valor buscado es mayor al valor medio entonces se llama a la propia función de nuevo y 
			se envía la mitad de la izquierda, el contador de comparaciones aumenta en 1*/
			comps++;
			return busBinaria(arr, valor, inicio, mitad-1, resp, comps);
		}
		
	}	
	
	return;
}
