#ifndef APC_H
#define APC_H

#include <stdint.h>
#include <stddef.h>

/* Each box holds 9 digits: 0 to 999999999 */
#define APC_BASE 1000000000u

/* Return codes */
#define APC_OK          0
#define APC_ERR_NOMEM  -1
#define APC_ERR_DIV0   -2
#define APC_ERR_SYNTAX -3
#define APC_ERR_DOMAIN -4

/* Decimal settings */
#define APC_DIV_EXTRA 100      /* extra decimal places produced by / */
#define APC_MAX_EXP   10000   /* largest exponent accepted by ^ */

typedef struct apc_node {
    uint32_t limb;            /* 9 digits */
    struct apc_node *prev;    /* toward head (bigger digits) */
    struct apc_node *next;    /* toward tail (smaller digits) */
} apc_node;

typedef struct {
    apc_node *head;   /* most significant box */
    apc_node *tail;   /* least significant box */
    size_t    len;    /* number of boxes */
    int       neg;    /* 1 = negative, 0 = positive or zero */
    size_t    scale;  /* digits after the decimal point.
                         value = (boxes read as one integer) / 10^scale */
} apc_num;

/* list.c */
apc_num *apc_new(void);
apc_num *apc_from_u32(uint32_t value);
int      apc_push_head(apc_num *n, uint32_t limb);
int      apc_push_tail(apc_num *n, uint32_t limb);
void     apc_pop_head(apc_num *n);
void     apc_trim(apc_num *n);
int      apc_is_zero(const apc_num *n);
void     apc_free(apc_num *n);

/* convert.c */
apc_num *apc_from_str(const char *s);
char    *apc_to_str(const apc_num *n);     /* caller must free() */

/* arithmetic.c */
apc_num *apc_add(const apc_num *a, const apc_num *b);
apc_num *apc_sub(const apc_num *a, const apc_num *b);
apc_num *apc_mul(const apc_num *a, const apc_num *b);
int      apc_divmod(const apc_num *a, const apc_num *b,
                    apc_num **q, apc_num **r);   /* integer only */
int      apc_div(const apc_num *a, const apc_num *b, apc_num **out);
int      apc_mod(const apc_num *a, const apc_num *b, apc_num **out);
int      apc_pow(const apc_num *a, const apc_num *e, apc_num **out);

/* parser.c */
int      apc_eval(const char *expr, apc_num **out,
                  char *err, size_t errlen);

#endif
