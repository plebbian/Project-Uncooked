// THIS IS FOR WINDOWS SYSTEMS, AND WILL NOT COMPILE ON UNIX OR WSL
// 
// 
// 
// This part is a macro that has to be defined
// so that the proper version of the windows headers are included.
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600 // not sure what that hexadecimal value is. Maybe a version number
#endif

// These are the headers that are required to list the network adapters.
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <stdlib.h>

// These are the libraries needed to run the program with the Microsoft Visual C Compiler
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

int main() {

	// Same initialization seen in win_init.c
	WSADATA d;

	if (WSAStartup(MAKEWORD(2, 2), &d)) {
		printf("Initialization failed.\n");
		return -1;
	}

	// This section is going to get a little heavy...
	// This section allocates memory for the network adapters, and we request adapters' addresses from Windows
	// using GetAdapterAddresses()

	// DWORD => Double Word => alias for unsigned long
	DWORD asize = 20000;			// This is the variable that holds the adapters' address buffer
	PIP_ADAPTER_ADDRESSES adapters;

	do {
		adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);

		if (!adapters) {
			//						 proof that DWORD is an alias for unsigned long
			printf("Couldn't allocate %ld bytes for adapters.\n", asize);
			WSACleanup();
			return -1;
		}

		// 1st AF_UNSPEC says that we want both IPv4(AF_INET) and IPv6(AF_INET6) Addresses
		// 2nd GAA_FLAG_INCLUDE_PREFIX is required to request a list of addresses
		// 3rd argument is the actual adapter
		// 4th argument is the adapters buffer size
		int r = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, adapters, &asize);

		// This means that our buffer was not big enough for all of the addresses
		if (r == ERROR_BUFFER_OVERFLOW) {
			printf("GetAdapterAddresses wants %ld bytes.\n", asize);
			free(adapters);
		}
		// GetAdaptersAddresses() returns ERROR_SUCCESS when successful
		else if (r == ERROR_SUCCESS) {
			break;
		}
		else {
			printf("Error from GetAdaptersAddresses: %d\n", r);
			free(adapters);
			WSACleanup();
			return -1;
		}
	} while (!adapters);

	// GetAdapterAddresses() writes a linked list into adapters, so we just have to
	// loop through them and print the information

	PIP_ADAPTER_ADDRESSES adapter = adapters;
	while (adapter) {
		printf("\nAdapter name: %S\n", adapter->FriendlyName);

		PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
		while (address) {
			printf("\t%s", address->Address.lpSockaddr->sa_family == AF_INET ? "IPv4" : "IPv6");

			char ap[100];

			// This converts the address into a standard notation address.
			getnameinfo(address->Address.lpSockaddr, address->Address.iSockaddrLength, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
			printf("\t%s\n", ap);

			address = address->Next;
		}
		adapter = adapter->Next;
	}

	free(adapters);
	WSACleanup();
	return 0;
}