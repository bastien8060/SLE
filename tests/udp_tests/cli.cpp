#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>

#include <chrono>
#include <thread>


using namespace std;
using namespace std::chrono;


#define PORT      6770
#define MAXLINE   1024

#define CPS_BM    0
#define CPS_120   8
#define CPS_60    16
#define CPS_30    32


bool isCornerPresent(std::string str, std::string pattern)
{
    if (str.find(pattern) != std::string::npos) {
        return true;
    }
    else {
        return false;
    }

    return false;
}

// Driver code
int main() {
    time_point<system_clock> t = system_clock::now();
    int req = 4;

    std::string cmd1 = "@[polygon]{c:10,56|50,63|32,90;}";
    std::string cmd2 = "@[circle]{r:50;c:10,56;}";
    std::string cmd3 = "#[screensize]{x:500;y:650;}";
    std::string cmd4 = "@@@";
    vector<std::string> cmd;

    cmd.push_back(cmd1);
    cmd.push_back(cmd2);
    cmd.push_back(cmd3);
    cmd.push_back(cmd4);

    for (int i = 0; i < req; ++i)
    {

        int sockfd;
        char buffer[MAXLINE];
        //std::string tmp = std::to_string(i);
        std::string tmp = cmd[i];
        std::cout << tmp;
        const char *hello = tmp.c_str();
        struct sockaddr_in     servaddr;

        // Creating socket file descriptor
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }


        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        int n;
        unsigned int len;

        sendto(sockfd, (const char *)hello, strlen(hello),
               MSG_CONFIRM, (const struct sockaddr *) &servaddr,
               sizeof(servaddr));
        //printf("Hello message sent.\n");

        //std::cout << i;
        bzero(buffer, MAXLINE);

        std::string totalmessage;
        int totalsize;

        std::string message = buffer;
        std::string pattern = "@@@";


        while (!isCornerPresent(message,pattern)){
            n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *) &servaddr,
                     &len);
            totalsize += n;
            std::string thismsg = buffer;
            totalmessage += thismsg;

        }
        
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);

        shutdown(sockfd, 1);
        usleep(100);
        close(sockfd);

        t += milliseconds(CPS_60);
        this_thread::sleep_until(t);

    }
    return 0;
}