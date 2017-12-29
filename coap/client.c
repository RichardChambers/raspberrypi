
/*
 *  client.c from https://github.com/nikosft/libcoap/piggybacked/client.c
 *
 *  This is an example of a CoAP client which requests a single URI, hello,
 *  which is provided by a sample CoAP server also in the same github folder.
 *
 *  Starting with that source code, I am embellishing with more comments and
 *  some additional functionality to explore the CoAP protocol.
 *
 *  To compile you must first have the libcoap library installed using:
 *    sudo apt-get install libcoap-dev-1
 *
 *  You will also need the FastJSON library for parsing JSON text libfastjson:
 *    sudo apt-get install libfastjson-dev
 *
 *  You will need to specify the include path and you will need to specify
 *  the define -DWITH_POSIX on the compiler command line.
 *
 *  cc -DWITH_POSIX -o client client.c -lcoap-1 -lfastjson
*/


#include <stdio.h>

// header for the libcoap library. should be in /usr/include/coap
#include <coap/coap.h>

// header for the Fast JSON library. should be in /usr/include/libfastjson
#include <libfastjson/json.h>

/*
 * The response handler
 */ 
static void
message_handler(struct coap_context_t *ctx, const coap_endpoint_t *local_interface, 
                const coap_address_t *remote, coap_pdu_t *sent, coap_pdu_t *received, 
                const coap_tid_t id) 
{
	unsigned char* data;
	size_t         data_len;
	if (COAP_RESPONSE_CLASS(received->hdr->code) == 2) 
	{
		if (coap_get_data(received, &data_len, &data))
		{
			// we have data which should be a JSON text message.
			// there should be a field labeled "item" in the JSON.
			fjson_object *newObj = NULL;
			fjson_object *o = NULL;
			char  *field = "item";
			int iItem = 0;

			// parse the JSON text and extract the field we are interested in.
			// the field, "item" is supposed to be an integer value.
			if (newObj = fjson_tokener_parse (data)) {
				fjson_object_object_get_ex (newObj, field, &o);
				iItem = fjson_object_get_int(o);
				fjson_object_put(newObj);
			}

			printf("Received: %s -> item = %d\n", data, iItem);
		}
	}
}

int main(int argc, char* argv[])
{
	static coap_uri_t uri;
	coap_context_t*   ctx;
	coap_address_t    dst_addr, src_addr;
	coap_pdu_t*       request;

	char *aszDevName = "DEV-01-203";
	char *aszTempoName = "TEMPO-12345";
	int  iItem = 5;

	const char*       serverhello_uri = "coap://127.0.0.1/hello";
	const char*       servergoodbye_uri = "coap://127.0.0.1/goodbye";
	const char*       server_uri = NULL;
	char              server_query[256];
	unsigned char     get_method = 1;

	// prepare the coap socket
	coap_address_init (&src_addr);

	src_addr.addr.sin.sin_family      = AF_INET;
	src_addr.addr.sin.sin_port        = htons(0);
	src_addr.addr.sin.sin_addr.s_addr = inet_addr("0.0.0.0");
	ctx = coap_new_context(&src_addr);
	if (! ctx) {
		printf ("ERROR: coap_new_context() failed.\n");
		return 1;
	}

	/* The destination endpoint */
	coap_address_init(&dst_addr);
	dst_addr.addr.sin.sin_family      = AF_INET;
	dst_addr.addr.sin.sin_port        = htons(5683);
	dst_addr.addr.sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* Prepare the request */
	server_uri = serverhello_uri;
	coap_split_uri(server_uri, strlen(server_uri), &uri);
	request            = coap_new_pdu();	
	request->hdr->type = COAP_MESSAGE_CON;
	request->hdr->id   = coap_new_message_id(ctx);
	request->hdr->code = get_method;

	printf (" Request URI: path %d %s\n", uri.path.length, uri.path.s);

	coap_add_option(request, COAP_OPTION_URI_PATH, uri.path.length, uri.path.s);
	sprintf (server_query, "item=%d", iItem);
	coap_add_option(request, COAP_OPTION_URI_QUERY, strlen(server_query), server_query);
	printf ("         Query: len %d %s\n", strlen(server_query), server_query);
	sprintf (server_query, "device=%s", aszDevName);
	coap_add_option(request, COAP_OPTION_URI_QUERY, strlen(server_query), server_query);
	printf ("         Query: len %d %s\n", strlen(server_query), server_query);
	sprintf (server_query, "tempo=%s", aszTempoName);
	coap_add_option(request, COAP_OPTION_URI_QUERY, strlen(server_query), server_query);
	printf ("         Query: len %d %s\n", strlen(server_query), server_query);

	/* Set the response handler and send the request to the server */
	coap_register_response_handler(ctx, message_handler);
	coap_send_confirmed(ctx, ctx->endpoint, &dst_addr, request);

	struct timeval tv = {0};
	fd_set   readfds; 
	FD_ZERO(&readfds);
	FD_SET( ctx->sockfd, &readfds );
	tv.tv_sec = 5;  // set time out value in case server not up.
	int result = select( FD_SETSIZE, &readfds, 0, 0, &tv );
	if ( result < 0 ) /* socket error */
	{
		exit(EXIT_FAILURE);
	} 
	else if ( result > 0 && FD_ISSET( ctx->sockfd, &readfds )) /* socket read*/
	{	 
		coap_read( ctx );       
	} 
	else {
		printf (" Socket read time out. Is Server running?\n");
	}
  return 0;
}
