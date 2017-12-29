/*
 *  server.c from https://github.com/nikosft/libcoap/piggybacked/server.c
 *
 *  This is an example of a CoAP server which provides a single URI, hello,
 *  which is accessed by a sample CoAP client also in the same github folder.
 *
 *  Starting with that source code, I am embellishing with more comments and
 *  some additional functionality to explore the CoAP protocol.
 *
 *  To compile you must first have the libcoap library installed using:
 *    sudo apt-get install libcoap-dev-1
 *
 *  You will need to specify the include path and you will need to specify
 *  the define -DWITH_POSIX on the compiler command line.
*/

#include <stdio.h>

// header for the libcoap library. it should be in /usr/include/coap
// we also need the options header since we are using options.
#include <coap/coap.h>
#include <coap/option.h>

/*
 * The following helper function, printQueryOption(), is used to
 * iterate over the list of options looking for query type options
 * to the base URI. This is analogous to a web URL that contains
 * a question mark followed by options such as:
 *    http://www.server.com/hello?type=1,id=2345
 *
 * We will return a value of 1 (true) if we found something or a value
 * of 0 (false) if we do not.
*/
static int
printQueryOption (coap_pdu_t *request, coap_opt_iterator_t * popt_iter )
{
	int  iRet = 0;
	coap_opt_t *option;

	// iterate over the options looking for queries. If we find one
	// then print it and return a value of 1, true, to indicate we
	// found one. If we don't find any then return the default value
	// of 0, false.
	while (option = coap_option_next(popt_iter)) {
		// found an option, is it a query option or not.
		if (popt_iter->type != COAP_OPTION_URI_QUERY) continue;
		// it is a query option so print out the query text.
		char xBuff[128] = {0};
		strncpy (xBuff, COAP_OPT_VALUE(option), COAP_OPT_LENGTH(option));
		printf ("    option  len %d\n         %s \n", COAP_OPT_LENGTH(option), xBuff);

		// indicate that we found a query option.
		iRet = 1;
		break;
	}

	return iRet;
}

/*
 * The resource handler which the libcoap library will invoke when the registered
 * URI is specified. This is a simple request handler which will just display some
 * of the information from the request.
 */ 
static void
hello_handler(coap_context_t *ctx, struct coap_resource_t *resource, 
              const coap_endpoint_t *local_interface, coap_address_t *peer, 
              coap_pdu_t *request, str *token, coap_pdu_t *response) 
{
	static  int iCount = 0;   // a simple count to provide some kind of response data.
	unsigned char buf[3];
	const char* response_data     = "{\"device\": \"DEV-01-123\", \"item\" : %d }";
	char response_buf[256] = {0};

	// generate a response to this request. we have a hard coded JSON text that
	// we are using as a stub for testing.
	response->hdr->code           = COAP_RESPONSE_CODE(205);
	coap_add_option(response, COAP_OPTION_CONTENT_TYPE, coap_encode_var_bytes(buf, COAP_MEDIATYPE_TEXT_PLAIN), buf);

	sprintf (response_buf, response_data, iCount);
	coap_add_data  (response, strlen(response_buf), (unsigned char *)response_buf);
	iCount++;    // this count is some type of varying data so that we can see things are working.

	if (request != NULL) {
		// there is a request URI so lets print out the base URI and then
		// iterate over the options looking for the Query type options.
		coap_opt_iterator_t  opt_iter;

		printf (" request %s\n", resource->uri.s);
		coap_option_iterator_init (request, &opt_iter, COAP_OPT_ALL);

		// iterate over the options of the request printing out any
		// query text that may exist.
		while (printQueryOption (request, &opt_iter));
	} else {
		printf (" request - NONE\n");
	}
}

int main(int argc, char* argv[])
{
	coap_context_t*  ctx;
	coap_address_t   serv_addr;
	coap_resource_t* hello_resource;

	/* Prepare the CoAP server socket */ 
	coap_address_init(&serv_addr);
	serv_addr.addr.sin.sin_family      = AF_INET;
	serv_addr.addr.sin.sin_addr.s_addr = INADDR_ANY;
	serv_addr.addr.sin.sin_port        = htons(5683); //default port for CoAP

	// create a context for this server. we will add the necessary resources
	// to implement the services we support below.
	ctx = coap_new_context(&serv_addr);
	if (!ctx) exit(EXIT_FAILURE);

	// Initialize the CoAP library resources for the server. We set
	// the resources for the services that this server is providing.
	// To access this resource the client will specify this name in
	// the URI such as in a URI of:
	//    coap://127.0.0.1/hello
	// Next register the handler for this resource. The function is called
	// when the type of HTTP request is received with the specified URI.
	hello_resource = coap_resource_init((unsigned char *)"hello", 5, 0);
	coap_register_handler(hello_resource, COAP_REQUEST_GET, hello_handler);
	coap_add_resource(ctx, hello_resource);

	// Infinite loop for server to listen for incoming connections
	// When a connect request comes in we will pass it on to the
	// libcoap handler to properly dispatch the requested based on
	// the URI.
	while (1) {
		fd_set   readfds;    

		FD_ZERO(&readfds);
		FD_SET( ctx->sockfd, &readfds );
		int result = select( FD_SETSIZE, &readfds, 0, 0, NULL );
		if ( result < 0 ) /* if socket error */
		{
			exit(EXIT_FAILURE);
		} 
		else if ( result > 0 && FD_ISSET( ctx->sockfd, &readfds )) /* if socket read*/
		{ 
			// dispatch the read for processing.
			coap_read( ctx );
		} 
		else {
			printf ("\nselect() returned, no read.");
		}
	}

	return 0;
}
