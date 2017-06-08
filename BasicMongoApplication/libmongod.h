#ifndef LIBMONGODBCAPI_H
#define LIBMONGODBCAPI_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct libmongodbcapi_db libmongodbcapi_db;
typedef struct libmongodbcapi_client libmongodbcapi_client;

typedef enum {
   LIBMONGODBCAPI_ERROR_SUCCESS = 0,
   LIBMONGODBCAPI_ERROR_UNKNOWN,
} libmongodbcapi_error;

libmongodbcapi_db* libmongodbcapi_db_new(int argc, char** argv, char** envp);
void libmongodbcapi_db_destroy(libmongodbcapi_db*);

bool libmongodbcapi_db_pump(libmongodbcapi_db*);

libmongodbcapi_client* libmongodbcapi_db_client_new(libmongodbcapi_db* db);
void libmongodbcapi_db_client_destroy(libmongodbcapi_client* client);

int libmongodbcapi_db_client_wire_protocol_rpc(libmongodbcapi_client* client, const void* input, size_t input_size, void** output, size_t* output_size);

#ifdef __cplusplus
}
#endif

#endif
