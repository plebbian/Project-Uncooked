#include <stdio.h>
#include <WinSock2.h>

// This tells, specifically, the Microsoft Visual C compiler to use the ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA d;
	// WSAStartup is requesting Winsock 2.2, and then it takes that
	// initialization information and stores it in WSADATA
	if (WSAStartup(MAKEWORD(2, 2), &d)) {
		printf("Failed to initialize.\n");
		return -1;
	}

	printf("OK.\n");
	return 0;
}