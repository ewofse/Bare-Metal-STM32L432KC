#include <cbuffer.h>
#include <stdbool.h>
#include <stdint.h>

#define next(v) ( ( (v) + 1 ) % BUF_SIZE )

_Bool cbuffer_write(cbuffer_t * buf, uint8_t data) {
	_Bool retval = false;

	if ( !cbuffer_full(buf) ) {
		buf->buffer[buf->head] = data;
		buf->head = next(buf->head);	
		retval = true;
	}

	return retval;
}

_Bool cbuffer_read(cbuffer_t * buf, uint8_t * data) {
	_Bool retval = false;

	if ( !cbuffer_empty(buf) ) {
		*data = buf->buffer[buf->tail];
		buf->tail = next(buf->tail);
		retval = true;
	}

	return retval;
}

_Bool cbuffer_full(cbuffer_t * buf) {
	return next(buf->head) == buf->tail;	
}

_Bool cbuffer_empty(cbuffer_t * buf) {
	return buf->head == buf->tail;
}
