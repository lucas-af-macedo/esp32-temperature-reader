#ifndef LISTDATA_H
#define LISTDATA_H

struct data{
    float temperature1;
    float temperature2;
    float voltage;
    float current;
    struct data *next;
};

struct listData{
    int len;
    struct data *firstData;
};

void listPush(struct listData *list, float temperature1, float temperature2, float current, float voltage);

extern struct listData lista;


#endif