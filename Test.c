#include "HashMap.h"
#include "aiv_unit_test.h"

#define SIZE 256

int tests_succeded = 0;
int tests_failed = 0;
int tests_executed = 0;

TEST(RandomTest)
{
    ASSERT_THAT(1);
}

TEST(INITHASH)
{
    _HashMap *new_Map = InitHashMap(SIZE);
    ASSERT_THAT(new_Map->entries_used == 0);
    ASSERT_THAT(new_Map->size == SIZE);

    for (size_t i = 0; i < new_Map->size; ++i)
    {
        ASSERT_THAT(new_Map->entries[i] == NULL);
    }

    Destroy(&new_Map);
}

TEST(MAPADD)
{
    _HashMap *new_Map = InitHashMap(SIZE);

    char *key = _strdup("AIV"); //strdup func shall return a pointer to a new string, which is a duplicate of the the string pointed to
    int value = 40;

    Add_Value(new_Map, key, (void *)&value);

    ASSERT_THAT(new_Map->entries_used == 1);

    Destroy(&new_Map);
    free(key);
}

TEST(MAPADDCOLLISION)
{
    _HashMap *new_Map = InitHashMap(SIZE);

    char *key = _strdup("AIV");
    int value = 40;

    char *key2 = _strdup("AIV");
    int value2 = 30;

    Add_Value(new_Map, key, (void *)&value);
    Add_Value(new_Map, key2, (void *)&value2);

    ASSERT_THAT(new_Map->entries_used == 1);
    ASSERT_THAT(GetChainLeng(new_Map, "AIV"));

    Destroy(&new_Map);
    free(key);
    free(key2);
}

TEST(GET)
{
    _HashMap *new_Map = InitHashMap(SIZE);

    char *key = _strdup("AIV");
    int value = 40;

    Add_Value(new_Map, key, (void *)&value);
    ASSERT_THAT(new_Map->entries_used == 1);

    LinkedList *res = GetValue(new_Map, key);

    ASSERT_THAT(res->next == NULL);
    ASSERT_THAT(*((int*)res->value) == 40);
}

int main(int argc, char **argv)
{
    RUN_TEST(RandomTest);
    RUN_TEST(INITHASH);
    RUN_TEST(MAPADD);
    RUN_TEST(MAPADDCOLLISION);
    RUN_TEST(GET);
    PRINT_TEST_RESULTS();
    return 0;
}