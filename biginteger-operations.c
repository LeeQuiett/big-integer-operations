#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define arrayMaxSize 1024

char* Sub(const char* buf1, const char* buf2);
char* Add(const char* buf1, const char* buf2);
int check_digit(const char* buf);
void removeLeadingZeros(char* str);

char* Sub(const char* buf1, const char* buf2)
{
	char* res = 0;
	int	len1 = 0, len2 = 0, raise = 0, size = 0;
	int negative = 0;

	res = malloc(sizeof(char) * arrayMaxSize);
	if (!res) {
		perror("malloc failed!");
		exit(1);
	}
	memset(res, 0, arrayMaxSize);

	len1 = strlen(buf1) - 1;
	len2 = strlen(buf2) - 1;
	if (len1 < 0 || len2 < 0)
		return 0;

	// buf1의 자릿수가 buf2보다 작거나 같다면 사전순 비교
	if (len1 < len2 || (len1 == len2 && strcmp(buf1, buf2) < 0)) {
		negative = 1;
		const char* temp = buf1;
		buf1 = buf2;
		buf2 = temp;
		int tlen = len1;
		len1 = len2;
		len2 = tlen;
	}

	size = len1 + 1;
	res[size] = '\0';

	int i = size - 1;
	while (len1 >= 0 || len2 >= 0) {
		int tmp1 = 0, tmp2 = 0, num = 0;

		if (len1 >= 0)
			tmp1 = buf1[len1--] - '0';
		if (len2 >= 0)
			tmp2 = buf2[len2--] - '0';

		num = tmp1 - tmp2 - raise;
		if (num < 0) {
			num += 10;
			raise = 1;
		}
		else {
			raise = 0;
		}

		res[i--] = num + '0';
	}

	// 앞의 불필요한 0 제거
	removeLeadingZeros(res);

	if (negative) {
		size = strlen(res);
		memmove(res + 1, res, size + 1); //음수 부호 붙이기 위해 한칸 밈
		res[0] = '-';
	}

	return res;
}

char* Add(const char* buf1, const char* buf2)
{
	char* res;
	int	len1 = 0, len2 = 0, raise = 0;
	int size;

	res = (char*)malloc(sizeof(char) * arrayMaxSize * 2);
	if (!res)
	{
		puts("malloc failed!");
		exit(1);
	}
	memset(res, 0, arrayMaxSize);

	len1 = strlen(buf1) - 1;
	len2 = strlen(buf2) - 1;
	if (len1 >= len2)
		size = len1 + 1;
	else
		size = len2 + 1;

	res[size - 1] = '\0';

	int i = 0;
	while (size--)
	{
		int tmp1 = 0, tmp2 = 0, num = 0;

		if (len1 >= 0)
			tmp1 = buf1[len1--] - '0'; // ASCII TO INT
		if (len2 >= 0)
			tmp2 = buf2[len2--] - '0';

		num = tmp1 + tmp2 + raise;
		if (num >= 10)
			raise = 1;
		else
			raise = 0;

		num = num % 10;
		res[size] = (char)(num + '0');
	}

	// 앞의 불필요한 0 제거
	removeLeadingZeros(res);

	return res;
}

int check_digit(const char* buf)
{
	while (*buf)
	{
		if (!isdigit(*buf++))
			return 0;
	}
	return 1;
}

void removeLeadingZeros(char* str)
{
	int len = strlen(str);
	int i = 0;
	while (i < len - 1 && str[i] == '0') {
		i++;
	}
	if (i > 0) {
		memmove(str, str + i, len - i + 1);
	}
}

int	main(void)
{
	char* buf1 = 0;
	char* buf2 = 0;
	char* res = 0;
	char op = 0;

	buf1 = malloc(sizeof(char) * arrayMaxSize); // char * arrayMaxSize 자리 할당 , +1 은 널값
	buf2 = malloc(sizeof(char) * arrayMaxSize); // char * arrayMaxSize 자리 할당 , +1 은 널값
	if (!buf1 || !buf2)
	{
		puts("malloc failed!");
		exit(1);
	}

	memset(buf1, 0, arrayMaxSize);
	memset(buf2, 0, arrayMaxSize);

	fgets(buf1, arrayMaxSize, stdin);
	scanf("%c%*c", &op);
	fgets(buf2, arrayMaxSize, stdin);

	buf1[strlen(buf1) - 1] = '\0'; // 개행 제거, // 최대 입력 자릿수: arrayMaxSize
	buf2[strlen(buf2) - 1] = '\0'; // 개행 제거, // 최대 입력 자릿수: arrayMaxSize

	if (!check_digit(buf1) || !check_digit(buf2))
	{
		perror("invalid argument!");
		return 1;
	}

	if (op == '+')
	{
		res = Add(buf1, buf2);
	}
	else
	{
		res = Sub(buf1, buf2);
	}

	printf("Result: %s\n", res);

	free(buf1);
	free(buf2);
	free(res);

	return 0;
}
