#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

buffer *
buffer_new(size_t initial_size)
{
	buffer *buf = malloc(sizeof(buffer));
	char *data = malloc(initial_size);
	if (!buf || !data) {
		free(buf);
		free(data);
		return NULL;
	}
	buf->data = data;
	buf->len = 0;
	buf->sz = initial_size;
	return buf;
}

void
buffer_free(buffer *buf)
{
	if (buf) {
		free(buf->data);
		free(buf);
	}
}

int
buffer_append(buffer *buf, const char *input, size_t len)
{
	if (buf->len + len > buf->sz) {
		size_t newsz;
		if (len > buf->sz)
			newsz = len * 2;
		else
			newsz = buf->sz * 2;
		char *newp = realloc(buf->data, newsz);
		if (!newp)
			return -1;
		buf->data = newp;
		buf->sz = newsz;
	}
	memcpy(buf->data + buf->len, input, len);
	buf->len += len;
	return 0;
}

int
buffer_append_buf(buffer *buf, const buffer *ibuf)
{
	return buffer_append(buf, ibuf->data, ibuf->len);
}

int
buffer_append_str(buffer *buf, const char *str)
{
	size_t len = strlen(str);
	return buffer_append(buf, str, len);
}

void
buffer_clear(buffer *buf)
{
	buf->len = 0;
}
