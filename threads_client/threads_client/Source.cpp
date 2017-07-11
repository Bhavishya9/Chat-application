#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>

DWORD WINAPI ThreadFunc(void* data) {
	while (1)
	{
		char message[100];
		memset(message, '\0', 100);
		int index = 0;
		FILE *file = fopen("C:\\Users\\Bhavisya\\Documents\\thread_server.txt", "r+");
		if (file == NULL)
			return -1;
		char ch;
		ch = fgetc(file);
		while (ch == EOF)
		{
			ch = fgetc(file);
		}
		int flag;
		fscanf(file, "%d", &flag);
		while (flag == 0)
		{
			fseek(file, 0, 0);
			fscanf(file, "%d", &flag);

		}
		ch = fgetc(file);
		while (ch != '\n')
		{
			message[index++] = ch;
			ch = fgetc(file);
		}
		message[index] = '\0';
		printf("Server: %s\n", message);
		fseek(file, 0, SEEK_SET);
		fprintf(file, "%d", 0);
		fclose(file);
	}
}

int main(void)
{
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
	while (1)
	{
		if (thread)
		{
			FILE *fp = fopen("C:\\Users\\Bhavisya\\Documents\\thread_client.txt", "w+");
			fprintf(fp, "%d", 0);
			printf("Client");
			char ch;
			while ((ch = getchar()) != '\n')
			{
				fputc(ch, fp);
			}
			fputc('\n', fp);
			fseek(fp, 0, SEEK_SET);
			fprintf(fp, "%d", 1);
			fclose(fp);
		}
	}
}