#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct tarea
{
    int ID;               // Numerado en ciclo iterativo
    char *descripcion;    // Lo que te haga feliz :)
    int duracion;         // Entre 10 y 100
} typedef tarea;

struct nodo
{
    tarea t;
    struct nodo *siguiente;
} typedef nodo;

nodo *crearLista();
nodo *crearNodo();
void cargarTareas(nodo **pListaDeTareas);
void enlazarNodoAlFinal(nodo **pListaDeTareas, nodo *pNodoACargar);
void mostrarTarea(nodo **pNodoTarea);
void listarTareas(nodo **pListaTareas);
void revisarTareas(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas);
void saltarNodo(nodo **pListaDeTareas, nodo *pNodoASaltar);
void liberarNodo(nodo *pNodoALiberar);
void buscarTareaPorID(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas);
bool buscarIDEnLista(nodo **pListaDeTareas, int IDBuscado);
void buscarTareaPorPalabra(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas);
bool buscarPalabraEnLista(nodo **pListaDeTareas, char *PalabraBuscada);
void liberarMemoria(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas);

void main()
{
    srand(time(NULL));
    int cantidadTareas;
    nodo *pListaDeTareas = crearLista();
    nodo *pListaDeTareasRealizadas = crearLista();
    printf("============================================================");
    printf("\n=========================BIENVENIDO=========================");
    printf("\n============================================================");
    cargarTareas(&pListaDeTareas);
    printf("\nListado de Tareas:\n");
    listarTareas(&pListaDeTareas);
    revisarTareas(&pListaDeTareas, &pListaDeTareasRealizadas);
    printf("\nMostrando tareas Realizadas:\n");
    listarTareas(&pListaDeTareasRealizadas);
    printf("\nMostrando tareas Incompletas:\n");
    listarTareas(&pListaDeTareas);
    buscarTareaPorID(&pListaDeTareas, &pListaDeTareasRealizadas);
    buscarTareaPorPalabra(&pListaDeTareas, &pListaDeTareasRealizadas);
    printf("\nLiberando memoria...");
    liberarMemoria(&pListaDeTareas, &pListaDeTareasRealizadas);
    printf("\nMemoria liberada");
    printf("\n============================FIN=============================");
}

nodo *crearLista()
{
    return NULL;
}

nodo *crearNodo()
{
    nodo *pNuevoNodo = (nodo *)malloc(sizeof(nodo));
    pNuevoNodo->siguiente = NULL;
    return pNuevoNodo;
}

void cargarTareas(nodo **pListaDeTareas)
{
    int ID=0;
    char pregunta;
    nodo *pNodoI;
    printf("\nCargando tareas:\n");
    do
    {
        ID++;
        pNodoI = crearNodo();
        printf("\n-Tarea [%i]:", ID);
        pNodoI->t.ID = ID;
        printf("\n\tIngrese la descripcion:\t\t");
        char *buffer = (char *)malloc(100*sizeof(char));
        gets(buffer);
        pNodoI->t.descripcion = (char *)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(pNodoI->t.descripcion, buffer);
        free(buffer);
        pNodoI->t.duracion = rand()%91+10;
        enlazarNodoAlFinal(pListaDeTareas, pNodoI);
        printf("\tDesea cargar otra tarea? (Y/N):\t");
        scanf("%c",&pregunta);
        fflush(stdin);
    } while (tolower(pregunta)=='y');
    printf("\n------------------------------------------------------------");
}

void enlazarNodoAlFinal(nodo **pListaDeTareas, nodo *pNodoACargar)
{
    nodo *pNodoAuxiliar = *pListaDeTareas;
    if (pNodoAuxiliar==NULL) // si la lista está vacía lo inserto primero
    {
        *pListaDeTareas = pNodoACargar;
    }
    else
    {
        while (pNodoAuxiliar->siguiente!=NULL)
        {
            pNodoAuxiliar = pNodoAuxiliar->siguiente;
        }
        pNodoAuxiliar->siguiente = pNodoACargar;
    }
}

void mostrarTarea(nodo **pNodoTarea)
{
        printf("\nTarea [%i]:", (*pNodoTarea)->t.ID);
        printf("\n\tID:\t\t%i", (*pNodoTarea)->t.ID);
        printf("\n\tDescripcion:\t%s", (*pNodoTarea)->t.descripcion);
        printf("\n\tDuracion:\t%i\n", (*pNodoTarea)->t.duracion);
}

void listarTareas(nodo **pListaDeTareas)
{
    nodo *pNodoAuxiliar = *pListaDeTareas;
    if (pNodoAuxiliar==NULL)
    {
        printf("\nLa lista está vacía.");
    }
    else
    {
        while (pNodoAuxiliar!=NULL)
        {
            mostrarTarea(&pNodoAuxiliar);
            pNodoAuxiliar = pNodoAuxiliar->siguiente;
        }
    }
    printf("\n------------------------------------------------------------");
}

void revisarTareas(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas)
{
    char realizado;
    nodo *pNodoAuxiliar = *pListaDeTareas;
    printf("\nRevisando tareas:\n");
    while (pNodoAuxiliar!=NULL)
    {
        mostrarTarea(&pNodoAuxiliar);
        printf("\n\tLa tarea fue realizada? (Y/N): ");
        scanf("%c",&realizado);
        fflush(stdin);
        if (tolower(realizado)=='y')
        {
            nodo *pNodoAuxiliarSiguiente = pNodoAuxiliar->siguiente;
            saltarNodo(pListaDeTareas, pNodoAuxiliar);
            enlazarNodoAlFinal(pListaDeTareasRealizadas, pNodoAuxiliar);
            pNodoAuxiliar->siguiente=NULL;
            pNodoAuxiliar=pNodoAuxiliarSiguiente;
        }
        else
        {
            pNodoAuxiliar = pNodoAuxiliar->siguiente;
        }
    }
    printf("\n------------------------------------------------------------");
}

void saltarNodo(nodo **pListaDeTareas, nodo *pNodoASaltar)
{
    nodo *pNodoActual = *pListaDeTareas;
    if ((*pListaDeTareas)->t.ID==pNodoASaltar->t.ID) // Si el nodo a saltar es el primero
    {
        *pListaDeTareas = (*pListaDeTareas)->siguiente;
    }
    else // Si no recorro la lista hasta encontrar el que quiero saltar
    {
        nodo *pNodoAnterior = *pListaDeTareas;
        while (pNodoActual!=NULL && pNodoActual->t.ID!=pNodoASaltar->t.ID)
        {
            pNodoAnterior = pNodoActual;
            pNodoActual = pNodoActual->siguiente;
        }
        if (pNodoActual!=NULL)
        {
            pNodoAnterior->siguiente = pNodoActual->siguiente;
        }
    }
}

void liberarNodo(nodo *pNodoALiberar)
{
    if (pNodoALiberar!=NULL)
    {
        free(pNodoALiberar);
    }
}

void buscarTareaPorID(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas)
{
    int IDBuscado, encontrado=0;
    printf("\nBuscar Tarea por ID:");
    printf("\n\tID a buscar: ");
    scanf("%i",&IDBuscado);
    fflush(stdin);
    if (buscarIDEnLista(pListaDeTareas, IDBuscado))
    {
        printf("\tEstado:\t\tIncompleta\n");
    }
    else
    {
        if (buscarIDEnLista(pListaDeTareasRealizadas, IDBuscado))
        {
            printf("\tEstado:\t\tCompleta\n");
        }
        else
        {
            printf("\nNo se encontro la tarea con el ID buscado.\n");
        }
    }
    printf("\n------------------------------------------------------------");
}

bool buscarIDEnLista(nodo **pListaDeTareas, int IDBuscado)
{
    nodo *pNodoAuxiliar = *pListaDeTareas;
    while (pNodoAuxiliar!=NULL && pNodoAuxiliar->t.ID!=IDBuscado)
    {
        pNodoAuxiliar= pNodoAuxiliar->siguiente;
    }
    if (pNodoAuxiliar!=NULL)
    {
        mostrarTarea(&pNodoAuxiliar);
        return true;
    }
    else
    {
        return false;
    }
}

void buscarTareaPorPalabra(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas)
{
    printf("\nBuscar Tarea por Palabra:");
    printf("\n\tPalabra a buscar: ");
    char *buffer = (char *)malloc(15*sizeof(char));
    gets(buffer);
    if (buscarPalabraEnLista(pListaDeTareas, buffer))
    {
        printf("\tEstado:\t\tIncompleta\n");
    }
    else
    {
        if (buscarPalabraEnLista(pListaDeTareasRealizadas, buffer))
        {
            printf("\tEstado:\t\tCompleta\n");
        }
        else
        {
            printf("\nNo se encontro la tarea con la palabra buscada.\n");
        }
    }
    free(buffer);
    printf("\n------------------------------------------------------------");
}


bool buscarPalabraEnLista(nodo **pListaDeTareas, char *PalabraBuscada)
{
    nodo *pNodoAuxiliar = *pListaDeTareas;
    while (pNodoAuxiliar!=NULL && !strstr((*pNodoAuxiliar).t.descripcion, PalabraBuscada))
    {
        pNodoAuxiliar=pNodoAuxiliar->siguiente;
    }
    if (pNodoAuxiliar!=NULL)
    {
        mostrarTarea(&pNodoAuxiliar);
        return true;
    }
    else
    {
        return false;
    }
}

void liberarMemoria(nodo **pListaDeTareas, nodo **pListaDeTareasRealizadas)
{
    free(*pListaDeTareas);
    free(*pListaDeTareasRealizadas);
}
