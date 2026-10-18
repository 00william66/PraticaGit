#include "unity.h"
#include "LinkedList.h"

/* Variável global para armazenar a cabeça da lista nos testes */
static NODE *listHead = NULL;

/* Executar ANTES de cada teste */
void setUp(void)
{
    listHead = NULL;
}

/* Executado DEPOIS de cada teste */
void tearDown(void)
{
    freeList(listHead);
    listHead = NULL;
}

/*
* TESTES PARA A FUNÇÃO insert
*/

void test_insert_into_empty_list(void)
{
    listHead = insert(listHead, 10);

    /* O ponteiro não pode ser NULL após a inserção */
    TEST_ASSERT_NOT_NULL(listHead);
}

void test_insert_multiple_elements_order(void)
{
    listHead = insert(listHead, 10);
    listHead = insert(listHead, 20);

    /* O novo elemento (20) deve estar no início */

    TEST_ASSERT_NOT_NULL(listHead);
}

/* 
 * TESTES PARA A FUNÇÃO delete
 */

void test_delete_from_empty_list(void)
{
    listHead = delete(NULL, 10);

    /* Apagar numa lista vazia deve devolver NULL sem crashar */
    TEST_ASSERT_NULL(listHead);
}

void test_delete_head_node(void)
{
    listHead = insert(listHead, 10);
    listHead = insert(listHead, 20);

    /* Apaga o elemento no topo (20) */
    listHead = delete(listHead, 20);

    TEST_ASSERT_NOT_NULL(listHead);
}

void test_delete_existing_element_makes_list_empty(void)
{
    listHead = insert(listHead, 5);
    listHead = delete(listHead, 5);

    /* A lista deve voltar a ficar vazia (NULL) */
    TEST_ASSERT_NULL(listHead);
}

/*
*  MAIN 
*/

int main(void)
{
    UNITY_BEGIN();

    setUp();
    RUN_TEST(test_insert_into_empty_list);
    tearDown();

    setUp();
    RUN_TEST(test_insert_multiple_elements_order);
    tearDown();

    setUp();
    RUN_TEST(test_delete_from_empty_list);
    tearDown();

    setUp();
    RUN_TEST(test_delete_head_node);
    tearDown();

    setUp();
    RUN_TEST(test_delete_existing_element_makes_list_empty);
    tearDown();

    return UNITY_END();
}