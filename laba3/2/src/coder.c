int encode(uint32_t code_point, CodeUnit* code_unit)
{
    assert(code_unit != NULL);

    if (code_point < 0x80) {
        code_unit->length = 1;
        code_unit->code[0] = code_point;
    } else if (code_point < 0x800) {
        code_unit->length = 2;
        code_unit->code[0] = 0xc0 | (code_point >> 6);
        code_unit->code[1] = 0x80 | (code_point & 0x3f);
    } else if (code_point < 0x10000) {
        code_unit->length = 3;
        code_unit->code[0] = 0xe0 | (code_point >> 12);
        code_unit->code[1] = 0x80 | ((code_point >> 6) & 0x3f);
        code_unit->code[2] = 0x80 | (code_point & 0x3f);
    } else if (code_point < 0x200000) {
        code_unit->length = 4;
        code_unit->code[0] = 0xf0 | (code_point >> 18);
        code_unit->code[1] = 0x80 | ((code_point >> 12) & 0x3f);
        code_unit->code[2] = 0x80 | ((code_point >> 6) & 0x3f);
        code_unit->code[3] = 0x80 | (code_point & 0x3f);
    } else {
        printf("%d превышает масимальное значение для кодирования\n", code_point);
        code_unit->length = 0;

        return -1;
    }
    return 0;
}

uint32_t decode(const CodeUnit* code_unit)
{
    uint32_t code_point;

    if (code_unit->length == 1) {
        code_point = code_unit->code[0];
    } else if (code_unit->length == 2) {
        code_point = code_unit->code[0] & 0x1f;
        code_point = (code_point << 6) | (code_unit->code[1] & 0x3f);
    } else if (code_unit->length == 3) {
        code_point = code_unit->code[0] & 0xf;
        code_point = (code_point << 6) | (code_unit->code[1] & 0x3f);
        code_point = (code_point << 6) | (code_unit->code[2] & 0x3f);
    } else if (code_unit->length == 4) {
        code_point = code_unit->code[0] & 0x7;
        code_point = (code_point << 6) | (code_unit->code[1] & 0x3f);
        code_point = (code_point << 6) | (code_unit->code[2] & 0x3f);
        code_point = (code_point << 6) | (code_unit->code[3] & 0x3f);
        code_unit = NULL;
    }

    return code_point;
}

int write_code_unit(FILE* out, const CodeUnits* code_unit)
{
    if ((out == NULL) || (code_unit == NULL) || (code_unit->length == 0)) {
        return -1;
    }

    if (fwrite(code_unit->code, 1, code_unit->length, out) < code_unit->length) {
        return -1;
    }

    return 0;
}

int read_next_code_unit(FILE* in, CodeUnits* code_units)
{
    
}