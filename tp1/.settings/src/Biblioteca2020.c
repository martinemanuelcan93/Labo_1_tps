#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Biblioteca2020.h"
/* Valida que la cadena este compuesta por letras y que no supere el limite de caracteres disponibles
 * puede determinarse la cantidad de intentos que tiene el usuario
 * retorna <0> si esta todo correcto
 * de lo contrario devuelve -1.
 * */
int getChar(char* cadena,int longitud,char* mensaje,char* msjerror,int intentos)
{
	int retorno=1;
	char buffer[400];
	puts(mensaje);

	if(migets(buffer, longitud)==0
	&&esnumerica(buffer,4096)==0)
	{
	    strcpy(cadena,buffer);
	    retorno=0;
	}
	else
	    puts(msjerror);

	return retorno;
}
int getBinary(int* string,int longitud,char* mensaje,char* msjError,int intentos)
{
 	int retorno=-1;
 	char cadena[4096];
 	if(string!=NULL && longitud>0 && mensaje!=NULL && msjError!=NULL && intentos>0  )
	{
	    do{
 		puts(mensaje);
 		if(migets(cadena,longitud)== 0
		&& isbinary(cadena, longitud)== 1 )
 		{
		    *string = atoi(cadena);
 		    retorno = 0;
 		}
		else
		{
		    printf("%s \nIntentos restantes %d ",msjError,intentos);
		    intentos--;
		}
	    }while(retorno!=0  &&  intentos>=0);
 	}
 	return retorno;
}
/* Valida que lo ingresado sea unicamente un numero
 * si todo esta correcto se devuelve un "0" de lo contrario se muestra un <mensaje de error>
 * con cantidad "n" de reintentos
 * */
int getNro(int* resp,char* mensaje,char* msjError,int minimo,int maximo,int intentos)
{
	int retorno = -1;
	int buffer;
	if (resp!=NULL && mensaje!=NULL && msjError!=NULL && minimo<=maximo && intentos>=0) {
	    do{
		printf("%s",mensaje);
		if(getint(&buffer)==0
		&& buffer>=minimo && buffer<=maximo)
		{
		    *resp=buffer; // "lo que apunta resp"
		    retorno = 0;
		    break;
		}
		else
		{
		    intentos--;
		    printf("Usted ingreso %d",buffer);
		    printf("\n%s",msjError);
		    printf("/// Intentos restantes:%d  \n",intentos);
		}
	    }while(intentos>=0 && retorno==-1);
	}
	return retorno;
}
/*Obtiene un float del teclado retorna 0 si esta todo ok.
 * */
int getfloat(float* resp,char* mensaje,char* msjError,float min,float max,int intentos)
{
	int retorno=-1;
	float bufferFloat;

 	if (resp!=NULL && mensaje!=NULL && msjError!=NULL && min<=max && intentos>=0)
	{
 	do{
		printf("%s",mensaje);
		if(getf(&bufferFloat)==0
		    && bufferFloat>=min && bufferFloat<=max)
		{
		    *resp = bufferFloat;
		    retorno = 0;
		    break;
		}
		else
		{
		    intentos--;//acadeberia entrar si puse letra
		    printf("%s intentos restantes %d ",msjError,intentos);//ERROR ingrese salario valido intentos restantes
		}
	    }while(intentos>=0);
	}
 	return retorno;
}
/* Valida unicamente enteros atravez de "migets" y "esnumerica"
 * */
int getint(int* resp)
{
	int retorno=-1;
	char buffer[4096];
	if(resp!=NULL
	    && migets(buffer,sizeof(buffer))==0
	    && esnumerica(buffer,4096)==1)
	{
	    *resp = atoi(buffer);
	    retorno = 0;
	}
	return retorno;
}
/* Valida que la cadena no desborde el limite establecido para escribir
 * retorna "0" todo ok
 * */
int migets(char* cadena,int longitud)
{
 	char buffer[4096];
 	int retorno=-1;
 	if(cadena!=NULL && longitud>0)
	{
	    fflush(stdout);
	    if(fgets(buffer,sizeof(buffer),stdin)!=NULL) // no desborda nunca
	    {
		if(buffer[strlen(buffer)-1]== '\n')
		{
		    buffer[strlen(buffer)-1]= '\0';
		}
		if(strlen(buffer)<=longitud)
		{
		    strncpy(cadena,buffer,longitud);
		    retorno=0;
		}
	    }
 	}
 	return retorno;
 }
/* Valida que una cadena contenga un caracter numerico
 * en caso de encontrar "-"y "+"continuara por ser negativo o positivo,
 * en caso de encontrar un Char retornara "0"
 * en caso de encontrarlo retornara "1"
 * */
int esnumerica(char* cadena,int limite)
{
 	int retorno = -1;
 	if (cadena !=NULL && limite>0)
	{
 	     retorno = 1;
	     for(int i=0; i<limite && cadena[i] != '\0';i++)
	     {
		if(i==0 && (cadena[i]=='-' || cadena[i]=='+'))
		{
		    continue;
		}
		if(cadena[i] > '9'||cadena[i] < '0')
		{
		    retorno = 0;
		    break;
		}
	      }
 	}
 	return retorno;
 }
/* Si la cadena contiene caracteres '1' o '0' retorna 1
 * De lo contrario retornara [0]
 * */
int isbinary(char* cadena,int longitud)
{
    int retorno=1;
    if(cadena!=NULL&& longitud>0)
    {
	for(int i=0; i<longitud; i++)
	{
	    if(*(cadena+i)!='1' && *(cadena+i)!='0')
	    retorno = 0 ;
	    break;
	}
    }
    return retorno;
}
/* controla que no desborde la cadena y
 * si es en efecto un float
 * */
int getf(float* resultadof)
{
	int retorno=-1;
	char buffer[4096];

	if(resultadof!=NULL
	    && migets(buffer,4096)==0
	    && esfloat(buffer)==1)
	{
	    *resultadof = atof(buffer);
	    retorno = 0;
	}
	return retorno;
}
/* Devuelve 0 cuando hay error
 * */
int esfloat(char* cadena)
{
	int retorno = 1;
	int i=0;
	int contadorPuntos=0;

	if (cadena !=NULL && strlen(cadena)>0)
	{
	     for(  ; cadena[i] != '\0'; i++)
	     {
		if(i==0 && (cadena[i]=='-' || cadena[i]=='+'))
		{
		    continue;
		}
		if(cadena[i]=='.')
		    contadorPuntos++;
		if((cadena[i] > '9'||cadena[i] < '0')
		    &&contadorPuntos>1)
		{
		    retorno = 0;
		    break;
		}
	    }
	}
	return retorno;
}
/* Cambia el primer caracter de una cadena a Mayuscula
 * si existe una mayuscula en otro lugar de la cadena se tornara a Minuscula
 * Ejemplo: "martin >> Martin ; argEntiNA >> Argentina. Basicamente un nombre propio
 * */
void formatoName(char* nombreoapellido)
{
    if(nombreoapellido!=NULL)
    {
	strlwr(nombreoapellido);
	*(nombreoapellido+0) = toupper(*(nombreoapellido+0));
    }
}
void redondeo(char* cadenaflotante,int longitud)
{
    char enganio[2];
    int aux;
    char buffer[5];

    for(int i =0 ; i<longitud; i++)
    {
	if(cadenaflotante[i]=='.' && cadenaflotante[i+1]>'5')
	{
	    enganio[0] = cadenaflotante[i-1]; // guardo caracter
	    aux = atoi(enganio)+1; // convierto en int y le sumo uno
	    sprintf(buffer,"%d",aux);
	    cadenaflotante[i-1] = buffer[0];
	    cadenaflotante[i+1] ='0';
	}
    }
}
/// ARRAYS, ARREGLOS, VECTORES PARALELOS
int ordenarArrayNrico(int Array[],int i,int L,int condicion){
	int j,buffer;

	for(i=0;i<L-1;i++)
	{
	    for(j=i+1;j<L;j++)
	    {
		if(Array[i]>Array[j] && condicion==0) //menor a mayor
		{
		    buffer=Array[i];
		    Array[i]=Array[j];
		    Array[j]=buffer;
		}
		else if(Array[i]<Array[j]&& condicion==1) // mayor a menor
		{
		    buffer=Array[j];
		    Array[j]=Array[i];
		    Array[i]=buffer;
		}
	    }
	}
	return 0;
}
int ingresoTexto(char* texto[60],char* mensaje,int L){
	setbuf(stdout,NULL);

	for(int i=0;i<L;i++)
	{
	    printf("%s",mensaje);
	    fflush(stdin);
	    scanf("%s",texto[i]);
	}
	return 0;
}
int mostrarTexto(char texto[][60],char* mensaje,int L)
{
	int i;
	setbuf(stdout,NULL);
	printf("%s",mensaje);
	for(i=0;i<L;i++)
	{
	    printf("\n%s",texto[i]);
	}
  return 0;

}

