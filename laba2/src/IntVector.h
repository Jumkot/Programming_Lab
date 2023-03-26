#include <stdio.h>

typedef struct {
    size_t size; // размер
    size_t capacity; // ёмкость
    int* data; // массив
} IntVector; // Структура IntVector

IntVector* int_vector_new(size_t initial_capacity); // Создает массив нулевого размера

IntVector* int_vector_copy(const IntVector* v); // Создает указатель на копию вектора v

void int_vector_free(IntVector* v); // Освобождает память, выделенную для вектора v

int int_vector_get_item(const IntVector* v, size_t index); // Возвращает элемент под номером index

void int_vector_set_item(IntVector* v, size_t index, int item); // Присваивает элементу под номером index значение item

size_t int_vector_get_size(const IntVector* v); // Возвращает размер вектора

size_t int_vector_get_capacity(const IntVector* v); // Возвращает емкость вектора

int int_vector_push_back(IntVector* v, int item); // Добавляет элемент в конец массива

void int_vector_pop_back(IntVector* v); // Удаляет последний элемент из массива

int int_vector_shrink_to_fit(IntVector* v); // Уменьшает емкость массива до его размера

int int_vector_resize(IntVector* v, size_t new_size); // Изменяет размер массива.
// Если новый размер массива больше исходного, то добавленные элементы заполняются нулями.
// Если новый размер массива меньше исходного, то перевыделение памяти не происходит.
// Для уменьшения емкости массива в этом случае следует использовать функцию int_vector_shrink_to_fit

int int_vector_reserve(IntVector* v, size_t new_capacity); // Изменяет емкость массива. 
// Нет эффекта, если новая емкость меньше либо равна исходной