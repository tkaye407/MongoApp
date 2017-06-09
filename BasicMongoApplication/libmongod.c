#include "libmongod.h"
#include <stdlib.h>
#include <string.h>
struct libmongodbcapi_db {
	char db_num;
	char num_clients;

};

struct libmongodbcapi_client {
	char db_num;
	char client_num;
    size_t output_size;
    size_t buffer_size;
    void* output_buffer;
};

libmongodbcapi_db* libmongodbcapi_db_new(int argc, char** argv, char** envp) {
	libmongodbcapi_db* our_db = malloc(sizeof(libmongodbcapi_db));
	if (our_db == NULL) {
		return NULL;
	}
	our_db->db_num = (char) argc;
	our_db->num_clients = (char)0;
	return our_db;
}

void libmongodbcapi_db_destroy(libmongodbcapi_db* our_db) {
	if (our_db != NULL) {
		free(our_db);
	}
}

bool libmongodbcapi_db_pump(libmongodbcapi_db* our_db) {
	return true;
}

libmongodbcapi_client* libmongodbcapi_db_client_new(libmongodbcapi_db* db) {
	if (db == NULL) {
		return NULL;
	}
	libmongodbcapi_client* our_client = malloc(sizeof(libmongodbcapi_client));
	if (our_client == NULL) {
		return NULL;
	}
	our_client->db_num = db->db_num;
	our_client->client_num = (db->num_clients)++;
    our_client->output_buffer = NULL;
    our_client->output_size = 0;
    our_client->buffer_size = 0;
	return our_client;
}

void libmongodbcapi_db_client_destroy(libmongodbcapi_client* client) {
    if (client->output_buffer != NULL) {
        free(client->output_buffer);
    }
    if (client != NULL) {
		free(client);
	}
}

int libmongodbcapi_db_client_wire_protocol_rpc(libmongodbcapi_client* client, const void* input, size_t input_size, void** output, size_t* output_size) {
	if (input == NULL || output == NULL || (*output) == NULL) {
		return LIBMONGODBCAPI_ERROR_UNKNOWN;
	}
    // this should be the size of the return message, which is input_size + 4 for now
    if (client->buffer_size == 0) {
        client->output_buffer = malloc(sizeof(char) * (input_size + 4));
        if (client->output_buffer == NULL) {
            return LIBMONGODBCAPI_ERROR_UNKNOWN;
        }
        client->buffer_size = input_size + 4;
    }
    if( input_size + 4 > client->buffer_size) {
        size_t temp_size = sizeof(char) * (input_size + 4);
        void * new_buf = realloc(client->output_buffer, temp_size);
        if (new_buf == NULL) {
            return LIBMONGODBCAPI_ERROR_UNKNOWN;
        }
        client->output_size = temp_size;
        client->output_buffer = new_buf;
    }

    
    (*output_size) = client->output_size;
    (*output) = client->output_buffer;
	((char *)(client->output_buffer))[0] = 'a';
	((char *)(client->output_buffer))[1] = 'b';
	((char *)(client->output_buffer))[2] = ':';
    ((char *)(client->output_buffer))[(client->output_size) - 1] = '\0';
    memcpy((client->output_buffer) + 3, input, input_size);
    (*output_size) = client->output_size;
    (*output) = client->output_buffer;
	
	return LIBMONGODBCAPI_ERROR_SUCCESS;
}

