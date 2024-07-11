#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int edad;
    char matricula[20];
} Alumno;

void
grabarAlumnos(const char *nombreArchivo, Alumno *alumnos, int cantidad) {
FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para escribir");
        exit(EXIT_FAILURE);
    }
    fwrite(alumnos, sizeof(Alumno), cantidad, archivo);
    fclose(archivo);
}

Alumno* leerAlumnos(const char *nombreArchivo, int *cantidad) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para leer");
        exit(EXIT_FAILURE);
    }

    fseek(archivo, 0, SEEK_END);
    long fileSize = ftell(archivo);
    rewind(archivo);
    *cantidad = fileSize / sizeof(Alumno);

    Alumno *alumnos = (Alumno *)malloc(fileSize);
    if (alumnos == NULL) {
        perror("Error al reservar memoria");
        exit(EXIT_FAILURE);
    }

    fread(alumnos, sizeof(Alumno), *cantidad, archivo);
    fclose(archivo);

    return alumnos;
}

void ingresarAlumno(Alumno *alumno) {
    printf("Ingrese el nombre del alumno: ");
    fgets(alumno->nombre, 50, stdin);
    alumno->nombre[strcspn(alumno->nombre, "\n")] = '\0';
    printf("Ingrese la edad del alumno: ");
    scanf("%d", &alumno->edad);
    getchar();

    printf("Ingrese la matrícula del alumno: ");
    fgets(alumno->matricula, 20, stdin);
    alumno->matricula[strcspn(alumno->matricula, "\n")] = '\0';


void imprimirAlumno(const Alumno *alumno) {
    printf("Nombre: %s\n", alumno->nombre);
    printf("Edad: %d\n", alumno->edad);
    printf("Matrícula: %s\n", alumno->matricula);
}

int main() {
    Alumno *alumnos = NULL;
    int cantidad = 0;
    int opcion;
    const char *nombreArchivo = "alumnos.dat";

    do {
        printf("Menu:\n");
        printf("1. Grabar datos de alumnos\n");
        printf("2. Leer datos de alumnos\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();
        switch(opcion) {
            case 1: {
                do {

alumnos = (Alumno *)realloc(alumnos, (cantidad + 1) * sizeof(Alumno));
  if (alumnos == NULL) {
    perror("Error al reservar memoria");
     exit(EXIT_FAILURE);
                    }

ingresarAlumno(&alumnos[cantidad]);
 cantidad++;
printf("¿Desea ingresar otro registro? (s/n): ");

} while (getchar() == 's');
    getchar();

grabarAlumnos(nombreArchivo, alumnos, cantidad);
free(alumnos);
alumnos = NULL;
cantidad = 0;
 break;
        }
case 2: {

 alumnos = leerAlumnos(nombreArchivo, &cantidad);

for (int i = 0; i < cantidad; i++) {
imprimirAlumno(&alumnos[i]);
printf("\n");
    }

free(alumnos);
alumnos = NULL;
cantidad = 0;
    break;
}

case 3:
printf("Saliendo...\n");
    break;

default:
printf("Opción no válida. Intente de nuevo.\n");
    break;
 }

} w hile (opcion != 3);

    return 0;
}

