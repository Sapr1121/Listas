#include <stdio.h>
#include <stdlib.h>


struct estudiantes{
    long codigo;
    long long telefono;
    char nombre[30];
    char direccion[20];
    int estado;

    struct estudiantes *sig;
};

struct estudiantes *cabeza = NULL;
int comprobar(long cod);

void agregar(){
    struct estudiantes *n;
    n = malloc(sizeof(struct estudiantes));
    long cod;

    printf("Ingresa el codigo: ");
    fflush(stdin);
    scanf("%li",&cod);


    if(comprobar(cod)){
        return;
    }

    n->codigo = cod;
    printf("Nombre del estudiante: ");
    fflush(stdin);
    gets(n->nombre);
    printf("Direccion: ");
    fflush(stdin);
    gets(n->direccion);
    printf("Telefono: ");
    fflush(stdin);
    scanf("%lli",&n->telefono);

    if (cabeza == NULL){
        cabeza = n;
        n->sig = NULL;
    }

    struct estudiantes *temp;
    temp = cabeza;

    while(temp->sig != NULL){
        temp = temp->sig;
    }
    temp->sig = n;
    n->sig = NULL;

}


int comprobar(long cod){


    struct estudiantes *temp;
    temp = cabeza;

    while(temp != NULL){

        if(temp->codigo == cod){
            printf("Error ese codigo si esta registrado.\n");
            fflush(stdin);
            getchar();
            return 1;
        }
        printf("%li\n",temp->codigo);
        temp = temp->sig;
    }
    return 0;
}



void imprimir(){
    struct estudiantes *temp;

    temp = cabeza;

    while(temp != NULL){
        printf("Codigo: %li\n",temp->codigo);
        printf("Nombre: %s\n",temp->nombre);
        printf("Direccion : %s\n",temp->direccion);
        printf("Telefono: %lli\n\n\n",temp->telefono);
        temp = temp->sig;

    }
    printf("Todos los estudiantes han sido impresos");
    fflush(stdin);
    getchar();
}



int main(){
    int op;
    do{
        system("cls");
        printf("Menu principal.\n");
        printf("1.Agregar estudiante\n");
        printf("2.Imprimir todo\n");
        printf("Opciones: ");
        fflush(stdin);
        scanf("%i",&op);

        switch(op){
            case 1:
                    system("cls");
                    printf("Agregar estudiante.\n\n");
                    agregar();
                    break;
            case 2:
                    system("cls");
                    printf("Lista de todos los datos de los estudiantes\n\n");
                    imprimir();
                    break;
            case 3:;break;
            default:
                printf("\nError ese opcion no existe.\n");
                break;
        }
    }while(op != 3);

    return 0;
}