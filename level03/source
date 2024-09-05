#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void	decrypt(int num)
{
	char			var1[17] ;	/* ebp-0x1d */
	int				len;		/* ebp-0x24 */
	int				var3;		/* ebp-0x28 */

	/*
	   0x08048673 <+19>:	mov    DWORD PTR [ebp-0x1d],0x757c7d51
	   0x0804867a <+26>:	mov    DWORD PTR [ebp-0x19],0x67667360
	   0x08048681 <+33>:	mov    DWORD PTR [ebp-0x15],0x7b66737e
	   0x08048688 <+40>:	mov    DWORD PTR [ebp-0x11],0x33617c7d
	   0x0804868f <+47>:	mov    BYTE PTR [ebp-0xd],0x0
	*/
	strcpy(var1, "Q}|u`sfg~sf{}|a3");
	/*
	   0x0804869c <+60>:	lea    eax,[ebp-0x1d]
	   0x0804869f <+63>:	mov    DWORD PTR [ebp-0x2c],0xffffffff
	   0x080486a6 <+70>:	mov    edx,eax
	   0x080486a8 <+72>:	mov    eax,0x0
	   0x080486ad <+77>:	mov    ecx,DWORD PTR [ebp-0x2c]
	   0x080486b0 <+80>:	mov    edi,edx
	   0x080486b2 <+82>:	repnz scas al,BYTE PTR es:[edi]
	   0x080486b4 <+84>:	mov    eax,ecx
	   0x080486b6 <+86>:	not    eax
	   0x080486b8 <+88>:	sub    eax,0x1
	   0x080486bb <+91>:	mov    DWORD PTR [ebp-0x24],eax
	   0x080486be <+94>:	mov    DWORD PTR [ebp-0x28],0x0
	*/
	len = strlen(var1);
	var3 = 0;
	/*
	   0x080486e5 <+133>:	mov    eax,DWORD PTR [ebp-0x28]
	   0x080486e8 <+136>:	cmp    eax,DWORD PTR [ebp-0x24]
	   0x080486eb <+139>:	jb     0x80486c7 <decrypt+103>
	*/
	while (var3 < len)
	{
		/*
		   0x080486c7 <+103>:	lea    eax,[ebp-0x1d]
		   0x080486ca <+106>:	add    eax,DWORD PTR [ebp-0x28]
		   0x080486cd <+109>:	movzx  eax,BYTE PTR [eax]
		   0x080486d0 <+112>:	mov    edx,eax
		   0x080486d2 <+114>:	mov    eax,DWORD PTR [ebp+0x8]
		   0x080486d5 <+117>:	xor    eax,edx
		   0x080486d7 <+119>:	mov    edx,eax
		   0x080486d9 <+121>:	lea    eax,[ebp-0x1d]
		   0x080486dc <+124>:	add    eax,DWORD PTR [ebp-0x28]
		   0x080486df <+127>:	mov    BYTE PTR [eax],dl
		   0x080486e1 <+129>:	add    DWORD PTR [ebp-0x28],0x1
		*/
		var1[var3] = var1[var3] ^ num;
		++var3;
	}
	/*
	   0x080486ed <+141>:	lea    eax,[ebp-0x1d]
	   0x080486f0 <+144>:	mov    edx,eax
	   0x080486f2 <+146>:	mov    eax,0x80489c3
	   0x080486f7 <+151>:	mov    ecx,0x11
	   0x080486fc <+156>:	mov    esi,edx
	   0x080486fe <+158>:	mov    edi,eax
	   0x08048700 <+160>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
	   0x08048702 <+162>:	seta   dl
	   0x08048705 <+165>:	setb   al
	   0x08048708 <+168>:	mov    ecx,edx
	   0x0804870a <+170>:	sub    cl,al
	   0x0804870c <+172>:	mov    eax,ecx
	   0x0804870e <+174>:	movsx  eax,al
	   0x08048711 <+177>:	test   eax,eax
	   0x08048713 <+179>:	jne    0x8048723 <decrypt+195>
	*/
	if (strncmp(var1, "Congratulations!", 0x11) == 0)
	{
		/*
		   0x08048715 <+181>:	mov    DWORD PTR [esp],0x80489d4
		   0x0804871c <+188>:	call   0x80484e0 <system@plt>
		   0x08048721 <+193>:	jmp    0x804872f <decrypt+207>
		*/
		system("/bin/sh");
		return ;
	}
	/*
	   0x08048723 <+195>:	mov    DWORD PTR [esp],0x80489dc
	   0x0804872a <+202>:	call   0x80484d0 <puts@plt>
	*/
	puts("\nInvalid Password");
}

void	test(int p, unsigned int var)
{
	unsigned int dif;

	/*
	   0x0804874d <+6>:		mov    eax,DWORD PTR [ebp+0x8]
	   0x08048750 <+9>:		mov    edx,DWORD PTR [ebp+0xc]
	   0x08048753 <+12>:	mov    ecx,edx
	   0x08048755 <+14>:	sub    ecx,eax
	   0x08048757 <+16>:	mov    eax,ecx
	   0x08048759 <+18>:	mov    DWORD PTR [ebp-0xc],eax
	*/
	dif = var - p;	/* ebp+0xc - ebp+0x8 */
	/*
	   0x0804875c <+21>:	cmp    DWORD PTR [ebp-0xc],0x15
	   0x08048760 <+25>:	ja     0x804884a <test+259>
	*/
	if (dif > 0x15)
	{
		/*
		   0x0804884a <+259>:	call   0x8048520 <rand@plt>
		   0x0804884f <+264>:	mov    DWORD PTR [esp],eax
		   0x08048852 <+267>:	call   0x8048660 <decrypt>
		*/
		decrypt(rand());
		return ;
	}
	/*
	   0x08048766 <+31>:	mov    eax,DWORD PTR [ebp-0xc]
	   0x08048769 <+34>:	shl    eax,0x2
	   0x0804876c <+37>:	add    eax,0x80489f0
	   0x08048771 <+42>:	mov    eax,DWORD PTR [eax]
	   0x08048773 <+44>:	jmp    eax
	   0x08048775 <+46>:	mov    eax,DWORD PTR [ebp-0xc]
	   0x08048778 <+49>:	mov    DWORD PTR [esp],eax
	   0x0804877b <+52>:	call   0x8048660 <decrypt>
	*/
	// ((void*)((dif << 0x2) + 0x80489f0))();
	decrypt(dif);
}

int main()
{
	int p;	/* esp+0x1c */

	/*
	   0x0804886c <+18>:	mov    DWORD PTR [esp],0x0
	   0x08048873 <+25>:	call   0x80484b0 <time@plt>
	   0x08048878 <+30>:	mov    DWORD PTR [esp],eax
	   0x0804887b <+33>:	call   0x8048500 <srand@plt>
	*/
	srand(time(0x0));
	/*
	   0x0804887b <+33>:	call   0x8048500 <srand@plt>
	   0x08048880 <+38>:	mov    DWORD PTR [esp],0x8048a48
	   0x08048887 <+45>:	call   0x80484d0 <puts@plt>
	   0x0804888c <+50>:	mov    DWORD PTR [esp],0x8048a6c
	   0x08048893 <+57>:	call   0x80484d0 <puts@plt>
	   0x08048898 <+62>:	mov    DWORD PTR [esp],0x8048a48
	   0x0804889f <+69>:	call   0x80484d0 <puts@plt>
	   0x080488a4 <+74>:	mov    eax,0x8048a7b
	   0x080488a9 <+79>:	mov    DWORD PTR [esp],eax
	   0x080488ac <+82>:	call   0x8048480 <printf@plt>
	*/
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	/*
	   0x080488b1 <+87>:	mov    eax,0x8048a85
	   0x080488b6 <+92>:	lea    edx,[esp+0x1c]
	   0x080488ba <+96>:	mov    DWORD PTR [esp+0x4],edx
	   0x080488be <+100>:	mov    DWORD PTR [esp],eax
	   0x080488c1 <+103>:	call   0x8048530 <__isoc99_scanf@plt>
	*/
	scanf("%d", &p);
	/*
	   0x080488c6 <+108>:	mov    eax,DWORD PTR [esp+0x1c]
	   0x080488ca <+112>:	mov    DWORD PTR [esp+0x4],0x1337d00d
	   0x080488d2 <+120>:	mov    DWORD PTR [esp],eax
	   0x080488d5 <+123>:	call   0x8048747 <test>
	*/
	test(p, 0x1337d00d);
	return (0);
}
