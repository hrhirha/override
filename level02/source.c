#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	FILE	*f;			/* rbp-0x8 */
	size_t	len;		/* rbp-0xc */
	char	user[0x64];	/* rbp-0x70 */
	char	buff[0x29];	/* rbp-0xa0 */
	char	pass[0x64];	/* rbp-0x110 */

	memset(user, 0x0, 0x64);
	memset(buff, 0x0, 0x29);
	memset(pass, 0x0, 0x64);
	f = 0x0;
	len = 0x0;
	f = fopen("/home/users/level02/.pass", "r");
	if (f == 0x0)
	{
		fwrite("RROR: failed to open password file\n", 0x1, 0x24, stderr);
		exit(0x1);
	}
	len = fread(buff, 0x1, 0x64, f);
	buff[strcspn(buff, "\n")] = 0x0;
	if (len != 0x29)
	{
		fwrite("RROR: failed to open password file\n", 0x1, 0x24, stderr);
		fwrite("RROR: failed to open password file\n", 0x1, 0x24, stderr);
		exit(0x1);
	}
	fclose(f);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/39*\\");
	puts("| You must login to access this system. |");
	puts("\\38*/");
	printf("--[ Username: ");
	fgets(user, 0x64, stdin);
	user[strcspn(user, "\n")] = 0x0;
	printf("--[ Password: ");
	fgets(pass, 0x64, stdin);
	pass[strcspn(pass, "\n")] = 0x0;
	puts("41*");
	if (strncmp(buff, pass, 0x29) != 0)
	{
		printf(user);
		puts(" does not have access!");
		exit(1);
	}
	printf("Greetings, %s!\n", user);
	system("/bin/sh");
}
