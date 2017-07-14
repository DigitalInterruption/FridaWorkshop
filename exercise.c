#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define MESSAGE_NUM 5
char* encryptString(char*,char*,size_t);
char* getKey(int);
void decryptAllMessage();
int checkPassword();
int getMessage(char*);
void printAllEncryptedMessages();

struct messages{
	char* key;
	char* encryptedString;
	size_t len;
}message[MESSAGE_NUM];


int main()
{
	srand(time(NULL));   
	char readString[255];
	for(int i=0;i<MESSAGE_NUM;++i)	{
		memset(readString,0,255);
		printf("Enter Message:\n");
		int len = getMessage(readString);
		char* key = getKey(len);
		char* encryptedString = encryptString(readString,key,len);
		message[i].key=key;
		message[i].encryptedString = encryptedString;
		message[i].len = len;		
	}
	
	printf("Enter Password\n");
	if(checkPassword())
	{
		decryptAllMessage();
	}	
	else
		printAllEncryptedMessages();

	for(int i=0;i<MESSAGE_NUM;++i)
	{
		free(message[i].encryptedString);
		free(message[i].key);
	}
}

int getMessage(char* message)
{
	return read(0,message,100);
}

int checkPassword()
{
	char password[255];
	size_t passwordLen = read(0,password,100);
	return (passwordLen != 0) && (!memcmp(password,"password",8));

}

char* getKey(int len)
{
	char* key = malloc(len);
	for(int i=0;i<len;++i)
	{
		key[i]=rand();
	}
	return key;
}

char* encryptString(char* val,char* key, size_t len)
{
	char* encryptedMessage = malloc(len);
		
	for(int i=0;i<len;++i)	
	{
		encryptedMessage[i] = val[i]^key[i];
	}
	return encryptedMessage;
}

void printAllEncryptedMessages()
{	
	for(int i=0;i<MESSAGE_NUM;++i)
	{
		printf("message %d:",i);
		for(int j=0;j<message[i].len;++j)
		{
			printf("%c",message[i].encryptedString[j]);
		}
		printf("\n");
	}
	
}

void decryptAllMessage()
{
	for(int i=0;i<MESSAGE_NUM;++i)
	{
		printf("message %d:",i);
		for(int j=0;j<message[i].len;++j)
		{
			printf("%c",message[i].encryptedString[j]^message[i].key[j]);
		}
	}	
}
