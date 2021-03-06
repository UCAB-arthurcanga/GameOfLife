//
// Source code de visualización
// Arturo Canga. V-25.696.222
// Luis Fernández. V-28.002.235
// Para AyPII. Primer Proyecto. Creado el 13/6/20
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libgenerate.h"

//Escritura de archivo
void printinfile(FILE *file, int **matrix, int x, int y){
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (!matrix[i][j])
                fprintf(file,"_");
            else fprintf(file,"0");
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n\n");
}

//Impresión en pantalla
void printinscreen(int **matrix1, int **matrix2, int **matrix3, int x, int y){
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (!matrix1[i][j])
                printf("_");
            else printf("0");
        }
        if (y<12){
            int spaces=12-y;
            for (int j = 0; j < spaces; j++) {
                printf(" ");
            }
        }
        printf("     ");
        for (int j = 0; j < y; j++) {
            if (!matrix2[i][j])
                printf("_");
            else printf("0");
        }
        if (y<11){
            int spaces=11-y;
            for (int j = 0; j < spaces; j++) {
                printf(" ");
            }
        }
        printf("     ");
        for (int j = 0; j < y; j++) {
            if (!matrix3[i][j])
                printf("_");
            else printf("0");
        }
        printf("\n");
    }
}



//Sistema de iteración
void show(char *ogfile, int ogsize, int **plana, int **vertical, int **horizontal, const int x, const int y, int time, int iter){
    FILE *planafile, *verticalfile, *horizontalfile;
    char *plananame=(char *)malloc((18+ogsize)*sizeof(char));
    char *verticalname=(char *)malloc((21+ogsize)*sizeof(char));
    char *horizontalname=(char *)malloc((23+ogsize)*sizeof(char));
    strcpy(plananame,"output-plana-");
    strcpy(verticalname,"output-vertical-");
    strcpy(horizontalname,"output-horizontal-");
    strcat(plananame,ogfile);
    strcat(verticalname,ogfile);
    strcat(horizontalname,ogfile);
    strcat(plananame,".txt");
    strcat(verticalname,".txt");
    strcat(horizontalname,".txt");
    planafile = fopen(plananame,"w");
    verticalfile = fopen(verticalname,"w");
    horizontalfile = fopen(horizontalname,"w");
    free(plananame);
    free(verticalname);
    free(horizontalname);
    printf("\e[1;1H\e[2J");
    //Aqui luego hago el llamado a la funcion para la iteracion 0, aka estado inicial
    for (int i = -1; i < iter; i++) {

        //Llamada de limpiado de pantalla. NOTA: CLION NO LO INTERPRETA, EL TERMINAL SI. NO FUNCIONA EN WINDOWS
        printf("\e[1;1H\e[2J");
        if (i>-1) {
            fprintf(planafile, "Iteracion %d\n", i + 1);
            fprintf(verticalfile, "Iteracion %d\n", i + 1);
            fprintf(horizontalfile, "Iteracion %d\n", i + 1);
            printf("Iteración %d\n", i+1);
            printf("\n");

        }
        else{
            printf("Iteracion 0 (iteración inicial)\n");
            printf("\n");
            fprintf(planafile,"Iteracion 0 (iteración inicial)\n");
            fprintf(planafile,"\n");
            fprintf(verticalfile,"Iteracion 0 (iteración inicial)\n");
            fprintf(verticalfile,"\n");
            fprintf(horizontalfile,"Iteracion 0 (iteración inicial)\n");
            fprintf(horizontalfile,"\n");
        }
        //Imprimimos los títulos con los espacios respectivos
        printf("MATRIZ PLANA");
        if (y>12){
            int spaces=12-y;
            for (int j = 0; j < spaces ; j++) {
                printf(" ");
            }
        }
        printf("     ");
        printf("C. VERTICAL");
        if (y>11){
            int spaces=11-y;
            for (int j = 0; j < spaces; j++) {
                printf(" ");
            }
        }
        printf("     ");
        printf("C. HORIZONTAL\n");
        if (i>-1){
            //Aquí se supone que hacemos los llamados a las 3 funciones generadoras para luego mostrar en pantalla
            automatePlana(plana,x,y);
            automateVert(vertical,x,y);
            automateHorz(horizontal,x,y);
            //Primero escribimos en los archivos
            printinfile(planafile,plana,x,y);
            printinfile(verticalfile,vertical,x,y);
            printinfile(horizontalfile,horizontal,x,y);
        }
        //Ahora se imprime en pantalla, uno al lado del otro
        printinscreen(plana,vertical,horizontal,x,y);
        usleep(time*1000);
    }
    fclose(planafile);
    fclose(verticalfile);
    fclose(horizontalfile);
    free(plana);
    free(vertical);
    free(horizontal);
}
