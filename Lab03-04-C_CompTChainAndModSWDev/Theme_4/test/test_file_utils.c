#include <unity.h>
#include <stdio.h>
#include "file_utils.h"

#define TEST_FILE "test_sample.txt"

void setUp(void) {
    /* Cria um ficheiro temporário para os testes antes de cada função de teste */
    FILE *f = fopen(TEST_FILE, "w");
    if (f != NULL) {
        fprintf(f, "Hello world\nThis is a test file.\nUnity testing.\n");
        fclose(f);
    }
}

void tearDown(void) {
    /* Remove o ficheiro temporário após cada teste */
    remove(TEST_FILE);
}

void test_countParam_validFile(void) {
    int lines = 0, words = 0, chars = 0;

    /* Executa a contagem no ficheiro de teste */
    countParam(TEST_FILE, &lines, &words, &chars);

    /* O ficheiro criado tem:
       - 3 linhas
       - 9 palavras ("Hello", "world", "This", "is", "a", "test", "file.", "Unity", "testing.")
       - 48 carateres totais (incluindo quebras de linha \n)
    */
    TEST_ASSERT_EQUAL_INT(3, lines);
    TEST_ASSERT_EQUAL_INT(9, words);
    TEST_ASSERT_EQUAL_INT(48, chars);
}

void test_countParam_nonExistentFile(void) {
    int lines = -1, words = -1, chars = -1;

    /* Testa o comportamento quando o ficheiro não existe */
    countParam("non_existent_file.txt", &lines, &words, &chars);

    /* As variáveis devem manter o valor por omissão ou erro (ex: 0 ou -1) */
    TEST_ASSERT_EQUAL_INT(-1, lines);
    TEST_ASSERT_EQUAL_INT(-1, words);
    TEST_ASSERT_EQUAL_INT(-1, chars);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_countParam_validFile);
    RUN_TEST(test_countParam_nonExistentFile);
    UNITY_END();
    return 0;
}