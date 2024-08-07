#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Boolean
{
    uint8_t *vector;
    size_t num_bytes;
    size_t num_bits;
} Boolean;

Boolean* Boolean_from_str(char*);
char* Boolean_to_str(Boolean*);

bool inversion(Boolean*);
Boolean* conjunction(Boolean*, Boolean*);
Boolean* disjunction(Boolean*, Boolean*);
Boolean* exclusive_or(Boolean*, Boolean*);

bool left_shift(Boolean*, int);
bool right_shift(Boolean*, int);

size_t Boolean_len(Boolean*);
bool set_one(Boolean*, int);
bool set_zero(Boolean*, int);
int get_bit(Boolean*, int);

#endif