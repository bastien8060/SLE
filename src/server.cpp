// Driver code

std::vector<std::string> split(std::string s, int l)
{
  int len = s.length();
  if (s.empty()) {
    std::vector<std::string> entries;
    entries.push_back("null");
    return entries;
  }
  const char *c = s.c_str();
  char buffer[l];
  std::vector<std::string> entries;
  entries.reserve(int(s.length() / l) + 1);

  int d = 0;
  for (int i = 0; i < s.length() - 1;)
  {
    if (d != l)
    {
      buffer[d] = c[i];
      d++;
      i++;
    }
    else
    {
      entries.push_back(std::string(buffer, l));

      //Clear array
      memset(buffer, 0, l);
      d = 0;
    }
  }

  return entries;
}

int server_start() {
  while (true) {
    int sockfd;
    char buffer[MAXLINE];
    //char *hello = (char *)"Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
    }
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
      printf("setsockopt(SO_REUSEADDR) failed");

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
              sizeof(servaddr)) < 0 )
    {
      perror("bind failed");
      exit(EXIT_FAILURE);
    }

    int n;
    unsigned int len;

    len = sizeof(cliaddr);  //len is value/resuslt
    bzero(buffer, MAXLINE);
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                 &len);
    buffer[n] = '\0';
    //printf("Client : %s\n", buffer);


    std::string fullresp = parse(buffer);
    //std::cout << "\n";



    std::vector<std::string> splittexts;
    if (fullresp.size() > 1020) {
      //splittexts = split(fullresp, 1024);

      for (size_t i = 0; i < fullresp.size(); i += 1024)
        splittexts.push_back(fullresp.substr(i, 1024));



    } else {
      splittexts.push_back(fullresp);
    }



    for (int i = 0; i < splittexts.size(); ++i)
    {

      //std::cout << "Sending part [" << i + 1 << "] for " << splittexts.size() << " parts and " << fullresp.size() << "\n";
      //std::cout << "\n\n\n" << << "\n\n\n"
      std::string tmp = splittexts[i];

      const char *hello = tmp.c_str();
      sendto(sockfd, (const char *)hello, strlen(hello),
             MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
             len);
      usleep(2);

    }




    std::string tmp = "@@@";
    const char *hello = tmp.c_str();
    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
           len);
    usleep(2);
    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
           len);
    //printf("End message sent.\n");


    close(sockfd);
  }
  return 0;
}