#include "Pacientes.h"
#include "libreriaMPacient.h"
#include "libreriaArchivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


///Iniciar un Arbol
arbolPaciente*inicarbol()
{
    return NULL;
}



///Crear un nuevo nodo raiz de tipo arbol de paciente

arbolPaciente * createPatient(sT_Paciente pers)
{

    arbolPaciente*aux=(arbolPaciente*)malloc(sizeof(arbolPaciente));
    strcpy(aux->pers.AyN,pers.AyN);
    strcpy(aux->pers.Domicilio,pers.Domicilio);
    aux->pers.DNI=pers.DNI;
    aux->pers.Edad=pers.Edad;
    aux->pers.Eliminado=pers.Eliminado;
    strcpy(aux->pers.Telefono,pers.Telefono);

    aux->Der=inicarbol();
    aux->Izq=inicarbol();

    //aux->ingrerso=NULL;

    return aux;
}

///Insertar un nuevo nodo raiz de tipo arbol de paciente

arbolPaciente* getIntoTree (arbolPaciente*tree,sT_Paciente neew)
{
    if(tree==NULL)
    {
        tree=createPatient(neew);
    }
    else
    {

        if(neew.DNI<tree->pers.DNI)
        {
            tree->Izq=getIntoTree(tree->Izq,neew);
        }
        else
        {
            tree->Der=getIntoTree(tree->Der,neew);
        }
    }
    return tree;
}

///Buscar un nodo raiz de tipo arbol de paciente

arbolPaciente * buscar(arbolPaciente*arbol, int dato)
{
    arbolPaciente * buscado =inicarbol();
    if(arbol)
    {
    printf("Flagg");
        if(arbol->pers.DNI==dato)
        {
            buscado=arbol;
        }
        else
        {
            if(dato<arbol->pers.DNI)
            {
                buscado=buscar(arbol->Izq, dato);
            }
            else
            {
                buscado=buscar(arbol->Der,dato);
            }
        }
    }
    return buscado ;
}

///Cambiar estado de paciente

int onOffPatient()
{
    int estado=0;
    char opc;
    printf("Desea eliminar al paciente?");
    fflush(stdin);
    gets(&opc);
    if(opc=='s'||opc=='S')
    {
        estado=1;
    }
    return estado;
}

///Crear un nuevo paciente de tipo paciente

sT_Paciente newPatient()
{
    sT_Paciente aux;
    printf("\nIngrese Apellido y Nombre\n");
    fflush(stdin);
    gets(aux.AyN);
//
//    printf("\nDomicilio: \n");
//    fflush(stdin);
//    gets(&aux.Domicilio);
//
    printf("\nIngrese DNI\n");
    scanf("%d",&aux.DNI);
//
//    printf("\nIngrese Edad\n");
//    scanf("%d", &aux.Edad);
//
//    printf("\nIngrese Telefono de Contacto\n");
//    fflush(stdin);
//    gets(&aux.Telefono);


    aux.Eliminado=0;
    return aux;
}

///Crear un alta de paciente, en un nodo raiz de tipo arbol de paciente

arbolPaciente* alta_de_Paciente(arbolPaciente*tree, char nombrearchivo[])
{
    sT_Paciente aux=newPatient();
    printf("Flagg");
    arbolPaciente*buscado=buscar(tree,aux.DNI);
    if(buscado==NULL)
    {
        tree=getIntoTree(tree,aux);
    }
    else
    {
        char opc;
        printf("Paciente ya ingresado anteriormente\nDesea darlo de alta nuevamente?\n");
        fflush(stdin);
        gets(&opc);
        if(opc=='s'||opc=='S')
        {
            buscado->pers.Eliminado=onOffPatient();
        }
    }
    return tree;
}


arbolPaciente * modificarPaciente (arbolPaciente*tree)
{
    int dato=0;
    printf("Ingrese DNI del paciente a modificar sin puntos\n");
    scanf("%d", &dato);
    arbolPaciente*aux=inicarbol();
    aux=buscar(tree,dato);
    if(aux==NULL)
    {
        printf("No se encontraron pacientes con ese DNI\n");
    }
    else
    {
        printf("Ingrese nuevamente los datos\n");
        aux->pers=newPatient();
    }

    return tree;
}


void mostrarPaciente(arbolPaciente* tree)
{
    printf("Apellido y nombre: %s",tree->pers.AyN);

    printf("Domicilio: %s",tree->pers.Domicilio);
    printf("DNI: %i",tree->pers.DNI);
    printf("Edad: %i",tree->pers.Edad);
    printf("Telefono: %s",tree->pers.Telefono);
    if(tree->pers.Eliminado==0)
        printf("Estado: Activo");
    else
        printf("Estado: Inactivo");

}

void mostrarArbol(arbolPaciente*tree)
{
    if(tree)
    {
        mostrarPaciente(tree);
        mostrarArbol(tree->Izq);
        mostrarArbol(tree->Der);
    }
}

