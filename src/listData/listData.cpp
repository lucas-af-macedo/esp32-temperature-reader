#include <stdio.h>
#include "listData.h"


void listPush(struct listData *list, float temperature1, float temperature2, float current, float voltage){
    struct data *aux = list->firstData;
    struct data *newData = (struct data *)malloc(sizeof(struct data));
    int len = list->len;
    if(list->len==900){
        struct data *aux2 = list->firstData;
        list->firstData = list->firstData->next;
        free(aux2);
    }else{
        list->len++;
    }
    for(int i=0;i<len-1;i++){
        aux=aux->next;
    }
    newData->temperature1 = temperature1;
    newData->temperature2 = temperature2;
    newData->current = current;
    newData->voltage = voltage;
    newData->next = NULL;
    if(len==0){
        list->firstData = newData;
    } else{
        aux->next = newData;
    }
}

void printList(struct listData *list) {
    struct data *current = list->firstData;
    while (current != NULL) {
        printf("Temperature1: %f, Temperature2: %f, Voltage: %f, Current: %f\n",
               current->temperature1, current->temperature2, current->voltage, current->current);
        current = current->next;
    }
}

struct listData lista = {0};
