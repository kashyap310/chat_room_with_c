```c
status_code_s set_file_buffer(const char *src_Dir, char *request_file, char *buffer, reqType reqMethod)
{
    status_code_s return_data;
    char file_path[256]; // Allocate enough space for file_path
    struct stat file_stat;

    // Ensure src_Dir is not null
    if (src_Dir == NULL)
    {
        fprintf(stderr, "Invalid directory or file name\n");
        return_data.buffer_allocation_state = 0;
        return_data.status_code = "404 Not Found";
        return return_data;
    }
    if (strlen(request_file) == 1)
    { // there is still null char in the path
        printf("Resuest for Index.html");
        request_file = "index.html";
    }

    // For GET request method
    if (reqMethod == 0)
    {
        // Safely copy the source directory into file_path
        strncpy(file_path, src_Dir, sizeof(file_path) - 1);
        file_path[sizeof(file_path) - 1] = '\0'; // Ensure null termination

        // Concatenate the request file to the directory path
        strncat(file_path, request_file, sizeof(file_path) - strlen(file_path) - 1);
        printf("Full path is %s\n", file_path);

        int file_fd = open(request_file, O_RDONLY);
        if (file_fd < 0)
        {
            perror("open error");
            return_data.buffer_allocation_state = 1;
            return_data.status_code = "404 Not Found";
            return return_data;
        }
        if (fstat(file_fd, &file_stat) < 0)
        {
            perror("fstat error\n");
            close(file_fd);
            return_data.buffer_allocation_state = 1;
            return_data.status_code = "404 Not Found";
            return return_data;
        }

        // read fiel content into buffer
        size_t file_size = file_stat.st_size;
        buffer = malloc(file_size);
        if (buffer == NULL)
        {
            perror("malloc error\n");
            close(file_fd);
            return_data.buffer_allocation_state = 1;
            return_data.status_code = "404 Not Found";
            return return_data;
        }
        ssize_t bytes_read = read(file_fd, buffer, file_size);
        if (bytes_read < 0)
        {
            perror("read error");
            free(buffer);
            close(file_fd);
            return_data.buffer_allocation_state = 1;
            return_data.status_code = "404 Not Found";
            return return_data;
        }
        close(file_fd);
    }
    return_data.buffer_allocation_state = 1;
    return_data.status_code = "404 Not Found";
    return return_data;
}
```

```c
// creating Response
    char *buffer = malloc(MAX_READ_BUFFER * sizeof(char));
    status_code_s response_content;
    response_content = set_file_buffer(SRC_DIR, parms.path, buffer, parms.reqMethod);
    if (response_content.buffer_allocation_state == 1)
    {
        perror("response struct error\n");
    }

    // Calculate the length of the HTML content
    size_t content_length = strlen(buffer);
    char *html_content_buffer = (char *)realloc(buffer, content_length);

    if (html_content_buffer == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free(buffer); // Clean up the original buffer if realloc fails
        
    }

    // Use the resized buffer (Note: content may be truncated)
    // Ensure the buffer is null-terminated
    html_content_buffer[content_length - 1] = '\0';
    printf("Buffer content after resizing: %s\n", html_content_buffer);

    // Construct the response header with the correct Content-Length
    char *response = malloc(MAX_READ_BUFFER * sizeof(char)); // Ensure this buffer is large enough
    const char *mime_type;

    if (strlen(parms.path) == 1)
    { // there is still null char in the
        mime_type = get_mime_type("index.html");
    }
    else
    {

        mime_type = get_mime_type(parms.path);
    }

    snprintf(response, MAX_READ_BUFFER,
             "HTTP/1.1 %s\r\n"
             "Content-Type: %s; charset=UTF-8\r\n"
             "Content-Length: %zu\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s",
             response_content.status_code, mime_type, content_length, html_content_buffer);

```