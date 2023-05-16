#include "coder.h"
#include "command.h"

int encode_file(const char* in_file_name, const char* out_file_name)
{
    FILE *in, *out;
    in = fopen(in_file_name, "r");
    if (!in) {
        printf("Ошибка: не удалось открыть файл %s\n", in_file_name);
        return -1;
    }

    out = fopen(out_file_name, "wb");
    if (!out) {
        printf("Ошибка: не удалось открыть файл %s\n", out_file_name);
        fclose(in);
        return -1;
    }

    uint32_t value;
    CodeUnits enc_units;

    while (!feof(in)) {
        if (fscanf(in, "%" SCNx32, &value) == 0) {
            printf("Ошибка: элемент '%d'в файле '%s' не является значением типа uint32_t\n", value, in_file_name);
            return -1;
        }
        encode(value, &enc_units);
        write_code_unit(out, &enc_units);
    }

    fclose(in);
    fclose(out);

    return 0;
}

int decode_file(const char* in_file_name, const char* out_file_name)
{
    FILE *in, *out;
    in = fopen(in_file_name, "rb");
    if (!in) {
        printf("Ошибка: не удалось открыть файл %s\n", in_file_name);
        return -1;
    }

    out = fopen(out_file_name, "w");
    if (!out) {
        printf("Ошибка: не удалось открыть файл %s\n", out_file_name);
        fclose(in);
        return -1;
    }

    uint32_t value;
    CodeUnits dec_units;

    while (!feof(in)) {
        if (read_next_code_unit(in, &dec_units) == EOF) {
            break;
        }
        value = decode(&dec_units);
        fprintf(out, "%" PRIx32, value);
        fprintf(out, "\n");
    }

    fclose(in);
    fclose(out);

    return 0;
}