#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct _List
{
    int32_t *Data; // Data es un array
    size_t Capacity; // Cantidad de elemento de Data
    size_t Size; // Cuántos bloques de memoria asignados o ocupados
};

typedef struct _List List, *ListPointer;

ListPointer ListNew();
void ListAdd(ListPointer, int32_t);
void ListDestroy(ListPointer);
void Elements(ListPointer);
size_t ListSize(ListPointer);
void ListSet(ListPointer, int32_t, int32_t);
int32_t* ListGet(ListPointer, int32_t);
void ListRemoveAt(ListPointer, int32_t);
void ListRemove(ListPointer, int32_t);
void ListRemoveIf(ListPointer, int32_t);
int32_t Menu();

int32_t main(const int32_t argc, char const * agrv[])
{
    int32_t option = 0, value = 0, index = 0;
    char answer;

    ListPointer list = ListNew();

    do
    {
        switch (option = Menu())
        {
            case 1:
                printf("\n Enter a value: ");
                scanf("%d", &value);
                ListAdd(list, value);
                break;
            case 2:
                if (list->Size == 0)
                {
                    printf(" Empty array\n");
                }
                else
                {
                    Elements(list);
                }
                break;
            case 3:
                if (list->Size == 0)
                {
                    printf(" Empty array\n");
                }
                else
                {
                    printf("\n Enter the position: ");
                    scanf("%d", &index);
                    ListRemoveAt(list, index);
                }
                break;
            case 4:
                if (list->Size == 0)
                {
                    printf(" Empty array\n");
                }
                else
                {
                    printf("\n Enter a new value and position: ");
                    scanf("%d %d", &value, &index);
                    ListSet(list, index, value);
                }
                break;
            case 5:
                if (list->Size == 0)
                {
                    printf(" Empty array\n");
                }
                else
                {
                    printf("\n Enter the value to remove: ");
                    scanf("%d", &value);
                    ListRemove(list, value);
                }
                break;
            case 6:
                if (list->Size == 0)
                {
                    printf(" Empty array\n");
                }
                else
                {
                    printf("\n Enter the value to remove: ");
                    scanf("%d", &value);
                    ListRemoveIf(list, value);
                }
                break;
            case 7:
                printf("\n Good bye\n");
                break;
        }
    } while (option >= 1 && option < 7);

    ListDestroy(list);

    return EXIT_SUCCESS;
}

int32_t Menu()
{
    int32_t option = 0;

    do
    {
        printf("\t Menu \n\n");
        printf(" 1. Insert\n");
        printf(" 2. See elements\n");
        printf(" 3. Delete At\n");
        printf(" 4. Update\n");
        printf(" 5. Delete By Value\n");
        printf(" 6. Delete All element with that Value\n");
        printf(" 7. Exit\n");

        printf("\n Enter your choice: ");
        scanf("%d", &option);

        if (option < 1 || option > 7)
        {
            printf("\n Enter a correct option. Enter again\n");
            getchar(); // TODO: Crear una función para pause
        }
        system("clear");
    } while (option < 1 || option > 7);

    return option;
}

void Elements(ListPointer list_pointer)
{
    printf("\n\t Elements \n");
    for (size_t index = 0; index < ListSize(list_pointer); ++index)
    {
        printf("[%lu]: %d\n", index, *ListGet(list_pointer, index));
    }
    printf("\n");
}

ListPointer ListNew()
{
    ListPointer list = NULL;
    list = malloc(sizeof(List));

    //Incializando en Cero las variables
    list->Capacity = 4;
    list->Data = NULL;
    list->Size = 0;

    //Dando capacidad por defecto
    // (int32_t*)malloc(list->Capacity * sizeof(int32_t)) Me retorna el array de enteros
    //    Array                           Tamaño de un int

    //(int32_t*)malloc(list->Capacity * sizeof(int32_t*)) -> Está retornando un array de punteros de enteros

    list->Data = (int32_t*)malloc(list->Capacity * sizeof(int32_t));

    return list;
}

void ListAdd(ListPointer list_pointer, int32_t value)
{
    printf(" Capacidad: %lu", list_pointer->Capacity);
    printf(" Size: %lu", list_pointer->Size);
    // Validación
    if (list_pointer->Capacity == list_pointer->Size)
    {
        printf("\n Full capacity\n");
        int32_t new_capacity = (list_pointer->Capacity) * 2;
        int32_t *aux = NULL;

        aux = (int32_t*)malloc(new_capacity * sizeof(int32_t));

        for (size_t i = 0; i < list_pointer->Size; ++i)
        {
            aux[i] = list_pointer->Data[i];
        }

        free(list_pointer->Data);

        list_pointer->Data = aux;

        list_pointer->Capacity = new_capacity;
    }

    list_pointer->Data[list_pointer->Size] = value;
    list_pointer->Size += 1;

    printf(" Size: %lu\n\n", list_pointer->Size);
}

size_t ListSize(ListPointer list_pointer)
{
    return list_pointer->Size;
}

void ListDestroy(ListPointer list_pointer)
{
    printf("\n Destroying object\n");
    free(list_pointer->Data);
    free(list_pointer);
}

void ListSet(ListPointer list_pointer, int32_t index, int32_t value)
{
    if ((index >= 0 ) && (index < list_pointer->Size))
    {
        printf("\n Indice [%d] encontrado. Valor Actualizado\n", index);
        *(list_pointer->Data + index) = value;
    }
    else
    {
        printf("\n Indice [%d] no encontrado. Valor no actualizado\n", index);
    }
}

int32_t* ListGet(ListPointer list_pointer, int32_t index)
{       // >= 0 < Size
    if ((index >= 0) && (index < list_pointer->Size))
    {
        // También se puede &(list_pointer->Data[index])
        return (list_pointer->Data + index);
    }

    return NULL;
}

void ListRemoveAt(ListPointer list_pointer, int32_t index)
{
    if ((index >= 0) && (index < list_pointer->Size))
    {
        printf("\n Indice [%d] encontrado. Borrando\n", index);
        printf(" Capacidad: %lu", list_pointer->Capacity);
        printf(" Size: %lu", list_pointer->Size);

        // int32_t *aux = NULL, i = 0;
        // int32_t new_capacity = list_pointer->Capacity - 1;
        int32_t i = 0;

        // aux = (int32_t*)malloc(new_capacity * sizeof(int32_t));

        // list_pointer->Capacity = new_capacity;

        for (i = index; i < list_pointer->Size - 1; ++i)
        {
            *(list_pointer->Data + i) = *(list_pointer->Data + i + 1);
        }

        // free(list_pointer->Data);
        // list_pointer->Data = aux;
        list_pointer->Size -= 1;

        printf("\n Capacidad: %lu", list_pointer->Capacity);
        printf(" Size: %lu", list_pointer->Size);
    }
}

void ListRemove(ListPointer list_pointer, int32_t value)
{
    for (size_t i = 0; i < list_pointer->Size; i++)
    {
        if (value == list_pointer->Data[i])
        {
            ListRemoveAt(list_pointer, i);
            break;
        }
    }
}

void ListRemoveIf(ListPointer list_pointer, int32_t value)
{
    for (size_t i = 0; i < list_pointer->Size; i++)
    {
        if (value == list_pointer->Data[i])
        {
            ListRemoveAt(list_pointer, i);
        }
    }

}