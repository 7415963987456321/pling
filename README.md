# PLING
## A work in progress

I needed a small utility to ping a list of VPN servers and find the one with
the best ping.

Wrote it mostly just to learn how to deal with sockets and network stuff in C.

### Input:
A list of IPv4-addresses

### Output:
The IP with the lowest ping.


# TODO:
* Convert nanosecond time to human-readable
* Write tests?
* Figure out in_addr_t (what the hell is going on with it?)
* Sort the output
* Implement IPv6 capability
* Improve makefile
* profit???
