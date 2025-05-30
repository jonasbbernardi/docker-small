
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {
    int port = 8080;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 16\r\n"
        "Connection: close\r\n"
        "\r\n"
        "{\"success\":true}";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        write(2, "socket failed\n", 14);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        write(2, "bind failed\n", 12);
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 3);
    write(1, "Servidor rodando...\n", 21);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            write(2, "accept failed\n", 14);
            exit(EXIT_FAILURE);
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, sizeof(buffer));
        if (strncmp(buffer, "GET", 3) != 0) {
            char *method_not_allowed =
                "HTTP/1.1 405 Method Not Allowed\r\n"
                "Content-Length: 0\r\n"
                "Connection: close\r\n"
                "\r\n";
            send(new_socket, method_not_allowed, strlen(method_not_allowed), 0);
            close(new_socket);
            continue;
        }

        send(new_socket, response, strlen(response), 0);
        close(new_socket);
    }

    return 0;
}
