c-ares-playground
=================
### Using
- [dirkarnez/c-ares-prebuilt](https://github.com/dirkarnez/c-ares-prebuilt)

### ChatGPT
> c-ares is a C library that provides asynchronous DNS resolution functionality. It allows you to perform DNS queries in a non-blocking way, which means that your program can continue to do other tasks while DNS queries are in progress. When the results of the DNS query are available, c-ares notifies your program through a callback function.
> 
> Here's how c-ares works:
> 
> 1. Initialization: Before you can use c-ares, you need to initialize the library by calling `ares_library_init()`. This function initializes the c-ares library and sets up any resources that it needs.
> 
> 2. Channel Creation: Once the library is initialized, you can create a c-ares channel by calling `ares_init()`. A channel is a handle that represents a set of DNS queries that are in progress or waiting to be executed.
> 
> 3. DNS Query: To perform a DNS query, you call one of the `ares_gethostbyname()` functions. These functions take a hostname or IP address as input and begin the DNS resolution process. The function returns immediately, and the query is executed in the background.
> 
> 4. Callback: When the result of the DNS query is available, c-ares notifies your program by calling a callback function that you provide. The callback function takes the results of the DNS query as input, such as the IP address of the hostname.
> 
> 5. Cleanup: After you're done with the channel, you can destroy it by calling `ares_destroy()`. When you're completely done with c-ares, you can cleanup any resources used by the library by calling `ares_library_cleanup()`.
> 
> c-ares supports various types of DNS queries, including A, AAAA, MX, SRV, and TXT records. It also supports asynchronous name resolution using multiple channels, and can be configured for various options such as timeout values and DNS server addresses.
