#include <unity.h>
#include <stdlib.h>
#include <string.h>
#include "word_list.h"

static WORD *head = NULL;

void setUp(void) {
    /* Garante que a lista começa vazia antes de cada teste */
    head = NULL;
}

void tearDown(void) {
    /* Liberta a memória alocada para não haver leaks entre testes */
    freeList(&head);
}

void test_newWord_insertSingleNode(void) {
    newWord(&head, "hello");

    TEST_ASSERT_NOT_NULL(head);
    TEST_ASSERT_EQUAL_STRING("hello", head->word);
    TEST_ASSERT_EQUAL_INT(1, head->wordCount);
    TEST_ASSERT_NULL(head->ptr);
}

void test_search_insertNewAndIncrementExisting(void) {
    /* Insere uma palavra nova */
    search(&head, "apple");
    TEST_ASSERT_NOT_NULL(head);
    TEST_ASSERT_EQUAL_STRING("apple", head->word);
    TEST_ASSERT_EQUAL_INT(1, head->wordCount);

    /* Repete a mesma palavra: deve apenas incrementar o contador */
    search(&head, "apple");
    TEST_ASSERT_EQUAL_INT(2, head->wordCount);

    /* Insere uma nova palavra diferente */
    search(&head, "banana");
    
    /* "banana" passa a ser a nova cabeça da lista */
    TEST_ASSERT_EQUAL_STRING("banana", head->word);
    TEST_ASSERT_EQUAL_INT(1, head->wordCount);

    /* O nó seguinte deve ser "apple" com contador 2 */
    TEST_ASSERT_NOT_NULL(head->ptr);
    TEST_ASSERT_EQUAL_STRING("apple", head->ptr->word);
    TEST_ASSERT_EQUAL_INT(2, head->ptr->wordCount);
}

void test_freeList_cleansListCorrectly(void) {
    search(&head, "one");
    search(&head, "two");
    search(&head, "three");

    TEST_ASSERT_NOT_NULL(head);

    freeList(&head);

    /* Garante que a cabeça da lista fica NULL após a limpeza */
    TEST_ASSERT_NULL(head);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_newWord_insertSingleNode);
    RUN_TEST(test_search_insertNewAndIncrementExisting);
    RUN_TEST(test_freeList_cleansListCorrectly);
    return UNITY_END();
}