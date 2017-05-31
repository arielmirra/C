#ifndef CFROMJAVA_ACCESORY_H
#define CFROMJAVA_ACCESORY_H

typedef struct Accessory {
    char* name;
    char* description;
    int id;
}Accessory;

//functions
Accessory* createAccessory(char* name, char* description);
void destroyAccessory(Accessory* accessory);
#endif //CFROMJAVA_ACCESORY_H