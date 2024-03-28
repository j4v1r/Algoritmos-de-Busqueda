/*
BusquedaLinealArregloOrdenado.c
V 1.0 Marzo 2024
Grupo: 2CM2
Autores: Colunga Aguilar Javier Alejandro
		
Programa que lee una n cantidad de n�meros y los escribe en un arreglo din�mico A,
despu�s ejecuta el algoritmo de ordenamiento R�pido O(n logn) que ordena estos 
n�meros de menor a mayor. 
Teniendo el arreglo ordenado el programa manda a llamar la funci�n "busLineal" y busca
el n�mero solicitado al inicio del programa, usando el algoritmo de B�squeda Lineal O(n).

Compilaci�n:
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
		
		//Llamar el algoritmo de ordenamiento "r�pido" para ordenar el arreglo
		rapido(A, 0, n-1);
	
		//Llamar al algoritmo de b�squeda
		busLineal(A, n, valor, arrRes);
		
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
void rapido(int *arr,int p, int r)

Recibe: int *arr, direcci�n del arreglo ptr de memoria din�mica
		int p, inicio del arreglo recibido
		int r, final del arreglo recibido
		
Devuelve: void (No retorna valor explicito)

Observaciones: Si la primera posici�n del arreglo es menor que la �ltima se manda a llamar
la funci�n "pivote" para obtener un n�mero pivote ("j") que "divida" el arreglo en dos partes.
Despu�s, se vuelve a llamar la funci�n "rapido", enviando el arreglo, y la posici�n "p" como el 
inicio y "j-1" como el final para los n�meros a la derecha del pivote y la posici�n "j+1" como 
el inicio y "r" como el final para los n�meros a la izquierda del pivote. 
*/
void rapido(int *arr, int p, int r){
	 
	if(p<r){
		//Se obtiene el n�mero que divide el arreglo con la funci�n "pivote"
		int j=pivote(arr, p, r);
		//Se mandan a llamar nuevamente la funci�n para repetir el mismo proceso
		rapido(arr, p, j-1);
		rapido(arr, j+1, r);
	}
	
	return;	
}


/*
void pivote(int *arr, int p, int r)

Recibe: int *arr, direcci�n del arreglo ptr de memoria din�mica
		int p, posici�n incial en el arreglo de los n�meros a la izquierda del pivote
		int r, posici�n final en el arreglo de los n�meros a la derecha del pivote
		
Devuelve: int j, la posici�n en el arreglo donde se encuentra el pivote seleccionado

Observaciones: La funci�n "pivote" se encarga de seleccionar el n�mero en la posici�n "p"
del arreglo (que llamaremos pivote) y compararlo con los dem�s n�meros del arreglo, de 
izquierda a derecha lo hace con el indice "i" (excluyendo el n�mero en la posici�n 0, 
es decir, el pivote) y de derecha a izquierda con el indice "j".

Si un n�mero a la izquierda es mayor o igual que el pivote se guarda la posici�n de este ("i"), 
de lo contrario el ciclo continua, avanzando una posici�n, hasta encontrar un n�mero mayor o igual.
Lo mismo sucede con los n�meros a la derecha, si hay un n�mero menor que el pivote se guarda
su posici�n ("j"), de lo contrario el ciclo continua, retrocediendo una posici�n, hasta
encontar un n�mero menor.

Una vez se ha encontrado un n�mero mayor y un n�mero menor al pivote se manda a llamar la 
funci�n "intercambiar", enviando el arreglo y la posici�n de estos en el mismo para 
ser intercambiados entre ellos.
Este ciclo se repite mientras el indice que va de izquierda derecha ("i") sea menor al 
indice de los que va de derecha a izquierda ("j"), pues cuando "i" es mayor que "j" significa
que se han recorrido y ordenado todos los n�meros del arreglo.

Despu�s, el pivote se coloca en su posici�n correcta en el arreglo mandando a llamar nuevamente
la funci�n "intercambiar" y enviando la posici�n original del pivote ("p") y la posici�n donde debe
colocarse ("j").

Finalmente, la funci�n regresa la posici�n en el arreglo donde se encuentra el pivote seleccionado ("j").
*/
int pivote(int *arr, int p, int r){
	
	int piv=arr[p], i=p+1, j=r;
	
	//Mientras el indice "i" est� a la derecha del indice "j" el ciclo continua
	while(i<j){
		
		//Ciclo que recorre los n�meros de izquierda a derecha hasta encontrar uno mayor o igual al pivote
		while(arr[i]<=piv && i<r){
			i++;
		}
		
		//Ciclo que recorre los n�meros de izquierda a derecha hasta encontrar uno menor al pivote
		while(arr[j]>piv){
			j--;
		}
		
		//Condicional que indica intercambiar la posici�n de los n�meros mientras el indice "i" sea menor al "j"
		if(i<j){
			intercambiar(arr, i, j);
		}
	}
	
	//Al finalizar de ordenar los n�meros mayores, menore e iguales al pivote, se coloca este en su posici�n correcta
	intercambiar(arr, p, j);
	
	return j;	
}


/*
void intercambiar(int *arr, int i, int j)

Recibe: int *arr, direcci�n del arreglo ptr de memoria din�mica
		int i, posici�n en el arreglo de un n�mero a intercambiar
		int j, posici�n en el arreglo de un n�mero a intercambiar
		
Devuelve: void (No retorna valor explicito)

Observaciones: Haciendo uso de la variable "aux", la funci�n intercambia los
n�meros en la posici�n "i" y "j" del arreglo, asignando a la variable "aux" 
el valor del n�mero en la posici�n "j", despu�s a la posici�n "j" el n�mero
en la posici�n "i" y finalmente a la posici�n "i" el valor de "aux".
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
la �ltima posici�n del arreglo (n-1) y mientras el n�mero en esa posici�n sea menor
o igual al valor buscado, pues de lo contrario significa que el n�mero no se 
encuentra en el arreglo. Cada que se repite el ciclo la variable "comps" aumenta en
1 su valor, pues se ha necesitado de otra comparaci�n para buscar el n�mero.
Finalmente, se coloca en la posici�n 0 del arreglo "resp" la posici�n del n�mero 
buscado (-1 si no existe) y en la posici�n 1 el n�mero de comparaciones que tom�. 
*/
void busLineal(int *arr, int n, int valor, int resp[]){
	
	int res=-1, comps=0;
	
	/*Ciclo iterativo que continua la comparaci�n mientras el indice sea menor o 
	igual al del final del arreglo y el n�mero en esa posici�n sea menor al
	n�mero buscado*/
	for(int i=0;i<=(n-1) && arr[i]<=valor; i++){
	
		//Se aumenta "comps" al haber una comparaci�n
		comps++;
		
		/*Si el n�mero en la posici�n "i" es igual al n�mero buscado entonces "res" 
		toma el valor de "i"*/
		if(arr[i]==valor){
			res=i;
		}
			
	}	
	
	/*Se env�an los valores de la posici�n del n�mero buscado y la cantidad de 
	comparaciones en el indice 0 y 1 del arreglo "resp" respectivamente*/
	resp[0]=res;
	resp[1]=comps;
	
	return;
}
