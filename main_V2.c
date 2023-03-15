#include <stdio.h>
#include <stdlib.h>


struct dPeriodos{
    int semestre,nMaterias;
    char periodo[10];
    float promedio;
    struct dPeriodos *sig;

};



struct estudiantes{
    long codigo;
    long long telefono;
    char nombre[30];
    char direccion[20];
    int Cperiodo;
    struct dPeriodos *periodos;

    struct estudiantes *sig;
};




int comprobar(long cod,struct estudiantes **cabeza);
void periodo(long cod,struct estudiantes **cabeza);


void agregar(struct estudiantes **cabeza){
    struct estudiantes *n;
    n = malloc(sizeof(struct estudiantes));
    long cod;

    printf("Ingresa el codigo: ");
    fflush(stdin);
    scanf("%li",&cod);


    if(comprobar(cod,cabeza)){
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
    n->Cperiodo = 0;
    n->periodos = NULL;

    if (*cabeza == NULL){
        n->sig = NULL;
        *cabeza = n;


        printf("Se a guardado el estudiante.\n\n");
        printf("Desea anexar el periodo academico (s/n): ");
        fflush(stdin);
        if(getchar() == 's'){
            periodo(cod,cabeza);
        }
        return;
    }

    struct estudiantes *temp;
    temp = *cabeza;

    while(temp->sig != NULL){
        temp = temp->sig;
    }
    temp->sig = n;
    n->sig = NULL;
    printf("Se a guardado el estudiante.\n\n");
    printf("Desea anexar el periodo academico (s/n): ");
    fflush(stdin);
    if(getchar() == 's'){
        periodo(cod,cabeza);
    }

}

int comprobar(long cod,struct estudiantes **cabeza){


    struct estudiantes *temp;
    temp = *cabeza;

    while(temp != NULL){

        if(temp->codigo == cod){
            printf("Error ese codigo si esta registrado.\n");
            fflush(stdin);
            getchar();
            return 1;
        }

        temp = temp->sig;
    }
    return 0;
}




void periodo(long cod,struct estudiantes **cabeza){
    int np;
    struct estudiantes *temp;
    struct dPeriodos *tempPeriodo,*aux;

    temp = *cabeza;

    while(temp!=NULL){
        if(temp->codigo == cod){

            do{
                system("cls");
                tempPeriodo = malloc(sizeof(struct dPeriodos));
                printf("Periodos vistos: %i\n",temp->Cperiodo);
                printf("Ingrese el semestre: ");
                fflush(stdin);
                scanf("%i",&tempPeriodo->semestre);

                printf("Ingrese el periodo: ");
                fflush(stdin);
                gets(tempPeriodo->periodo);

                printf("Ingrese el Numero de materias: ");
                fflush(stdin);
                scanf("%i",&tempPeriodo->nMaterias);

                printf("Ingrese el promedio: ");
                fflush(stdin);scanf("%f",&tempPeriodo->promedio);

                temp->Cperiodo++;

                if(temp->periodos == NULL){
                    temp->periodos = tempPeriodo;
                    tempPeriodo->sig = NULL;
                }else{


                    aux = temp->periodos;
                    while(aux->sig != NULL){
                        aux = aux->sig;
                    }
                    aux->sig = tempPeriodo;
                    tempPeriodo->sig = NULL;

                }


                printf("Quieres continuar anexando periodos? (s/n): ");
                fflush(stdin);
            }while(getchar() == 's');

        }
        temp = temp->sig;
    }


}



float estadoprom(struct dPeriodos *pt,int limit){
    int i;
    float sumaprom = 0;
    while(pt != NULL){

        sumaprom += pt->promedio;
        pt = pt->sig;
    }

    return sumaprom /= limit;

}


void estado(struct estudiantes **cabeza){
    float sumaprom;
    int i;

    struct estudiantes *temp;
    temp = *cabeza;

    while (temp != NULL){

        sumaprom = estadoprom(temp->periodos,temp->Cperiodo);
        if(sumaprom < 2.5){
            printf("Nombre: %s\tPeriodos vistos: %i\tPromedio: %.2f\tEstado: FUERA\n",temp->nombre,temp->Cperiodo,sumaprom);
        }
        if(sumaprom >= 2.5 && sumaprom <= 2.9){
            printf("Nombre: %s\tPeriodos vistos: %i\tPromedio: %.2f\tEstado: PRUEBA\n",temp->nombre,temp->Cperiodo,sumaprom);
        }
        if(sumaprom >= 3.0){
            printf("Nombre: %s\tPeriodos vistos: %i\tPromedio: %.2f\tEstado: NORMAL\n",temp->nombre,temp->Cperiodo,sumaprom);
        }


    temp = temp->sig;
    }
    printf("\nEsos son todos los estados de los estudiantes\n");
    fflush(stdin);
    getchar();

}


void fuera(struct estudiantes **cabeza){
    struct estudiantes *temp;
    struct dPeriodos *temPer;
    temp = *cabeza;
    int i=0;
    while(temp != NULL){
        if(estadoprom(temp->periodos,temp->Cperiodo) < 2.5){
            printf("Codigo: %li\n",temp->codigo);
            printf("Nombre: %s\n",temp->nombre);
            printf("Direccion: %s\n",temp->direccion);
            printf("Telefono: %lli\n",temp->telefono);
            printf("periodos vistos: %i\n",temp->Cperiodo);
            printf("Estado: FUERA\n\n");
            printf("Periodos vistos: \n");
            temPer = temp->periodos;
            while(temPer != NULL){
                printf("Semestre: %i\n",temPer->semestre);
                printf("Periodo: %s\n",temPer->periodo);
                printf("Numero de  materias: %i\n",temPer->nMaterias);
                printf("Promedio: %.2f\n\n",temPer->promedio);
                temPer = temPer->sig;
            }
        }
        temp = temp->sig;
    }
    printf("\nEsos son todos los estudiantes que estan FUERA\n");
    fflush(stdin);
    getchar();
}


void imprimir(struct estudiantes **cabeza){
    struct estudiantes *temp;
    struct dPeriodos *temPer;
    int i;
    temp = *cabeza;

    while(temp != NULL){
        printf("Codigo: %li\n",temp->codigo);
        printf("Nombre: %s\n",temp->nombre);
        printf("Direccion : %s\n",temp->direccion);
        printf("Telefono: %lli\n\n",temp->telefono);
        if(temp->Cperiodo > 0){
            printf("Periodos vistos: \n");
            temPer = temp->periodos;
            while(temPer != NULL){
                printf("Semestre: %i\n",temPer->semestre);
                printf("Periodo: %s\n",temPer->periodo);
                printf("Numero de  materias: %i\n",temPer->nMaterias);
                printf("Promedio: %.2f\n\n",temPer->promedio);
                temPer = temPer->sig;
            }
        }
        printf("\n\n\n");
        temp = temp->sig;

    }
    printf("Todos los estudiantes han sido impresos");
    fflush(stdin);
    getchar();
}



int main(){
    struct estudiantes *cabeza = NULL;
    int op;
    long cod;

    do{
        system("cls");
        printf("Menu principal.\n");
        printf("1.Agregar estudiante.\n");
        printf("2.Anexar periodo academico.\n");
        printf("3.Estados.\n");
        printf("4.Estudiantes Fuera\n");
        printf("5.Imprimir todo\n");
        printf("6.Salir\n");
        printf("Opciones: ");
        fflush(stdin);
        scanf("%i",&op);

        switch(op){
            case 1:
                system("cls");
                printf("Agregar estudiante.\n\n");
                agregar(&cabeza);
                break;

            case 2:
                    system("cls");
                    printf("Anexar periodo.\n\n");
                    printf("Ingresa el codigo del estudiante: ");
                    scanf("%i",&cod);
                    periodo(cod,&cabeza);
                    break;

            case 3:
                    system("cls");
                    printf("Estado de todos los estudiantes \n\n");
                    estado(&cabeza);
                    break;

            case 4:
                    system("cls");
                    printf("Lista de los estudiantes que estan FUERA\n\n");
                    fuera(&cabeza);
                    break;

            case 5:
                system("cls");
                printf("Lista de todos los datos de los estudiantes\n\n");
                imprimir(&cabeza);
                break;

            case 6:;break;
            default:
                printf("\nError ese opcion no existe.\n");
                break;
        }
    }while(op != 6);

    return 0;
}
