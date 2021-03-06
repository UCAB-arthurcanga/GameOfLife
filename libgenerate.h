//
// Source code de generación celular
// Arturo Canga. V-25.696.222
// Luis Fernandez. V-28.002.235
// Para AyPII. Primer proyecto. Creado el 14/6/20
//

void checkplana(int **matrix, int **aux, int n, int m, int x, int y);

void checkvertical(int **matrix, int **aux, int n, int m, int x, int y);

void checkhorizontal(int **matrix, int **aux, int n, int m, int x, int y);

void clone(int **a, int **b, int x, int y);

void automatePlana(int **matriz, int x, int y);

void automateVert(int **matriz, int x, int y);

void automateHorz(int **matriz, int x, int y);
