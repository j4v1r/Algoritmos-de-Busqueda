/*
BusquedaLinealArregloOrdenado.c
V 1.0 Marzo 2024
Grupo: 2CM2
Autores: Colunga Aguilar Javier Alejandro
		
Programa que lee una n cantidad de números y los escribe en un arreglo dinámico A,
después ejecuta el algoritmo de ordenamiento Rápido O(n logn) que ordena estos 
números de menor a mayor. 
Teniendo el arreglo ordenado el programa manda a llamar la función "busLineal" y busca
el número solicitado al inicio del programa, usando el algoritmo de Búsqueda Lineal O(n).

Compilación:
En el script.bat: 
gcc BusquedaLinealArregloOrdenado.c -o busLinealOr
busLinealOr n<archivo.txt> nombrearchivosalida.txt					

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TRUE 1
#define FALSE 0

void rapido(int *arr, int p, int r);
int pivote(int *arr, int p, int r);
void intercambiar(int *arr, int i, int j);
void busLineal(int *arr, int n, int valor, int resp[]);

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
		
		//Llamar el algoritmo de ordenamiento "rápido" para ordenar el arreglo
		rapido(A, 0, n-1);
	
		//Llamar al algoritmo de búsqueda
		busLineal(A, n, valor, arrRes);
		
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
void busLineal(int *arr, int n, int valor, int resp[])

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
la última posición del arreglo (n-1) y mientras el número en esa posición sea menor
o igual al valor buscado, pues de lo contrario significa que el número no se 
encuentra en el arreglo. Cada que se repite el ciclo la variable "comps" aumenta en
1 su valor, pues se ha necesitado de otra comparación para buscar el número.
Finalmente, se coloca en la posición 0 del arreglo "resp" la posición del número 
buscado (-1 si no existe) y en la posición 1 el número de comparaciones que tomó. 
*/
void busLineal(int *arr, int n, int valor, int resp[]){
	
	int res=-1, comps=0;
	
	/*Ciclo iterativo que continua la comparación mientras el indice sea menor o 
	igual al del final del arreglo y el número en esa posición sea menor al
	número buscado*/
	for(int i=0;i<=(n-1) && arr[i]<=valor; i++){
	
		//Se aumenta "comps" al haber una comparación
		comps++;
		
		/*Si el número en la posición "i" es igual al número buscado entonces "res" 
		toma el valor de "i"*/
		if(arr[i]==valor){
			res=i;
		}
			
	}	
	
	/*Se envían los valores de la posición del número buscado y la cantidad de 
	comparaciones en el indice 0 y 1 del arreglo "resp" respectivamente*/
	resp[0]=res;
	resp[1]=comps;
	
	return;
}
