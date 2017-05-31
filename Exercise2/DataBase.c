#include "DataBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Description: creates an empty DataBase
 * Return: the DataBase created
 */
DataBase* createDataBase(){
    DataBase* result = malloc(sizeof(DataBase));
    int initialSize = 10;
    result->manufacturers = malloc(sizeof(Manufacturer*) * initialSize);
    result->manufacturerMaxCapacity = initialSize;
    result->providers = malloc(sizeof(Provider*) * initialSize);
    result->providerMaxCapacity = initialSize;
    result->products = malloc(sizeof(Product*) * initialSize);
    result->productMaxCapacity = initialSize;
    result->amountOfManufacturers = 0;
    result->amountOfProviders = 0;
    result->amountOfProducts = 0;
    return result;
}

/*
 * Description: searches a Manufacturer on the DataBase and returns it if found
 * Return: Manufacturer pointer
 */
Manufacturer* getManufacturer(DataBase* database, int manufacturerID){
    for(int i = 0; i < database->amountOfManufacturers; i++){
        if(database->manufacturers[i]->manufacturerID == manufacturerID)
            return database->manufacturers[i];
    }
    return NULL;
}

/*
 * Description: searches a Provider on the DataBase and returns it if found
 * Return: Provider pointer
 */
Provider* getProvider(DataBase* database, int providerID){
    for(int i = 0; i < database->amountOfProviders; i++){
            if(database->providers[i]->providerID == providerID)
                return database->providers[i];
    }
    return NULL;
}

/*
 * Description: searches a Appliance on the DataBase and returns it if found
 * Return: Product pointer
 */
Product* getProduct(DataBase *database, int productID){
    for(int i = 0; i < database->amountOfProducts; i++){
        if(database->products[i]->productID == productID)
            return database->products[i];
    }
    return NULL;
}

/*
 * Description: expands the Manufacturer array inside the DataBase
 * Return: void
 */
void growManufacturer(DataBase* database){
    database->manufacturers = realloc(database->manufacturers, sizeof(Manufacturer*) * database->manufacturerMaxCapacity * 2);
    database->manufacturerMaxCapacity *= 2;
}

/*
 * Description: expands the Provider array inside the DataBase
 * Return: void
 */
void growProvider(DataBase* database){
    database->providers = realloc(database->providers, sizeof(Provider*) * database->providerMaxCapacity * 2);
    database->providerMaxCapacity *= 2;
}

/*
 * Description: expands the Appliance array inside the DataBase
 * Return: void
 */
void growProduct(DataBase* database){
    database->products = realloc(database->products, sizeof(Product*) * database->productMaxCapacity * 2);
    database->productMaxCapacity *= 2;
}

int nextManufacturerID(DataBase* dataBase){
    return dataBase->manufacturerIDGenerator++;
}
int nextProviderID(DataBase* dataBase){
    return dataBase->providerIDGenerator++;
}
int nextProductID(DataBase* dataBase){
    return dataBase->productIDGenerator++;
}

/*
 * Description: adds a Manufacturer to the DataBase
 * Return: void
 */
void addManufacturer(DataBase* database, Manufacturer* manufacturer){
    if(database->amountOfManufacturers != database->manufacturerMaxCapacity){
        manufacturer->manufacturerID = nextManufacturerID(database);
        database->manufacturers[database->amountOfManufacturers] = manufacturer;
        database->amountOfManufacturers++;
    }else{
        growManufacturer(database);
        addManufacturer(database,manufacturer);
    }
}

/*
 * Description: adds a Provider to the DataBase
 * Return: void
 */
void addProvider(DataBase* database, Provider* provider){
    if(database->amountOfProviders != database->providerMaxCapacity){
        provider->providerID = nextProviderID(database);
        database->providers[database->amountOfProviders] = provider;
        database->amountOfProviders++;
    }else{
        growProvider(database);
        addProvider(database,provider);
    }
}

/*
 * Description: adds an Appliance to the DataBase and sets it's manufacturer and provider
 * Return: void
 */
void addProduct(DataBase *database, Product *product, int manufacturerID, int providerID){
    if(database->amountOfProducts != database->productMaxCapacity){
        product->productID = nextProductID(database);
        setManufacturerID(product,manufacturerID);
        setProviderID(product, providerID);
        database->products[database->amountOfProducts] = product;
        database->amountOfProducts++;
    }else{
        growProduct(database);
        addProduct(database, product, manufacturerID, providerID);
    }
}

/*
 * Description: searches a Manufacturer on the DataBase and deletes it if found
 * Return: returns 1 if found and deleted, 0 if not found
 */
int removeManufacturer(DataBase* database,int manufacturerID){
    for(int i = 0; i < database->amountOfManufacturers; i++){
        if(database->manufacturers[i]->manufacturerID == manufacturerID){
            Manufacturer* result = database->manufacturers[i];
            for (int j = i; j < database->amountOfManufacturers; j++){
                database->manufacturers[j] = database->manufacturers[j+1];
            }
            destroyManufacturer(result);
            database->amountOfManufacturers--;
            return 1;
        }
    }
    return 0;
}

/*
 * Description: searches a Provider on the DataBase and deletes it if found
 * Return: returns 1 if found and deleted, 0 if not found
 */
int removeProvider(DataBase* database, int providerID){
    for(int i = 0; i < database->amountOfProviders; i++){
        if(database->providers[i]->providerID == providerID){
            Provider* result = database->providers[i];
            for (int j = i; j < database->amountOfProviders; j++){
                database->providers[j] = database->providers[j+1];
            }
            destroyProvider(result);
            database->amountOfProviders--;
            return 1;
        }
    }
    return 0;
}

/*
 * Description: searches a product on the DataBase and deletes it if found
 * Return: returns 1 if found and deleted, 0 if not found
 */
int removeProduct(DataBase *database, int productID){
    for(int i = 0; i < database->amountOfProducts; i++){
        if(database->products[i]->productID == productID){
            Product* result = database->products[i];
            for (int j = i; j < database->amountOfProducts; j++){
                database->products[j] = database->products[j+1];
            }
            destroyProduct(result);
            database->amountOfProducts--;
            return 1;
        }
    }
    return 0;
}

/*
 * Description: checks if a Manufacturer is in the DataBase
 * Return: 1 if it has been found in the DataBase, 0 if not
 */
int manufacturerExist(DataBase* database, int manufacturerID){
    for(int i = 0; i < database->amountOfManufacturers; i++){
        if(manufacturerID == database->manufacturers[i]->manufacturerID) return 1;
    }
    return 0;
}

/*
 * Description: checks if a Provider is in the DataBase
 * Return: 1 if it has been found in the DataBase, 0 if not
 */
int providerExist(DataBase* database, int providerID){
    for(int i = 0; i < database->amountOfProviders; i++){
        if(providerID == database->providers[i]->providerID) return 1;
    }
    return 0;
}

/*
 * Description: checks if an Appliance is in the DataBase
 * Return: 1 if it has been found in the DataBase, 0 if not
 */
int productExist(DataBase *database, int productID){
    for(int i = 0; i < database->amountOfProducts; i++){
        if(productID == database->products[i]->providerID) return 1;
    }
    return 0;
}

/*
 * Description: Deallocates memory assigned for a DataBase and all its components
 * Return: void
 */
void destroyDataBase(DataBase* dataBase){
    for (int i = 0; i < dataBase->amountOfManufacturers; i++)
        destroyManufacturer(dataBase->manufacturers[i]);
    for (int i = 0; i < dataBase->amountOfProviders; i++)
        destroyProvider(dataBase->providers[i]);
    for (int i = 0; i < dataBase->amountOfProducts; i++)
        destroyProduct(dataBase->products[i]);
    free(dataBase->manufacturers);
    free(dataBase->providers);
    free(dataBase->products);
    free(dataBase);
}
