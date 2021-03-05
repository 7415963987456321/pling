#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>

#define ADDR_BUFSIZE 17
#define _PORT 80
#define _SERVER "92.43.192.120" // Temporary
#define VERSION "0.1"

int sockfd;
struct timeval timeout;
struct timespec start;
struct timespec end;

int ping_time(struct timespec *start, struct timespec *end, struct sockaddr_in addr) {
    printf("pinging\n");

    // Timing and all actual ping happens here
    clock_gettime(CLOCK_MONOTONIC, start); // Start timer

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));

    clock_gettime(CLOCK_MONOTONIC, end); // End timer

    if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) != 0){
        printf("Failed to scan \n");
    } else{
        printf("Success\n");
    }
    return 0;
}

// TODO: support IPv6
void read_input(struct sockaddr_in *addr) {
    volatile uint8_t ip[4];
    char IPbuf[12];

    while (fscanf(stdin, "%s", IPbuf)) {
        // Implement
    }
    /* while(fscanf(stdin, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]) == 4){ */
    /*     printf("%hhu.%hhu.%hhu.%hhu\n", ip[0], ip[1], ip[2], ip[3]); */

    /*     /1* ping_time(&start, &end, addr); *1/ */
    /* } */
}

void help(void) {
    printf("This program takes a list of IP-addresses and pings them.\n");
    printf("The time of the response is measured and reported for each IP\n");
    printf("\n");
    printf("The following options are available\n");
    printf("-v, --version \t Print version\n");
    printf("-h, --help \t Display this help message\n");
    printf("-t, --timeout \t Set timeout for pings\n");
    printf("-n, --number \t The number of pings for each IP \n");
}

void version(void) {
    printf("Version: %s\n", VERSION);
    printf("Written by: Hrafnkell Sigurðarson\n");
}

int main(int argc, char *argv[]) {
    struct sockaddr_in addr = {AF_INET, htons(_PORT), inet_addr(_SERVER)};

    // Declare timeout for ping.
    timeout.tv_sec  = 1;
    timeout.tv_usec = 0;


    // Deal with input
    int choice;
    while (1) {
        static struct option long_options[] = {
            {"version", no_argument,       0, 'v'},
            {"number",  required_argument, 0, 'n'},
            {"timeout", required_argument, 0, 't'},
            {"help",    no_argument,       0, 'h'},
            {0,0,0,0}
        };

        int option_index = 0;

        choice = getopt_long( argc, argv, "vh",
                long_options, &option_index);

        if (choice == -1)
            break;

        switch(choice) {
            case 'v':
                version();
                return EXIT_SUCCESS;

            case 'h':
                help();
                return EXIT_SUCCESS;

            case 'n':
                // Implement this later
                break;
            case 't':
                timeout.tv_sec = atoi(optarg);
                timeout.tv_sec = 0;
                break;

            case '?':
                /* getopt_long will have already printed an error */
                break;

            default:
                return EXIT_FAILURE;
        }
    }

    // Setup socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    read_input(&addr);
    ping_time(&start, &end, addr);

    printf("%ld\n", end.tv_sec);
    printf("%ld\n", end.tv_nsec);

    close(sockfd);
    return 0;
}
