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
	return our_client;
}

void libmongodbcapi_db_client_destroy(libmongodbcapi_client* client) {
	if (client != NULL) {
		free(client);
	}
}

int libmongodbcapi_db_client_wire_protocol_rpc(libmongodbcapi_client* client, const void* input, size_t input_size, void** output, size_t* output_size) {
	if (input == NULL || output == NULL || (*output) == NULL) {
		return LIBMONGODBCAPI_ERROR_UNKNOWN;
	}

	(*output_size) = sizeof(char) * (input_size + 3);
	(*output) = malloc(*output_size);
	((char *)(*output))[0] = client->db_num;
	((char *)(*output))[1] = client->client_num;
	((char *)(*output))[2] = ':';

	memcpy((*output) + 3, input, input_size);

	return LIBMONGODBCAPI_ERROR_SUCCESS;
}

