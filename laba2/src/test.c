#include <stdio.h>
#include <stdlib.h>
#include "IntVector.h"
#define BLUE "\e[1;34m"
#define CLOSE "\e[0m"
#define VALUE 10

void is_error(IntVector* v) // Проверяет на ошибку
{
    if (!v) {
        printf("Error of memory\n");
        exit(1);
    }
}

int main()
{
    IntVector *start, *test;

    printf("1\n");
    printf("Вызов %sint_vector_new%s: создает массив нулевого размера %sstart%s\n", BLUE, CLOSE, BLUE, CLOSE);
    start = int_vector_new(VALUE);
    is_error(start);
    printf("\n");

    printf("2\n");
    printf("Вызов %sint_vector_get_capacity%s: возвращает ёмкость вектора %sstart%s\n", BLUE, CLOSE, BLUE, CLOSE);
    printf("start->capacity = %ld\n", int_vector_get_capacity(start));
    printf("\n");
    
    printf("3\n");
    printf("Вызов %sint_vector_set_item%s: присваивает элементу под номером index = %si%s значение item = %si * 5%s\n", BLUE, CLOSE, BLUE, CLOSE, BLUE, CLOSE);
    for (int i = 0; i < int_vector_get_capacity(start); i++) {
        int_vector_set_item(start, i, i * 5);
    }
    printf("\n");

    printf("4\n");
    printf("Вызов %sint_vector_get_item%s: возвращает элемент под номером index = %si%s\n", BLUE, CLOSE, BLUE, CLOSE);
    for (int i = 0; i < int_vector_get_capacity(start); i++) {
        printf("start->data[%d] = %d\n", i, int_vector_get_item(start, i));
    }
    printf("\n");
    
    printf("5\n");
    printf("Вызов %sint_vector_copy%s: создает указатель test на копию вектора %sstart%s\n", BLUE, CLOSE, BLUE, CLOSE);
    test = int_vector_copy(start);
    is_error(test);
    printf("Проверка:\ntest->data[1] = %d\nstart->data[1] = %d\n\n", int_vector_get_item(test, 1), int_vector_get_item(start, 1));
    printf("\n");
    
    printf("6\n");
    printf("Вызов %sint_vector_free%s: освобождает память, выделенную для вектора %stest%s\n", BLUE, CLOSE, BLUE, CLOSE);
    int_vector_free(test);
    printf("Проверка:\ntest->data[0] = %d\nstart->data[0] = %d\n\n", int_vector_get_item(test, 1), int_vector_get_item(start, 1));
    
    printf("7\n");
    printf("Вызов %sint_vector_pop_back%s: удаляет последний элемент из массива %sstart->data%s\n", BLUE, CLOSE, BLUE, CLOSE);
    printf("Последний элемент до: start->data[%ld] = %d\n\n", int_vector_get_size(start) - 1, start->data[int_vector_get_size(start) - 1]);
    int_vector_pop_back(start);
    printf("Последний элемент после: start->data[%ld] = %d\n\n", int_vector_get_size(start) - 1, start->data[int_vector_get_size(start) - 1]);

    printf("8\n");
    printf("Вызов %sint_vector_get_size%s: возвращает размер вектора %sstart%s\n", BLUE, CLOSE, BLUE, CLOSE);
    printf("Размер массива: %ld\nЁмкость массива: %ld\n\n", int_vector_get_size(start), int_vector_get_capacity(start));

    printf("9\n");
    printf("Вызов %sint_vector_push_back%s: добавляет элемент в конец массива %sstart->data%s\n", BLUE, CLOSE, BLUE, CLOSE);
    int_vector_push_back(start, 2038);
    printf("Проверка: start->data[%ld] = %d\n\n", int_vector_get_capacity(start) - 1, int_vector_get_item(start, VALUE - 1));
    
    printf("10\n");
    printf("Вызов %sint_vector_reserve%s: изменяет ёмкость массива %sstart->capacity%s\n", BLUE, CLOSE, BLUE, CLOSE);
    printf("Старая ёмкость: %ld\n\n", int_vector_get_capacity(start));
    int_vector_reserve(start, VALUE + 5);
    printf("Новая ёмкость: %ld\n\n", int_vector_get_capacity(start));
    printf("\n");
    
    printf("11\n");
    printf("Вызов %sint_vector_resize%s: изменяет размер массива %sstart->size%s\n", BLUE, CLOSE, BLUE, CLOSE);
    int_vector_resize(start, VALUE + 2);
    for (int i = 0; i < int_vector_get_capacity(start); i++) {
        printf("start->data[%d] = %d\n", i, int_vector_get_item(start, i));
    }
    printf("\n");

    printf("12\n");
    printf("Вызов %sint_vector_shrink_to_fit%s: уменьшает ёмкость массива %sstart->capacity%s до его размера %sstart->size%s\n", BLUE, CLOSE, BLUE, CLOSE, BLUE, CLOSE);
    printf("Старая ёмкость: %ld, размер: %ld\n\n", int_vector_get_capacity(start), int_vector_get_size(start));
    int_vector_shrink_to_fit(start);
    printf("Новая ёмкость: %ld, размер: %ld\n\n", int_vector_get_capacity(start), int_vector_get_size(start));

    printf("ГРАНИЧНЫЙ СЛУЧАЙ:\n1) уменьшение размера массива до нуля\n");
    int_vector_resize(start, 0);
    printf("    size = %ld\n    start->data[0] = %d\n", int_vector_get_size(start), int_vector_get_item(start, 0));
    printf("\n");
    printf("2) добавление элемента в конец массива\n");
    int_vector_push_back(start, 451);
    printf("    size = %ld\n    start->data[0] = %d\n", int_vector_get_size(start), int_vector_get_item(start, 0));
    printf("\n");

    printf("Вызов %sint_vector_free%s для освобождения памяти, выделенной для вектора %sstart%s\n", BLUE, CLOSE, BLUE, CLOSE);
    int_vector_free(start);
}