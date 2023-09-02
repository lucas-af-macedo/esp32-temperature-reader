#ifndef LISTDATA_H
#define LISTDATA_H

struct data{
    int time;
    float temperature1;
    float temperature2;
    float voltage;
    float current;
    struct data *next;
    struct data *previous;
};

struct listData{
    int len;
    struct data *firstData;
    struct data *lastData;
};

void listPush(struct listData *list, int time, float temperature1, float temperature2, float current, float voltage);

extern struct listData lista;


#endif