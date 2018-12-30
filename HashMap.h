#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <string.h>

typedef struct LinkedList
{
    void* value;
    struct LinkedList* next;
}LinkedList;

typedef struct Dict
{
    char* key;

    size_t chain_length;
    struct LinkedList* value;
}Dict;

typedef struct _HashMap
{
    Dict** entries;
    size_t entries_used;
    size_t size;
}_HashMap;

size_t GetHashSize(_HashMap*);
size_t GetChainLeng(_HashMap*, char* key);

_HashMap *InitHashMap(size_t size);
LinkedList *GetValue(_HashMap* , char* key);

LinkedList *NewLinked(void *value, LinkedList *next);
void DeleteLinked(LinkedList *value);

Dict *NewDict(char *key, LinkedList *value);
void DeleteDict(Dict* dict);

int hash(size_t hash_size, char *key);

void Add_Value(_HashMap*, char* key, void* value);
void Poll(_HashMap*, char* key);

int Clean(_HashMap*, char* key);
void Destroy(_HashMap**);

#endif