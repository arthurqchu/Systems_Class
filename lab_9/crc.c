#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *unsigned_to_binary(unsigned long msg, int size)
{
	//This function converts unsigned longs, in hexadecimal, to binary
	char* b = (char *)malloc(size + 1); //allocate space for the binary result
	b[0] = '\0';

	int z;
	for (z = (1<<(size-1)); z > 0; z >>= 1)
	{
		//For the specified size of the binary number, iterates through the unsigned long and either concatenates a 1 or 2 to the binary
		strcat(b, ((msg & z) == z) ? "1" : "0");
	}

	return b; //Returns the binary representation of the passed unsigned long
}

unsigned long crc_remainder(unsigned long msg, unsigned long check, int mlen, int clen) {
	unsigned long newmsg = msg << (clen-1); //Prepares new message by taking the first message and left shifting it by the length of the divisor
	unsigned long n;
	int i;
	for (i = mlen; i > 0; i--) { //Begins iterating an amount of times equal to the length of the message
		if ((newmsg & (1 << (i+clen-2))) != 0) { //Divides the newmessage by the divisor
			n = check << (i - 1);
			newmsg = newmsg ^ n;
		}
	}
	return newmsg & ((1 << clen) - 1); //Return binary representation
}

int main() { 
	unsigned long msg = 0xC74A;
	unsigned long divisor = 0xB;
	unsigned long newmsg = (msg << 3) + crc_remainder(msg, divisor, 16, 4); //Divides the hexadecimal message by the hexadecimal divisor and creates new messsage with the remainder appended to the end of the message
	unsigned long rem, newrem;
	printf("Message is: ");
	printf("%s\n", unsigned_to_binary(msg, 16)); //Prints the hexadecimal message into binary
	printf("Divisor is: ");
	printf("%s\n", unsigned_to_binary(divisor, 4)); //Prints the hexadecimal divisor into binary
	rem = crc_remainder(msg, divisor, 16, 4); //Divides the message,in hexadecimal, by the divisor, in hexadecimal, and stores the remainder, in hexadecimal
	printf("Remainder of message and divisor: ");
	printf("%s\n", unsigned_to_binary(rem, 3)); //Prints hexadecimal remainder in binary
	printf("Message with added bits is: ");
	printf("%s\n", unsigned_to_binary(newmsg, 19)); //Prints hexadecimal new message in binary
	newrem = crc_remainder(newmsg, divisor, 19, 4); //Divides the new message by the divisor and stores the new remainder in hexadecimal
	printf("Remainder is: ");
	printf("%s\n", unsigned_to_binary(newrem, 3)); //Prints hexadecimal new remainder in binary


	printf("\nEXAMPLE FROM BOOK:\n\n");
	char * ptr;
	msg = strtoul("10011010", &ptr, 2); //Converts a string to an unsigned long and stores it in msg
	divisor = strtoul("1101", &ptr, 2); //Converts a string to an unsigned long and stores it in divisor

	printf("Message is: ");
	printf("%s\n", unsigned_to_binary(msg, 8)); //Prints unsigned long message to binary
	printf("Divisor is: ");
	printf("%s\n", unsigned_to_binary(divisor, 4)); // Prints unsigned long divisor to binary
	rem = crc_remainder(msg, divisor, 8, 4); //Divides message by divisor and stores the remainderm antoher unsigned long in rem
	printf("Remainder of message and divisor: ");
	printf("%s\n", unsigned_to_binary(rem, 3)); //Prints the unsigned long remainder in binary
	newmsg = (msg << 3) + rem; // appends the remainder to the message and stores it as new message
	printf("Message with added bits is: ");
	printf("%s\n", unsigned_to_binary(newmsg, 11)); //Prints the new message in binary
	newrem = crc_remainder(newmsg, divisor, 11, 4); //Divides the new message by the divisor and stores it as newrem
	printf("Remainder is: ");
	printf("%s\n", unsigned_to_binary(newrem, 3)); //Prints the new remainder in binary
	return 0;
}
