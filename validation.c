//
// Por Arturo Canga. V-25.696.222
// Para AyPII, creado el 7/6/20
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Lee el archivo y extrae su contenido en una cadena
char *lectura(char *name){
    char dir[FILENAME_MAX];
    getcwd(dir,FILENAME_MAX);
    char fulldir[FILENAME_MAX]="\0";
    strcat(fulldir,dir);
    strcat(fulldir,"/");
    strcat(fulldir,name);
    FILE *archivo=fopen(fulldir,"r");
    if (!archivo){
        fprintf(stderr,"Error de apertura. El archivo no existe");
        exit(0);
    }
    char *content= (char *)malloc(FILENAME_MAX * sizeof(char));
    char buff[FILENAME_MAX];
    fgets(buff,FILENAME_MAX,archivo);
    while(!feof(archivo)){
        strcat(content,buff);
        fgets(buff,FILENAME_MAX,archivo);
    }
    return content;
}


//Elimina los espacios y saltos de linea
void eliminarespacios(char *s){
    const char* d = s;
    do {
        while (*d == ' ' || *d == '\n') {
            ++d;
        }
    } while ((*s++ = *d++));
}

//Verifica que cada caracter de la cadena sea valido y que los corchetes esten balanceados
int balanceyvalores(const char *s){
    int corch=0;
    while(*s!='\0'){
        if(*s=='{')
            corch++;
        if (*s=='}')
            corch--;
        if(*s!='0' && *s!='1' && *s!=',' && *s!='{' && *s!='}')
            return 0;
        s++;
    }
    if(corch)
        return 0;
    else return 1;
}

//Halla el ultimo elemento del arreglo. Usado para la funcion check
int limiter(const char array[]){
    int i=0;
    for (; array[i] ; i++);
    return i;
}

//Chequea que la fila sea valida

int check(const char array[], int limit){
    int dim=0;
    int dimaux=0;
    int i=2;

    //Chequeo de apertura
    if(array[0]!='{' && array[1]!='{')
        return 0;
    if(array[2]!='0' && array[2]!='1')
        return 0;
    if(array[limit-1]!='}' && array[limit-2]!='}')
        return 0;

    //Chequeo de primera fila y calculo de dimension
    for (; array[i]!='}' ; i++) {
        if ((array[i]=='0' || array[i]=='1') && (array[i+1]!=',' && array[i+1]!='}')){
            printf("Error encontrado en posicion %d. Valor invalido\n", i);
            return 0;
        }
        if(array[i]==','){
            dim++;
            if((array[i-1]!='0' && array[i-1]!='1') && (array[i+1]!='0' && array[i+1]!='1')){
                printf("Error encontrado en posicion %d\n",i);
                return 0;
            }
        }
    }
    while(i!=limit){
        //Luego de la primera fila, debe ir una comma
        if(array[i]==','){
            //Si es una coma, aumentamos el contador
            i++;
            //Empezamos a leer el siguiente arreglo
            for ( ; array[i]!='}' ; i++) {
                //Si estoy en un numero y el siguiente no es coma o cierre de corchete...
                if ((array[i]=='0' || array[i]=='1') && (array[i+1]!=',' && array[i+1]!='}')) {
                    printf("Error encontrado en posicion %d. Valor invalido\n", i);
                    return 0;
                }
                //Si la posicion es una coma...
                if(array[i]==','){
                    //Contado auxiliar aumenta
                    dimaux++;
                    //Verificamos que la estructura sea valida y sino return 0
                    if((array[i-1]!='0' && array[i-1]!='1') && (array[i+1]!='0' && array[i+1]!='1')){
                        printf("Error encontrado en posicion %d\n",i);
                        return 0;
                    }
                }
            }
            //Si la dimension del arreglo es distinta a la del primero return 0
            if (dimaux!=dim){
                printf("Error. Dimensiones incorrectas\n");
                return 0;
            }
        }
        //Aumentamos 1 porque caimos en un '}'
        i++;
        dimaux=0;
    }
    return 1;
}

//Obtiene la dimensión en Y (cantidad de filas)
int getdimY(const char *s){
    int dim=0;
    for (int i = 0; s[i] ; i++) {
        if (s[i]==',' && (s[i-1]=='}' && s[i+1]=='{'))
            dim++;
    }
    return dim+1;
}

//Obtiene la dimensión en X (casillas de arreglo individual)
int getdimX(const char *s){
    int dim=0;
    for (int i = 0; s[i]!='}' ; i++) {
        if (s[i]==',' && (s[i+1]=='0' || s[i+1]=='1'))
            dim++;
    }
    return dim+1;
}

int **generatematrix(char *string, int *X, int *Y){
    *X=getdimX(string);
    *Y=getdimY(string);
    //Reservamos espacio
    int **matrix=(int **)malloc(*Y*sizeof(int*));
    for (int a = 0; a < *Y; a++) {
        matrix[a]=(int *)malloc(*X*sizeof(int));
    }
    int j;
    int s=0;
    //for recorre en Y el arreglo
    for (int i = 0; i < *Y; i++) {
        //Inicializa el contador para recorrer en X
        j=0;
        //for recorre la cadena, variable declarada para guardar el valor
        for (; string[s]!='}'; s++) {
            //Guarda valor si es un 0 o 1. Resta 48 porque obtiene el valor ASCII
            if (string[s]=='0' || string[s]=='1'){
                matrix[i][j]=string[s]-48;
                j++;
            }
        }
        s++;
    }
    return matrix;
}

//Resume el proceso de obtencion de la cadena y de la validacion
char *obtainer(char *s){
    char *fullcontent;
    fullcontent=lectura(s);
    eliminarespacios(fullcontent);
    if (balanceyvalores(fullcontent)){
        int i=limiter(fullcontent);
        if (!check(fullcontent,i)){
            fprintf(stderr,"Formato invalido. Programa finalizado");
            exit(0);
        }
    } else {
        fprintf(stderr,"Formato invalido. Incongruencia de corchetes o caracteres invalidos.\nPrograma finalizado");
        exit(0);
    }
    return fullcontent;
}