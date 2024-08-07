#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Boolean.h"

Boolean* Boolean_from_str(char* vecStr) {
    if(!vecStr)
        return NULL;

    Boolean* BB = (Boolean*) calloc(1, sizeof(Boolean));
    if(!BB)
        return NULL;

    size_t vecLen = 0;
    for(vecLen; vecStr[vecLen]; ++vecLen)
        if(vecStr[vecLen] != '0' && vecStr[vecLen] != '1')
        {
            free(BB);
            return NULL;
        }


    BB->num_bytes = vecLen / 8;
    BB->num_bits = vecLen % 8;
    size_t bytes = BB->num_bytes + (BB->num_bits > 0);
    BB->vector = (uint8_t*) calloc(bytes, sizeof(uint8_t));
    if(!BB->vector)
        return NULL;

    //заполнение целых байтов
    int index = 0;
    for(int byte = 0; byte < BB->num_bytes; ++byte) {
        for(int bit = 0; bit < 8; ++bit) {
            index = vecLen - 1 - (byte * 8 + bit);
            BB->vector[byte] |= ((vecStr[index] - '0') << bit);
        }
    }

    //заполение оставшихся бит, не составляющих целый байт
    for(int bit = 0; bit < BB->num_bits; ++bit) {
        index = vecLen - 1 - (BB->num_bytes * 8 + bit);
        BB->vector[BB->num_bytes] |= ((vecStr[index] - '0') << bit);
    }

    return BB;
}

char* Boolean_to_str(Boolean* BB) {

    if(!BB)
        return NULL;

    size_t vecLen = Boolean_len(BB);
    char *vecStr = (char*) malloc(vecLen + 1);
    
    if(!vecStr)
        return NULL;

    int index = 0;
    for(int bit = vecLen - 1; bit >= 0; --bit) {
        index = vecLen - bit - 1; 
        vecStr[index] = BB->vector[bit / 8] >> (bit % 8) & 1;
        vecStr[index] += '0';
    }
    vecStr[vecLen] = '\0';

    return vecStr;
}

bool inversion(Boolean* BB) {
    
    if(!BB)
        return false;


    uint8_t mask = -1;
    for(int byte = 0; byte < BB->num_bytes; ++byte)
       BB->vector[byte] ^= mask;

    for(int bit = 0; bit < BB->num_bits; ++bit)
        BB->vector[BB->num_bytes] ^= 1 << bit;

    return true;
}

Boolean* conjunction(Boolean* BB1, Boolean* BB2) {
    if(!BB1 || !BB2)
        return NULL;        

    Boolean* res = (Boolean*) calloc(1, sizeof(Boolean));
    if(!res)
        return NULL;     

    Boolean* bigger_vector;
    Boolean* smaller_vector;
    size_t bigger_bytes, smaller_bytes;
    if(Boolean_len(BB1) >= Boolean_len(BB2)) {
        bigger_vector = BB1;
        smaller_vector = BB2;
        bigger_bytes = BB1->num_bytes + (BB1->num_bits > 0);
        smaller_bytes = BB2->num_bytes + (BB2->num_bits > 0);
    }
    else {
        bigger_vector = BB2;
        smaller_vector = BB1;
        bigger_bytes = BB2->num_bytes + (BB2->num_bits > 0);
        smaller_bytes = BB1->num_bytes + (BB1->num_bits > 0);
    }

    res->vector = (uint8_t*) calloc(bigger_bytes, sizeof(uint8_t));
    if(!res->vector)
        return NULL;

    size_t byte = 0;
    for(byte; byte < smaller_bytes; ++byte)
        res->vector[byte] = bigger_vector->vector[byte] & smaller_vector->vector[byte];
    for(byte; byte < bigger_bytes; ++byte)
        res->vector[byte] = 0;
    res->num_bytes = bigger_vector->num_bytes;
    res->num_bits = bigger_vector->num_bits;

    return res;
}

Boolean* disjunction(Boolean* BB1, Boolean* BB2) {
    
    if(!BB1 || !BB2)
        return NULL;        

    Boolean* res = (Boolean*) calloc(1, sizeof(Boolean));
    if(!res) 
        return NULL;        

    Boolean* bigger_vector;
    Boolean* smaller_vector;
    size_t bigger_bytes, smaller_bytes;
    if(Boolean_len(BB1) >= Boolean_len(BB2)) {
        bigger_vector = BB1;
        smaller_vector = BB2;
        bigger_bytes = BB1->num_bytes + (BB1->num_bits > 0);
        smaller_bytes = BB2->num_bytes + (BB2->num_bits > 0);
    }
    else {
        bigger_vector = BB2;
        smaller_vector = BB1;
        bigger_bytes = BB2->num_bytes + (BB2->num_bits > 0);
        smaller_bytes = BB1->num_bytes + (BB1->num_bits > 0);
    }

    res->vector = (uint8_t*) calloc(bigger_bytes, sizeof(uint8_t));
    if(!res->vector)
        return NULL;

    size_t byte = 0;
    for(byte; byte < smaller_bytes; ++byte)
        res->vector[byte] = bigger_vector->vector[byte] | smaller_vector->vector[byte];
    for(byte; byte < bigger_bytes; ++byte)
        res->vector[byte] = bigger_vector->vector[byte];

    res->num_bytes = bigger_vector->num_bytes;
    res->num_bits = bigger_vector->num_bits;

    return res;
}

Boolean* exclusive_or(Boolean* BB1, Boolean* BB2) {
    
    if(!BB1 || !BB2)
        return NULL;        

    Boolean* res = (Boolean*) calloc(1, sizeof(Boolean));
    if(!res)
        return NULL;        

    Boolean* bigger_vector;
    Boolean* smaller_vector;
    size_t bigger_bytes, smaller_bytes;
    if(Boolean_len(BB1) >= Boolean_len(BB2)) {
        bigger_vector = BB1;
        smaller_vector = BB2;
        bigger_bytes = BB1->num_bytes + (BB1->num_bits > 0);
        smaller_bytes = BB2->num_bytes + (BB2->num_bits > 0);
    }
    else {
        bigger_vector = BB2;
        smaller_vector = BB1;
        bigger_bytes = BB2->num_bytes + (BB2->num_bits > 0);
        smaller_bytes = BB1->num_bytes + (BB1->num_bits > 0);
    }

    res->vector = (uint8_t*) calloc(bigger_bytes, sizeof(uint8_t));
    if(!res->vector)
        return NULL;

    size_t byte = 0;
    for(byte; byte < smaller_bytes; ++byte)
        res->vector[byte] = bigger_vector->vector[byte] ^ smaller_vector->vector[byte];
    for(byte; byte < bigger_bytes; ++byte)
        res->vector[byte] = bigger_vector->vector[byte];

    res->num_bytes = BB1->num_bytes;
    res->num_bits = BB1->num_bits;
    
    return res;
}

bool left_shift(Boolean* BB, int shift) {
    
    if(!BB)
        return false;

    if(shift >= BB->num_bytes*8 + BB->num_bits)
    {
        for(size_t byte = 0; byte < BB->num_bytes; ++byte)
            BB->vector[byte] = 0;    
        return true;
    }

    if(shift < 0) {
        right_shift(BB, -shift);
        return true;
    }

    size_t byte = BB->num_bytes + (BB->num_bits > 0) - 1;
    for(byte; byte > shift / 8; --byte) {
        BB->vector[byte] = BB->vector[byte - shift / 8];
        BB->vector[byte] <<= shift % 8;
        BB->vector[byte] |= BB->vector[byte - shift / 8 - 1] >> (8 - shift % 8);
    }

    BB->vector[shift / 8] = BB->vector[0];
    BB->vector[shift / 8] <<= shift % 8;

    for(byte = 0; byte < shift / 8; ++byte)
        BB->vector[byte] = 0;

    uint8_t mask = -1;
    mask >>= 8 - BB->num_bits;
    BB->vector[BB->num_bytes + (BB->num_bits > 0) - 1] &= mask;    
    return true;
}

bool right_shift(Boolean* BB, int shift) {
    
    if(!BB)
        return false;

    if(shift >= BB->num_bytes*8 + BB->num_bits)
    {
        for(size_t byte = 0; byte < BB->num_bytes; ++byte)
            BB->vector[byte] = 0;    
        return true;
    }

    if(shift < 0) {
        left_shift(BB, -shift);
        return true;
    }

    size_t lastPart = BB->num_bytes + (BB->num_bits > 0) - shift / 8 - 1;
    for(size_t byte = 0; byte < lastPart; ++byte) {
        BB->vector[byte] = BB->vector[byte + shift / 8];
        BB->vector[byte] >>= shift % 8;
        BB->vector[byte] |= BB->vector[byte + shift / 8 + 1] << (8 - shift % 8);        
    }
    BB->vector[lastPart] = BB->vector[lastPart + shift / 8];
    BB->vector[lastPart] >>= shift % 8;

    for(size_t byte = lastPart + 1; byte < BB->num_bytes + (BB->num_bits > 0); ++byte)    
        BB->vector[byte] = 0;
    return true;
}

size_t Boolean_len(Boolean* BB) {
    return BB->num_bytes * 8 + BB->num_bits;
}

bool set_one(Boolean* BB, int pos)
{
    if(!BB)
        return false;
    if(pos > Boolean_len(BB) || pos < 0)
        return false;

    pos = Boolean_len(BB) - pos;
    BB->vector[pos / 8] |= 1 << (pos % 8); 
    return true;
}

bool set_zero(Boolean* BB, int pos)
{
    if(!BB)
        return false;
    if(pos > Boolean_len(BB) || pos < 0)
        return false;

    pos = Boolean_len(BB) - pos;
    uint8_t mask = -1;
    mask ^= 1 << (pos % 8);
    BB->vector[pos / 8] &= mask; 
    return true;
}

int get_bit(Boolean* BB, int pos) 
{
    if(!BB)
        return -1;
    if(pos > Boolean_len(BB))
        return -1;
    return BB->vector[pos / 8] >> (pos % 8) & 1;
}