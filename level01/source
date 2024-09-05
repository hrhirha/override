#include <stdio.h>
#include <string.h>

char	a_user_name[0x100];

int	verify_user_name()
{
	/*
	   0x0804846c <+8>:	mov    DWORD PTR [esp],0x8048690
	   0x08048473 <+15>:	call   0x8048380 <puts@plt>
	 */
	puts("verifying username....\n");
	/*
	   0x08048478 <+20>:	mov    edx,0x804a040
	   0x0804847d <+25>:	mov    eax,0x80486a8
	   0x08048482 <+30>:	mov    ecx,0x7
	   0x08048487 <+35>:	mov    esi,edx
	   0x08048489 <+37>:	mov    edi,eax
	   0x0804848b <+39>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
	 */
	return (strncmp("dat_wil", a_user_name, 0x7));
}

int	verify_user_pass(char *s)
{
	/*
	   0x080484a8 <+5>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x080484ab <+8>:	mov    edx,eax
	   0x080484ad <+10>:	mov    eax,0x80486b0
	   0x080484b2 <+15>:	mov    ecx,0x5
	   0x080484b7 <+20>:	mov    esi,edx
	   0x080484b9 <+22>:	mov    edi,eax
	   0x080484bb <+24>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
	 */
	return (strncmp("admin", s, 0x5));
}

int	main()
{
	int		var2;			/* esp+0x5c */
	char	var1[0x10];		/* esp+0x1c */

	/*
	   0x080484db <+11>:	lea    ebx,[esp+0x1c]
	   0x080484df <+15>:	mov    eax,0x0
	   0x080484e4 <+20>:	mov    edx,0x10
	   0x080484e9 <+25>:	mov    edi,ebx
	   0x080484eb <+27>:	mov    ecx,edx
	   0x080484ed <+29>:	rep stos DWORD PTR es:[edi],eax
	 */
	memset(var1, 0x0, 0x10);
	/*
	   0x080484ef <+31>:	mov    DWORD PTR [esp+0x5c],0x0
	 */
	var2 = 0x0;
	/*
	   0x080484f7 <+39>:	mov    DWORD PTR [esp],0x80486b8
	   0x080484fe <+46>:	call   0x8048380 <puts@plt>
	 */
	puts("********* ADMIN LOGIN PROMPT *********");
	/*
	   0x08048503 <+51>:	mov    eax,0x80486df
	   0x08048508 <+56>:	mov    DWORD PTR [esp],eax
	   0x0804850b <+59>:	call   0x8048360 <printf@plt>
	 */
	printf("Enter Username: ");
	/*
	   0x08048510 <+64>:	mov    eax,ds:0x804a020
	   0x08048515 <+69>:	mov    DWORD PTR [esp+0x8],eax
	   0x08048519 <+73>:	mov    DWORD PTR [esp+0x4],0x100
	   0x08048521 <+81>:	mov    DWORD PTR [esp],0x804a040
	   0x08048528 <+88>:	call   0x8048370 <fgets@plt>
	 */
	fgets(a_user_name, 0x100, stdin);
	/*
	   0x0804852d <+93>:	call   0x8048464 <verify_user_name>
	   0x08048532 <+98>:	mov    DWORD PTR [esp+0x5c],eax
	 */
	var2 = verify_user_name();
	/*
	   0x08048536 <+102>:	cmp    DWORD PTR [esp+0x5c],0x0
	   0x0804853b <+107>:	je     0x8048550 <main+128>
	 */
	if (var2 != 0)
	{
		/*
		   0x0804853d <+109>:	mov    DWORD PTR [esp],0x80486f0
		   0x08048544 <+116>:	call   0x8048380 <puts@plt>
		 */
		puts("nope, incorrect username...\n");
		return (0x1);
	}
	/*
	   0x08048550 <+128>:	mov    DWORD PTR [esp],0x804870d
	   0x08048557 <+135>:	call   0x8048380 <puts@plt>
	 */
	puts("Enter Password: ");
	/*
	   0x0804855c <+140>:	mov    eax,ds:0x804a020
	   0x08048561 <+145>:	mov    DWORD PTR [esp+0x8],eax
	   0x08048565 <+149>:	mov    DWORD PTR [esp+0x4],0x64
	   0x0804856d <+157>:	lea    eax,[esp+0x1c]
	   0x08048571 <+161>:	mov    DWORD PTR [esp],eax
	   0x08048574 <+164>:	call   0x8048370 <fgets@plt>
	 */
	fgets(var1, 0x64, stdin);
	/*
	   0x08048579 <+169>:	lea    eax,[esp+0x1c]
	   0x0804857d <+173>:	mov    DWORD PTR [esp],eax
	   0x08048580 <+176>:	call   0x80484a3 <verify_user_pass>
	 */
	var2 = verify_user_pass(var1);
	/*
	   0x08048589 <+185>:	cmp    DWORD PTR [esp+0x5c],0x0
	   0x0804858e <+190>:	je     0x8048597 <main+199>
	   0x08048590 <+192>:	cmp    DWORD PTR [esp+0x5c],0x0
	   0x08048595 <+197>:	je     0x80485aa <main+218>
	 */
	if (var2 == 0 || var2 != 0)
	{
		/*
		   0x08048597 <+199>:	mov    DWORD PTR [esp],0x804871e
		   0x0804859e <+206>:	call   0x8048380 <puts@plt>
		 */
		puts("nope, incorrect password...\n");
		return (0x1);
	}
	return (0x0);
}
