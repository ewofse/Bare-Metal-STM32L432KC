#ifndef CBUFFER_H
#define CBUFFER_H

#include <stdbool.h>
#include <stdint.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

typedef struct {
    uint8_t buffer[BUF_SIZE];
    uint32_t head;
    uint32_t tail;
} cbuffer_t;

_Bool cbuffer_write(cbuffer_t * buf, uint8_t data);
_Bool cbuffer_read(cbuffer_t * buf, uint8_t * data);
_Bool cbuffer_full(cbuffer_t * buf);
_Bool cbuffer_empty(cbuffer_t * buf);

#endif

