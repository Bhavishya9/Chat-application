#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>

DWORD WINAPI ThreadFunc(void* data) {
	while (1)
	{
		FILE *file = fopen("C:\\Users\\Bhavisya\\Documents\\thread_server.txt", "w+");
		if (file == NULL)
		{
			return -1;
		}
		fprintf(file, "%d", 0);
		printf("Server: ");
		char ch;
		while ((ch = getchar()) != '\n')
		{
			fputc(ch, file);
		}
		fputc(ch, file);
		fseek(file, 0, SEEK_SET);
		fprintf(file, "%d", 1);
		fseek(file, 0, SEEK_SET);
		fscanf(file, "%c", &ch);
		while (ch == '1')
		{
			fseek(file, 0, SEEK_SET);
			fscanf(file, "%c", &ch);
		}
		fclose(file);
	}
	return 0;
}


int main(void)
{
	char message[100];
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
	while (1)
	{
		if (thread)
		{
			memset(&message, 0, sizeof(message));
			int index = 0;
			FILE *fp = fopen("C:\\Users\\Bhavisya\\Documents\\thread_client.txt", "r+");
			char ch;
			ch = fgetc(fp);
			while (ch == EOF)
			{
				ch = fgetc(fp);
			}
			int flag;
			fscanf(fp, "%d", &flag);
			while (flag == 0)
			{
				fseek(fp, 0, 0);
				fscanf(fp, "%d", &flag);

			}
			ch = fgetc(fp);
			while (ch != '\n')
			{
				message[index++] = ch;
				ch = fgetc(fp);
			}
			message[index] = '\0';
			printf("Client: %s\n", message);
			fseek(fp, 0, SEEK_SET);
			fprintf(fp, "%d", 0);
			fclose(fp);
		}
	}
}