#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct tarea
{
    int ID;               // Numerado en ciclo iterativo
    char *descripcion;    // Lo que te haga feliz :)
    int duracion;         // Entre 10 y 100
} typedef tarea;

void cargarTareas(tarea **pTareas, int numeroTareas);
void listarTareas(tarea **pListaTareas, int numeroTareas);
void revisarTareas(tarea **pTareas, tarea **pTareasRealizadas, int numeroTareas);
void liberarMemoria(tarea **pTareas, tarea **pTareasRealizadas, int numeroTareas);

void main()
{
    int cantidadTareas;
    tarea **pTareas, **pTareasRealizadas;
    srand(time(NULL));
    printf("============================================================");
    printf("\n=========================BIENVENIDO=========================");
    printf("\n============================================================");
    printf("\n\nIngrese la cantidad de tareas a cargar: ");
    scanf("%i", &cantidadTareas);
    getchar();
    pTareas = (tarea **)malloc(sizeof(tarea *)*cantidadTareas);
    pTareasRealizadas = (tarea **)malloc(sizeof(tarea *)*cantidadTareas);
    cargarTareas(pTareas, cantidadTareas);
    revisarTareas(pTareas, pTareasRealizadas, cantidadTareas);
    printf("\nMostrando tareas Realizadas:\n");
    listarTareas(pTareasRealizadas, cantidadTareas);
    printf("\nMostrando tareas Incompletas:\n");
    listarTareas(pTareas, cantidadTareas);
    liberarMemoria(pTareas, pTareasRealizadas, cantidadTareas);
    printf("\n============================FIN=============================");
}

void cargarTareas(tarea **pTareas, int cantidad)
{
    int indice;
    printf("------------------------------------------------------------");
    printf("\nCargando tareas:\n");
    for (int i = 0; i < cantidad; i++)
    {
        pTareas[i] = (tarea *)malloc(sizeof(tarea));
        char *buffer = (char *)malloc(100*sizeof(char));
        printf("\n-Tarea [%i]:",i+1);
        pTareas[i]->ID = i+1;
        printf("\tIngrese la descripcion:\t");
        gets(buffer);
        pTareas[i]->descripcion = (char *)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(pTareas[i]->descripcion, buffer);
        free(buffer);
        pTareas[i]->duracion = rand()%91+10;
    }
    printf("------------------------------------------------------------");
}

void listarTareas(tarea **pListaTareas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (pListaTareas[i]!=NULL)
        {
            printf("\nTarea [%i]:", i+1);
            printf("\n\tID:\t\t%i", pListaTareas[i]->ID);
            printf("\n\tDescripcion:\t%s", pListaTareas[i]->descripcion);
            printf("\n\tDuracion:\t%i\n", pListaTareas[i]->duracion);
        }
    }
    printf("\n------------------------------------------------------------");
}

void revisarTareas(tarea **pTareas, tarea **pTareasRealizadas, int cantidad)
{
    char realizado;
    printf("\nRevisando tareas:\n");
    for (int i = 0; i < cantidad; i++)
    {
        if (pTareas[i]!=NULL)
        {
            printf("\nTarea [%i]:", i+1);
            printf("\n\tID:\t\t%i", pTareas[i]->ID);
            printf("\n\tDescripcion:\t%s", pTareas[i]->descripcion);
            printf("\n\tDuracion:\t%i", pTareas[i]->duracion);
            printf("\n\tLa tarea fue realizada? (Y/N): ");
            scanf("%c",&realizado);
            getchar();
            if (tolower(realizado)=='y')
            {
                pTareasRealizadas[i] = pTareas[i];
                pTareas[i] = NULL;
            }
            else
            {
                pTareasRealizadas[i] = NULL;
            }
        }
    }
    printf("\n------------------------------------------------------------");
}

void liberarMemoria(tarea **pTareas, tarea **pTareasRealizadas, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        free(pTareas[i]->descripcion);
        free(pTareasRealizadas[i]->descripcion);
    }
    free(*pTareas);
    free(*pTareasRealizadas);
}