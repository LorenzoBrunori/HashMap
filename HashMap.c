#include "HashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SEARCH(map, key) (map->entries[hash(GetHashSize(map), key)])

LinkedList *NewLinked(void *value, LinkedList *next)
{
    LinkedList *new_Linked = malloc(sizeof(LinkedList));
    if (new_Linked == NULL)
    {
        return NULL;
    }
    new_Linked->value = value;
    new_Linked->next = next;

    return new_Linked;
}
void DeleteLinked(LinkedList *value)
{
    value->next = NULL;
    value->value = NULL;
    free(value);
}

Dict *NewDict(char *key, LinkedList *value)
{
    Dict *new_Dict = malloc(sizeof(Dict));

    if (new_Dict == NULL)
    {
        return NULL;
    }
    new_Dict->key = key;
    new_Dict->value = value;

    if (value == NULL)
    {
        new_Dict->chain_length = 0;
    }
    else
    {
        new_Dict->chain_length = 1;
    }

    return new_Dict;
}
void DeleteDict(Dict *dict)
{
    dict->key = NULL;

    if (dict->value != NULL)
    {
        DeleteLinked(dict->value);
    }
    free(dict);
}

int hash(size_t hash_size, char *key)
{
    size_t i;
    int result = 0;
    size_t string_size = strlen(key);

    for (int i = 0; i < string_size; i++)
    {
        result += key[i];

        if (i < string_size - 1)
        {
            result <<= 1;
        }
    }
    return result % hash_size;
}

_HashMap *InitHashMap(size_t size)
{
    _HashMap *new_Map;
    size_t i;

    new_Map = malloc(sizeof(_HashMap));
    new_Map->size = size;
    new_Map->entries_used = 0;

    new_Map->entries = malloc(size * sizeof(Dict *));

    for (int i = 0; i < size; i++)
    {
        new_Map->entries[i] = NULL;
    }
    return new_Map;
}

size_t GetChainLeng(_HashMap *map, char *key)
{
    return SEARCH(map, key)->chain_length;
}

size_t GetHashSize(_HashMap *map)
{
    return map->size;
}

LinkedList *GetValue(_HashMap *map, char *key)
{
    Dict *dict = SEARCH(map, key);
    if (dict == NULL)
        return NULL;
    return dict->value;
}

void Add_Value(_HashMap *map, char *key, void *value)
{
    Dict *dict = SEARCH(map, key);

    if (dict == NULL)
    {
        Dict *new_Dict = NewDict(key, NewLinked(value, NULL));
        SEARCH(map, key) = new_Dict;
        map->entries_used++;
    }
    else
    {
        LinkedList *iterator = dict->value;
        while (iterator->next != NULL)
        {
            iterator = iterator->next;
        }
        iterator->next = NewLinked(value, NULL);
        dict->chain_length++;
    }
}

void Poll(_HashMap *map, char *key)
{
    Dict *dict = SEARCH(map, key);
    void *res = NULL;

    if (dict == NULL)
    {
        return res;
    }

    if (dict->chain_length > 0)
    {
        LinkedList *value = dict->value;
        LinkedList *next = value->next;
        res = value->value;
        DeleteLinked(value);

        dict->value = next;
        dict->chain_length--;

        if (dict->chain_length == 0)
        {
            DeleteDict(dict);
            SEARCH(map, key) = NULL;
            map->entries_used--;
        }
    }
    return res;
}

int Clean(_HashMap *map, char *key)
{
    Dict *current_dict = SEARCH(map, key);

    if (current_dict == NULL)
    {
        return 0;
    }

    LinkedList *curr_val = current_dict->value;
    LinkedList *next = curr_val->next;

    while (next != NULL)
    {
        curr_val = next;
        next = next->next;
        DeleteLinked(curr_val);
    }
    DeleteDict(current_dict);
    SEARCH(map, key) = NULL;
    map->entries_used--;
    return -1;
}

void Destroy(_HashMap **map)
{
    _HashMap *real_map = *map;

    for (size_t i = 0; i < real_map->size; ++i)
    {

        if (real_map->entries[i] != NULL)
        {
            LinkedList *curr = real_map->entries[i]->value;
            LinkedList *next = curr->next;

            while (next != NULL)
            {
                curr = next;
                next = next->next;

                DeleteLinked(curr);
            }
            DeleteDict(real_map->entries[i]);
        }
    }

    free(real_map->entries);
    free(real_map);

}
