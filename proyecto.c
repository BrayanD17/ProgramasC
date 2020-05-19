#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <regex.h>
#include <stdbool.h>
#define MAX_MATCHES 1
typedef enum {casa,movil}Tipo;
struct nodoTelefono{
	char telefono[100];
	Tipo tipo;
	struct nodoTelefono* sig;
}*primerTelefono;
bool verificar = false;
void insertarTelefono(char *telef, Tipo tipo)
{
	
	struct nodoTelefono* nuevoTelefono = (struct nodoTelefono*) malloc(sizeof(struct nodoTelefono));
	strcpy(nuevoTelefono -> telefono, telef);
	nuevoTelefono -> tipo = tipo;
	nuevoTelefono -> sig = NULL;
	if(primerTelefono == NULL)
	{
		primerTelefono = nuevoTelefono;
	}
	else
	{
		nuevoTelefono -> sig = primerTelefono;
		primerTelefono = nuevoTelefono;
	}
		
}
void imprimirTelefonos()
{
	
	while(primerTelefono != NULL)
	{
		if(primerTelefono -> tipo == casa){
			printf("Telefono residencial: %s\n",primerTelefono -> telefono);

		}
		if(primerTelefono -> tipo == movil){
			printf("Telefono movil: %s\n",primerTelefono -> telefono);
		}
		primerTelefono = primerTelefono -> sig;
	}
	
	
}
/*se encarga de comparar las palabras del texto con alguna expresion regular*/
void match(regex_t *pexp, char *dato) 
{
	regmatch_t matches[MAX_MATCHES];
	if (regexec(pexp, dato, MAX_MATCHES, matches, 0) == 0) {
		verificar = true;
	}
}
/**/
void clasificador()
{
	/*Variables encargadas de encontrar algun numero telefonico en el texto*/
	int expresion1;
	int expresion2;
	int expresion3;
	int expresion4;
	int expresion5;
	int expresion6;
	regex_t exp;
	/*Variables encargadas del manejo de archivos*/
	char ruta [200];
	char caracter[2]="";
	char palabra[100]="";
	
	printf("Ingrese la ruta del archivo que desea analizar: ");
	scanf("%s",ruta);
	FILE * archivo = fopen (ruta,"r");
	/*
	*/
	
	if (archivo == NULL){
		printf("\nError en la apertura del documento de texto!!");
	}
	else{
		
		while (feof(archivo) == 0)
		{
			fgets(caracter,2,archivo);
			if(isspace(caracter[0])){
				
				/*----- residencial -----*/
	
				/*primer carso*/
				expresion1 = regcomp(&exp, "2[0-9]{7}", REG_EXTENDED);
				if (expresion1 != 0) {
					printf("Fallo %d\n", expresion1);
				}
				else
				{
					match(&exp, palabra);
					if(verificar)
					{
						insertarTelefono(palabra,casa);
					}
					verificar = false;
				}
				
				/*segundo caso*/
				expresion2 = regcomp(&exp, "2[0-9]{3}-[0-9]{4}", REG_EXTENDED);
				if (expresion2 != 0) {
					printf("Fallo %d\n", expresion2);
				}
				else
				{
					match(&exp, palabra);
					if(verificar)
					{
						insertarTelefono(palabra,casa);
					}
					verificar = false;
				}
				/*tercero caso*/
				expresion3 = regcomp(&exp, "2[0-9]-[0-9]{2}-[0-9]{2}-[0-9]{2}", REG_EXTENDED);
				if (expresion3 != 0) {
					printf("Fallo %d\n", expresion3);
				}
				else
				{
					match(&exp, palabra);
					if(verificar)
					{
						insertarTelefono(palabra,casa);
					}
					verificar = false;
				}

				/*----- Telefono celular -----*/
				/*cuarto caso*/
				expresion4 = regcomp(&exp, "[5-8][0-9]-[0-9]{2}-[0-9]{2}-[0-9]{2}", REG_EXTENDED);
				if (expresion4 != 0) {
					printf("Fallo %d\n", expresion4);
				}
				else
				{
					match(&exp, palabra);
					if(verificar)
					{
						insertarTelefono(palabra,movil);
					}
					verificar = false;
				}
				/*quinto caso*/
				expresion5 = regcomp(&exp, "[5-8][0-9]{3}-[0-9]{4}", REG_EXTENDED);
				if (expresion5 != 0) {
					printf("Fallo %d\n", expresion5);
				}
				else
				{
					match(&exp, palabra);
					if(verificar)
					{
						insertarTelefono(palabra,movil);
					}
					verificar = false;
				}
				/*sexto caso*/
				expresion6 = regcomp(&exp, "[5-8][0-9]{7}", REG_EXTENDED);
				if (expresion6 != 0) {
					printf("Fallo %d\n", expresion6);
				}
				else
				{
					match(&exp, palabra);
					if(verificar)
					{
						insertarTelefono(palabra,movil);
					}
					verificar = false;
				}
				regfree(&exp);
				
				int i = 0;
				while (i <100){
					palabra[i]=0;
					i = i + 1;
				}
				
			}
			else{
				strcat(palabra,caracter);
				
			}
		}
		system("PAUSE");
	}
}
	
int main(){
	clasificador();
	imprimirTelefonos();
	printf("\nFin del programa\n");
	return 0;
}