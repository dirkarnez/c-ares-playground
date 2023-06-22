// #include <stdio.h>
// #include <stdlib.h>
// // #include <arpa/inet.h>

// #include <winsock2.h>
// #include <ws2tcpip.h>

// #include "ares.h"

// #include <iostream>
// #include <functional>
// #include <list>
// #include <map>
// #include <memory>
// #include <set>
// #include <string>
// #include <utility>
// #include <sstream>
// #include <vector>

// int inet_pton(int af, const char *src, void *dst)
// {
//   struct sockaddr_storage ss;
//   int size = sizeof(ss);
//   char src_copy[INET6_ADDRSTRLEN + 1];

//   ZeroMemory(&ss, sizeof(ss));
//   /* stupid non-const API */
//   strncpy(src_copy, src, INET6_ADDRSTRLEN + 1);
//   src_copy[INET6_ADDRSTRLEN] = 0;

//   if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0)
//   {
//     switch (af)
//     {
//     case AF_INET:
//       *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
//       return 1;
//     case AF_INET6:
//       *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
//       return 1;
//     }
//   }
//   return 0;
// }

// const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
// {
//   struct sockaddr_storage ss;
//   unsigned long s = size;

//   ZeroMemory(&ss, sizeof(ss));
//   ss.ss_family = af;

//   switch (af)
//   {
//   case AF_INET:
//     ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
//     break;
//   case AF_INET6:
//     ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
//     break;
//   default:
//     return NULL;
//   }
//   /* cannot direclty use &size because of strict aliasing rules */
//   return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0) ? dst : NULL;
// }

// using namespace std;

// std::string HexDump(std::vector<byte> data)
// {
//   std::stringstream ss;
//   for (size_t ii = 0; ii < data.size(); ii++)
//   {
//     char buffer[2 + 1];
//     sprintf(buffer, "%02x", data[ii]);
//     ss << buffer;
//   }
//   return ss.str();
// }

// std::string HexDump(const byte *data, int len)
// {
//   return HexDump(std::vector<byte>(data, data + len));
// }

// std::string HexDump(const char *data, int len)
// {
//   return HexDump(reinterpret_cast<const byte *>(data), len);
// }

// std::string AddressToString(const void *vaddr, int len)
// {
//   const byte *addr = reinterpret_cast<const byte *>(vaddr);
//   std::stringstream ss;
//   if (len == 4)
//   {
//     char buffer[4 * 4 + 3 + 1];
//     sprintf(buffer, "%u.%u.%u.%u",
//             (unsigned char)addr[0],
//             (unsigned char)addr[1],
//             (unsigned char)addr[2],
//             (unsigned char)addr[3]);
//     ss << buffer;
//   }
//   else if (len == 16)
//   {
//     for (int ii = 0; ii < 16; ii += 2)
//     {
//       if (ii > 0)
//         ss << ':';
//       char buffer[4 + 1];
//       sprintf(buffer, "%02x%02x", (unsigned char)addr[ii], (unsigned char)addr[ii + 1]);
//       ss << buffer;
//     }
//   }
//   else
//   {
//     ss << "!" << HexDump(addr, len) << "!";
//   }
//   return ss.str();
// }

// std::string StatusToString(int status)
// {
//   switch (status)
//   {
//   case ARES_SUCCESS:
//     return "ARES_SUCCESS";
//   case ARES_ENODATA:
//     return "ARES_ENODATA";
//   case ARES_EFORMERR:
//     return "ARES_EFORMERR";
//   case ARES_ESERVFAIL:
//     return "ARES_ESERVFAIL";
//   case ARES_ENOTFOUND:
//     return "ARES_ENOTFOUND";
//   case ARES_ENOTIMP:
//     return "ARES_ENOTIMP";
//   case ARES_EREFUSED:
//     return "ARES_EREFUSED";
//   case ARES_EBADQUERY:
//     return "ARES_EBADQUERY";
//   case ARES_EBADNAME:
//     return "ARES_EBADNAME";
//   case ARES_EBADFAMILY:
//     return "ARES_EBADFAMILY";
//   case ARES_EBADRESP:
//     return "ARES_EBADRESP";
//   case ARES_ECONNREFUSED:
//     return "ARES_ECONNREFUSED";
//   case ARES_ETIMEOUT:
//     return "ARES_ETIMEOUT";
//   case ARES_EOF:
//     return "ARES_EOF";
//   case ARES_EFILE:
//     return "ARES_EFILE";
//   case ARES_ENOMEM:
//     return "ARES_ENOMEM";
//   case ARES_EDESTRUCTION:
//     return "ARES_EDESTRUCTION";
//   case ARES_EBADSTR:
//     return "ARES_EBADSTR";
//   case ARES_EBADFLAGS:
//     return "ARES_EBADFLAGS";
//   case ARES_ENONAME:
//     return "ARES_ENONAME";
//   case ARES_EBADHINTS:
//     return "ARES_EBADHINTS";
//   case ARES_ENOTINITIALIZED:
//     return "ARES_ENOTINITIALIZED";
//   case ARES_ELOADIPHLPAPI:
//     return "ARES_ELOADIPHLPAPI";
//   case ARES_EADDRGETNETWORKPARAMS:
//     return "ARES_EADDRGETNETWORKPARAMS";
//   case ARES_ECANCELLED:
//     return "ARES_ECANCELLED";
//   default:
//     return "UNKNOWN";
//   }
// }

// // C++ wrapper for struct hostent.
// struct HostEnt
// {
//   HostEnt() : addrtype_(-1) {}
//   HostEnt(const struct hostent *hostent);
//   std::string name_;
//   std::vector<std::string> aliases_;
//   int addrtype_; // AF_INET or AF_INET6
//   std::vector<std::string> addrs_;
// };
// std::ostream &operator<<(std::ostream &os, const HostEnt &result);

// // Structure that describes the result of an ares_host_callback invocation.
// struct HostResult
// {
//   // Whether the callback has been invoked.
//   bool done_;
//   // Explicitly provided result information.
//   int status_;
//   int timeouts_;
//   // Contents of the hostent structure, if provided.
//   HostEnt host_;
// };
// std::ostream &operator<<(std::ostream &os, const HostResult &result);

// std::ostream &operator<<(std::ostream &os, const HostResult &result)
// {
//   os << '{';
//   if (result.done_)
//   {
//     os << StatusToString(result.status_) << " " << result.host_;
//   }
//   else
//   {
//     os << "(incomplete)";
//   }
//   os << '}';
//   return os;
// }

// HostEnt::HostEnt(const struct hostent *hostent) : addrtype_(-1)
// {
//   if (!hostent)
//     return;
//   if (hostent->h_name)
//     name_ = hostent->h_name;
//   if (hostent->h_aliases)
//   {
//     char **palias = hostent->h_aliases;
//     while (*palias != nullptr)
//     {
//       aliases_.push_back(*palias);
//       palias++;
//     }
//   }
//   addrtype_ = hostent->h_addrtype;
//   if (hostent->h_addr_list)
//   {
//     char **paddr = hostent->h_addr_list;
//     while (*paddr != nullptr)
//     {
//       std::string addr = AddressToString(*paddr, hostent->h_length);
//       addrs_.push_back(addr);
//       paddr++;
//     }
//   }
// }

// std::ostream &operator<<(std::ostream &os, const HostEnt &host)
// {
//   os << '{';
//   os << "'" << host.name_ << "' "
//      << "aliases=[";
//   for (size_t ii = 0; ii < host.aliases_.size(); ii++)
//   {
//     if (ii > 0)
//       os << ", ";
//     os << host.aliases_[ii];
//   }
//   os << "] ";
//   os << "addrs=[";
//   for (size_t ii = 0; ii < host.addrs_.size(); ii++)
//   {
//     if (ii > 0)
//       os << ", ";
//     os << host.addrs_[ii];
//   }
//   os << "]";
//   os << '}';
//   return os;
// }

// // void callback(void *arg, int status, int timeouts, struct hostent *hostent)
// // {
// //     if (status != ARES_SUCCESS)
// //     {
// //         printf("Failed to lookup %s: %s\n", (char *)arg, ares_strerror(status));
// //         return;
// //     }

// //     struct in_addr addr;
// //     memcpy(&addr, hostent->h_addr_list[0], sizeof(struct in_addr));
// //     printf("%s has address %s\n", (char *)arg, inet_ntoa(addr));
// // }

// void HostCallback(void *data, int status, int timeouts,
//                   struct hostent *hostent)
// {
//   //   EXPECT_NE(nullptr, data);
//   //   if (data == nullptr)
//   //     return;
//   if (status == ARES_SUCCESS)
//     std::cout << hostent->h_name << "\n";
//   else
//     std::cout << "lookup failed: " << status << '\n';

//   HostResult *result = reinterpret_cast<HostResult *>(data);
//   result->done_ = true;
//   result->status_ = status;
//   result->timeouts_ = timeouts;
//   if (hostent)
//     result->host_ = HostEnt(hostent);

//   std::cerr << "HostCallback(" << *result << ")" << std::endl;
// }

// int main()
// {
//   int status;
//   const char *domain = "google.com";

//   status = ares_library_init(ARES_LIB_INIT_ALL);
//   if (status != ARES_SUCCESS)
//   {
//     printf("Failed to initialize c-ares library: %s\n", ares_strerror(status));
//     return 1;
//   }

//   // Create a channel for asynchronous DNS resolution
//   ares_channel channel;
//   struct ares_options options;
//   int optmask = ARES_OPT_FLAGS;
//   options.flags = ARES_FLAG_USEVC | ARES_FLAG_STAYOPEN;
//   status = ares_init_options(&channel, &options, optmask);
//   if (status != ARES_SUCCESS)
//   {
//     // Handle error
//     return 1;
//   }

//   struct ares_addr_node servers;
//   servers.family = AF_INET6;
//   string t = "8.8.8.8";
//   inet_pton(AF_INET6, t.c_str(), &servers.addr.addr6);
//   servers.next = nullptr;

//   // Set the DNS servers to use

//   ares_set_servers(channel, &servers);

//   // status = ares_init(&channel);
//   // if (status != ARES_SUCCESS)
//   // {
//   //     printf("Failed to initialize c-ares channel: %s\n", ares_strerror(status));
//   //     return 1;
//   // }
//   // ares_set_servers_csv(channel, "8.8.8.8,8.8.4.4");

//   // ares_gethostbyname(channel, domain, AF_INET, callback, (void *)domain);

//   HostResult result;
//   ares_gethostbyname(channel, "google.com", AF_INET6, HostCallback, &result);

//   ares_destroy(channel);
//   ares_library_cleanup();
//   return 0;
// }

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <ares.h>

int inet_pton(int af, const char *src, void *dst)
{
  struct sockaddr_storage ss;
  int size = sizeof(ss);
  char src_copy[INET6_ADDRSTRLEN + 1];

  ZeroMemory(&ss, sizeof(ss));
  /* stupid non-const API */
  strncpy(src_copy, src, INET6_ADDRSTRLEN + 1);
  src_copy[INET6_ADDRSTRLEN] = 0;

  if (WSAStringToAddress(src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0)
  {
    switch (af)
    {
    case AF_INET:
      *(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
      return 1;
    case AF_INET6:
      *(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
      return 1;
    }
  }
  return 0;
}

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
  struct sockaddr_storage ss;
  unsigned long s = size;

  ZeroMemory(&ss, sizeof(ss));
  ss.ss_family = af;

  switch (af)
  {
  case AF_INET:
    ((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
    break;
  case AF_INET6:
    ((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
    break;
  default:
    return NULL;
  }
  /* cannot direclty use &size because of strict aliasing rules */
  return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0) ? dst : NULL;
}

void callback(void *arg, int status, int timeouts, struct hostent *host)
{
  if (status == ARES_SUCCESS)
  {
    char **p = host->h_addr_list;
    char ip[INET6_ADDRSTRLEN];
    while (*p != NULL)
    {
      inet_ntop(host->h_addrtype, *p, ip, sizeof(ip));
      printf("google.com resolved to %s\n", ip);
      ++p;
    }
  }
  else
  {
    fprintf(stderr, "ares_gethostbyname failed: %s\n", ares_strerror(status));
  }
}

int main()
{
  WSADATA wsa_data;
  int status = WSAStartup(MAKEWORD(2, 2), &wsa_data);
  if (status != 0)
  {
    fprintf(stderr, "WSAStartup failed: %d\n", status);
    return 1;
  }
  ares_library_init(ARES_LIB_INIT_ALL);

  ares_channel channel;
  const char *google_dns_servers[] = {"8.8.8.8", "8.8.4.4"};
  struct in_addr server_addrs[sizeof(google_dns_servers) / sizeof(google_dns_servers[0])];

  for (int i = 0; i < sizeof(google_dns_servers) / sizeof(google_dns_servers[0]); ++i)
  {
    inet_pton(AF_INET, google_dns_servers[i], &server_addrs[i]);
  }
  struct ares_options options;
  int optmask = ARES_OPT_FLAGS | ARES_OPT_SERVERS;
  options.flags = ARES_FLAG_USEVC | ARES_FLAG_STAYOPEN;
  options.servers = server_addrs;
  options.nservers = sizeof(server_addrs) / sizeof(server_addrs[0]);
  status = ares_init_options(&channel, &options, optmask);
  if (status != ARES_SUCCESS)
  {
    fprintf(stderr, "ares_init_options failed: %s\n", ares_strerror(status));
    return 1;
  }
  ares_gethostbyname(channel, "google.com", AF_INET, callback, NULL);
  // Wait for DNS resolution to complete
  while (1)
  {
    fd_set read_fds, write_fds;
    struct timeval tv;
    int nfds;

    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    ares_fds(channel, &read_fds, &write_fds);

    if (ares_fds(channel, &read_fds, &write_fds) <= 0)
    {
      break;
    }

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    nfds = select(FD_SETSIZE, &read_fds, &write_fds, NULL, &tv);
    if (nfds < 0)
    {
      fprintf(stderr, "select() failed\n");
      break;
    }

    ares_process(channel, &read_fds, &write_fds);
  }
  ares_destroy(channel);
  ares_library_cleanup();

  WSACleanup();

  return 0;
}