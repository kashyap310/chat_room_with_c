#include "csock.h"

void funerror(const char *errorMsg)
{
    perror(errorMsg);
    exit(0);
}

reqType getMethodFromString(const char *method)

{
    if (strcmp(method, "GET") == 0)
        return GET;
    if (strcmp(method, "POST") == 0)
        return POST;
    return INVALID_METHOD;
}

requestParms parse(char *request)

{
    char method[10], url[1024], httpV[10];
    requestParms parms;

    // Request parsing with whitespace
    sscanf(request, "%s %s %s", method, url, httpV);
    // printf("%s\n%s\n", method, url);

    reqType r = getMethodFromString(method);
    // printf("Req %d\n",r);
    if (r == INVALID_METHOD)
    {
        printf("INVALID REQUEST FROM CLIENT\n");
    }

    // setup params
    parms.reqMethod = r;
    parms.path = url + 1;

    return parms;
}

const char *get_filename_ext(const char *filename)
{
    // serch string after .
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

char *get_mime_type(char *file_name)
{
    if (strcmp(get_filename_ext(file_name), "html") == 0)
    {
        return "text/html";
    }
    else
    {
        return "application/octet-stream";
    }
}

//  int main()
// {
//     char *req = "GET /index.html HTTP/1.1\r\n"
//                 "Host: www.example.com\r\n"
//                 "Connection: keep-alive\r\n"
//                 "User-Agent: Mozilla/5.0\r\n"
//                 "Accept: text/html\r\n"
//                 "\r\n";
//     requestParms parms = parse(req);

//     // Print the results
//     printf("Request Method: %d\n", parms.reqMethod);
//     printf("Request Path: %s\n", parms.path);

// printf("%s\n", get_filename_ext("test.tiff"));
// printf("%s\n", get_filename_ext("test.blah.tiff"));
// printf("%s\n", get_filename_ext("test."));
// printf("%s\n", get_filename_ext("test"));
// printf("%s\n", get_filename_ext("..."));
//     printf("%s\n", get_filename_ext("test.html"));

//     const char *mime = get_mime_type(get_filename_ext("index.html"));
//     printf("%s MIME\n",mime);

// char *buffer = malloc(MAX_READ_BUFFER*sizeof(char));
// if(buffer==NULL){funerror("malloc");}

// set_file_buffer(SRC_DIR,"index.html",buffer);
// printf("Size of buff %d\n",strlen(buffer));
// printf("%s",buffer);

// free(buffer);
//  }
