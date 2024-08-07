#include <stdio.h>
#include <stdlib.h>
#include "Boolean.h"

int main(int argc, char const *argv[])
{
    char hundred_ones[] = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    
    Boolean *vec = Boolean_from_str(hundred_ones);
    printf("hudred ones inversion\n%s\n", hundred_ones);
    inversion(vec);
    char *vec_to_print = Boolean_to_str(vec);
    printf("%s\n\n", vec_to_print);
    
    printf("set_one test\n");
    for(int i = 1; i <= 100; i++)
    {
        set_one(vec, i);
        vec_to_print = Boolean_to_str(vec);
        printf("%s\n", vec_to_print);
        free(vec_to_print);
    }

    printf("\nset_zero test\n");
    for(int i = 1; i <= 100; i++)
    {
        set_zero(vec, i);
        vec_to_print = Boolean_to_str(vec);
        printf("%s\n", vec_to_print);
        free(vec_to_print);        
    }

    printf("\nset_one test (reverse)\n");
    for(int i = 100; i >= 1; i--)
    {
        set_one(vec, i);
        vec_to_print = Boolean_to_str(vec);
        printf("%s\n", vec_to_print);
        free(vec_to_print);        
    }

    printf("\nset_zero test (reverse)\n");
    for(int i = 100; i >= 1; i--)
    {
        set_zero(vec, i);
        vec_to_print = Boolean_to_str(vec);
        printf("%s\n", vec_to_print);
        free(vec_to_print);        
    }

    vec_to_print = Boolean_to_str(vec);
    printf("\nhudred zeros inversion\n%s\n", vec_to_print);
    inversion(vec);
    vec_to_print = Boolean_to_str(vec);
    printf("%s\n", vec_to_print);
    free(vec_to_print);    
    free(vec);

    Boolean *vec1 = Boolean_from_str("10010");
    Boolean *vec2 = Boolean_from_str("11010");
    Boolean *res;

    printf("\ndisjunction vector len < 8\n");
    res = disjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("conjunction vector len < 8\n");
    res = conjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("xor vector len < 8\n");
    res = exclusive_or(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);
    free(vec1);
    free(vec2);


    vec1 = Boolean_from_str("10011010");
    vec2 = Boolean_from_str("11010111");

    printf("disjunction vector len = 8\n");
    res = disjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("conjunction vector len = 8\n");
    res = conjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("xor vector len = 8\n");
    res = exclusive_or(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);
    free(vec1);
    free(vec2);

    vec1 = Boolean_from_str("10011010100000011111");
    vec2 = Boolean_from_str("11010111110111011010");

    printf("disjunction vector len > 8\n");
    res = disjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("conjunction vector len > 8\n");
    res = conjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("xor vector len > 8\n");
    res = exclusive_or(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);
    free(vec1);
    free(vec2);

    vec1 = Boolean_from_str("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    vec2 = Boolean_from_str("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    printf("disjunction hundred one & hundred zeros\n");
    res = disjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("conjunction hundred one & hundred zeros\n");
    res = conjunction(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);

    printf("xor hundred one & hundred zeros\n");
    res = exclusive_or(vec1, vec2);
    vec_to_print = Boolean_to_str(vec1);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(vec2);
    printf("%s\n", vec_to_print);
    vec_to_print = Boolean_to_str(res);
    printf("%s\n\n", vec_to_print);

    free(vec_to_print);
    free(res);
    free(vec2);

    printf("\nhundred ones left shift\n");
    for(int i = 0; i < 16; i++)
    {
        vec_to_print = Boolean_to_str(vec1);
        printf("%s\n", vec_to_print);
        left_shift(vec1, i);
        free(vec_to_print);
    }

    free(vec1);

    vec1 = Boolean_from_str("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    printf("\nhundred ones right shift\n");
    for(int i = 0; i < 16; i++)
    {
        vec_to_print = Boolean_to_str(vec1);
        printf("%s\n", vec_to_print);
        right_shift(vec1, i);
        free(vec_to_print);
    }    
    return 0;
}