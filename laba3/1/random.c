#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

/*
* Диапазон             Вероятность
* -------------------- -----------
* [0; 128)             90%
* [128; 16384)         5%
* [16384; 2097152)     4%
* [2097152; 268435455) 1%
*/

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}

int main()
{
    FILE* uncompressed = fopen("uncompressed.dat", "wb");
    FILE* compressed = fopen("compressed.dat", "wb");
    uint32_t number;
    uint32_t varint_size;
    uint8_t* var_arr = malloc(sizeof(uint32_t));
    
    for (int i = 0; i < 1000000; i++) {
    	number = generate_number();
    	fwrite(&number, sizeof(number), 1, uncompressed);
    	varint_size = encode_varint(number, var_arr);
    	fwrite(var_arr, varint_size, 1, compressed);
    }

    fclose(uncompressed);
    fclose(compressed);

    uncompressed = fopen("uncompressed.dat", "rb");
    compressed = fopen("compressed.dat", "rb");

    fseek(uncompressed, 0, SEEK_END);
    long uncomp_size = ftell(uncompressed);
    fseek(compressed, 0, SEEK_END);
    long comp_size = ftell(compressed);

    printf("%ld\n", uncomp_size);
    printf("%ld\n", comp_size);

    printf("Коэффициент сжатия равен %ld\n", (uncomp_size / comp_size));

    fseek(uncompressed, 0, SEEK_SET);
    fseek(compressed, 0, SEEK_SET);

    uint32_t decode;
    var_arr = realloc(var_arr, comp_size);
    const uint8_t* buf = var_arr;
    fread(var_arr, sizeof(uint8_t), comp_size, compressed);

    for (int i = 0; i < 1000000; i++) {
        fread(&number, sizeof(uint32_t), 1, uncompressed);
        decode = decode_varint(&buf);
        if (number != decode) {
            printf("Не удалось произвести кодирование или декодирование (%d)\n", i);
            return 1;
        }
    }

    free(var_arr);
    fclose(uncompressed);
    fclose(compressed);

    return 0;
}