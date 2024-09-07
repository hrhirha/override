#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>

int	auth(char *buf /* ebp+0x8 */, int serial /* ebp+0xc */)
{
	size_t			var2;	/* ebp-0x14 */
	unsigned int	var1;	/* ebp-0x10 */
	size_t			len;	/* ebp-0xc */

	/*
	   0x0804874e <+6>:		mov    DWORD PTR [esp+0x4],0x8048a63
	   0x08048756 <+14>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x08048759 <+17>:	mov    DWORD PTR [esp],eax
	   0x0804875c <+20>:	call   0x8048520 <strcspn@plt>
	   0x08048761 <+25>:	add    eax,DWORD PTR [ebp+0x8]
	   0x08048764 <+28>:	mov    BYTE PTR [eax],0x0
	 */
	buf[strcspn(buf, "\n")] = 0x0;
	/*
	   0x08048767 <+31>:	mov    DWORD PTR [esp+0x4],0x20
	   0x0804876f <+39>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x08048772 <+42>:	mov    DWORD PTR [esp],eax
	   0x08048775 <+45>:	call   0x80485d0 <strnlen@plt>
	   0x0804877a <+50>:	mov    DWORD PTR [ebp-0xc],eax
	 */
	len = strnlen(buf, 0x20);
	/*
	   0x08048786 <+62>:	cmp    DWORD PTR [ebp-0xc],0x5
	   0x0804878a <+66>:	jg     0x8048796 <auth+78>
	 */
	if (len <= 0x5)
	{
		/*
		   0x0804878c <+68>:	mov    eax,0x1
		   0x08048791 <+73>:	jmp    0x8048877 <auth+303>
		 */
		return (1);
	}
	/*
	   0x08048796 <+78>:	mov    DWORD PTR [esp+0xc],0x0
	   0x0804879e <+86>:	mov    DWORD PTR [esp+0x8],0x1
	   0x080487a6 <+94>:	mov    DWORD PTR [esp+0x4],0x0
	   0x080487ae <+102>:	mov    DWORD PTR [esp],0x0
	   0x080487b5 <+109>:	call   0x80485f0 <ptrace@plt>
	   0x080487ba <+114>:	cmp    eax,0xffffffff
	   0x080487bd <+117>:	jne    0x80487ed <auth+165>
	 */
	if (ptrace(PTRACE_TRACEME, 0x0, 0x1, 0x0) == -1)
	{
		/*
		   0x080487bf <+119>:	mov    DWORD PTR [esp],0x8048a68
		   0x080487c6 <+126>:	call   0x8048590 <puts@plt>
		   0x080487cb <+131>:	mov    DWORD PTR [esp],0x8048a8c
		   0x080487d2 <+138>:	call   0x8048590 <puts@plt>
		   0x080487d7 <+143>:	mov    DWORD PTR [esp],0x8048ab0
		   0x080487de <+150>:	call   0x8048590 <puts@plt>
		   0x080487e3 <+155>:	mov    eax,0x1
		   0x080487e8 <+160>:	jmp    0x8048877 <auth+303>
		 */
		puts("\033[32m.---------------------------");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m.---------------------------");
		return (0x1);
	}
	/*
	   0x080487ed <+165>:	mov    eax,DWORD PTR [ebp+0x8]
	   0x080487f0 <+168>:	add    eax,0x3
	   0x080487f3 <+171>:	movzx  eax,BYTE PTR [eax]
	   0x080487f6 <+174>:	movsx  eax,al
	   0x080487f9 <+177>:	xor    eax,0x1337
	   0x080487fe <+182>:	add    eax,0x5eeded
	   0x08048803 <+187>:	mov    DWORD PTR [ebp-0x10],eax
	   0x08048806 <+190>:	mov    DWORD PTR [ebp-0x14],0x0
	   0x0804880d <+197>:	jmp    0x804885b <auth+275>
	 */
	var1 = (buf[0x3] ^ 0x1337) + 0x5eeded;
	var2 = 0x0;
	/*
	   0x0804885b <+275>:	mov    eax,DWORD PTR [ebp-0x14]
	   0x0804885e <+278>:	cmp    eax,DWORD PTR [ebp-0xc]
	   0x08048861 <+281>:	jl     0x804880f <auth+199>
	 */
	while (var2 < len)
	{
		/*
		   0x0804880f <+199>:	mov    eax,DWORD PTR [ebp-0x14]
		   0x08048812 <+202>:	add    eax,DWORD PTR [ebp+0x8]
		   0x08048815 <+205>:	movzx  eax,BYTE PTR [eax]
		   0x08048818 <+208>:	cmp    al,0x1f
		   0x0804881a <+210>:	jg     0x8048823 <auth+219>
		 */
		if (buf[var2] <= 0x1f)
		{
			/*
			   0x0804881c <+212>:	mov    eax,0x1
			   0x08048821 <+217>:	jmp    0x8048877 <auth+303>
			 */
			return (0x1);
		}
		/*
		   0x08048823 <+219>:	mov    eax,DWORD PTR [ebp-0x14]
		   0x08048826 <+222>:	add    eax,DWORD PTR [ebp+0x8]
		   0x08048829 <+225>:	movzx  eax,BYTE PTR [eax]
		   0x0804882c <+228>:	movsx  eax,al
		   0x0804882f <+231>:	mov    ecx,eax
		   0x08048831 <+233>:	xor    ecx,DWORD PTR [ebp-0x10]
		   0x08048834 <+236>:	mov    edx,0x88233b2b
		   0x08048839 <+241>:	mov    eax,ecx
		   0x0804883b <+243>:	mul    edx
		   0x0804883d <+245>:	mov    eax,ecx
		   0x0804883f <+247>:	sub    eax,edx
		   0x08048841 <+249>:	shr    eax,1
		   0x08048843 <+251>:	add    eax,edx
		   0x08048845 <+253>:	shr    eax,0xa
		   0x08048848 <+256>:	imul   eax,eax,0x539
		   0x0804884e <+262>:	mov    edx,ecx
		   0x08048850 <+264>:	sub    edx,eax
		   0x08048852 <+266>:	mov    eax,edx
		   0x08048854 <+268>:	add    DWORD PTR [ebp-0x10],eax
		 */
		var1 += (buf[var2] ^ var1) - ((((((buf[var2] ^ var1) - ((buf[var2] ^ var1) * 0x88233b2b)) >> 0x1) + ((buf[var2] ^ var1) * 0x88233b2b)) >> 0xa) * 0x539);
		/*
		   0x08048857 <+271>:	add    DWORD PTR [ebp-0x14],0x1
		 */
		++var2;
	}
	/*
	   0x08048863 <+283>:	mov    eax,DWORD PTR [ebp+0xc]
	   0x08048866 <+286>:	cmp    eax,DWORD PTR [ebp-0x10]
	   0x08048869 <+289>:	je     0x8048872 <auth+298>
	 */
	if (serial == var1)
	{
		/*
		   0x08048872 <+298>:	mov    eax,0x0
		 */
		return (0x0);
	}
	return (0x1);
}

int	main(int ac, char **av)
{
	char			buf[0x20];	/* esp+0x2c */
	unsigned int	serial;		/* esp+0x28 */

	printf("PTRACE %d\n", PTRACE_TRACEME);
	/*
	   0x0804889e <+37>:	mov    DWORD PTR [esp],0x8048ad4
	   0x080488a5 <+44>:	call   0x8048590 <puts@plt>
	   0x080488aa <+49>:	mov    DWORD PTR [esp],0x8048af8
	   0x080488b1 <+56>:	call   0x8048590 <puts@plt>
	   0x080488b6 <+61>:	mov    DWORD PTR [esp],0x8048ad4
	   0x080488bd <+68>:	call   0x8048590 <puts@plt>
	   0x080488c2 <+73>:	mov    eax,0x8048b08
	   0x080488c7 <+78>:	mov    DWORD PTR [esp],eax
	   0x080488ca <+81>:	call   0x8048510 <printf@plt>
	 */
	puts("***********************************");
	puts("*		level06		  *");
	puts("***********************************");
	printf("-> Enter Login:");
	/*
	   0x080488cf <+86>:	mov    eax,ds:0x804a060
	   0x080488d4 <+91>:	mov    DWORD PTR [esp+0x8],eax
	   0x080488d8 <+95>:	mov    DWORD PTR [esp+0x4],0x20
	   0x080488e0 <+103>:	lea    eax,[esp+0x2c]
	   0x080488e4 <+107>:	mov    DWORD PTR [esp],eax
	   0x080488e7 <+110>:	call   0x8048550 <fgets@plt>
	 */
	fgets(buf, 0x20, stdin);
	/*
	   0x080488ec <+115>:	mov    DWORD PTR [esp],0x8048ad4
	   0x080488f3 <+122>:	call   0x8048590 <puts@plt>
	   0x080488f8 <+127>:	mov    DWORD PTR [esp],0x8048b1c
	   0x080488ff <+134>:	call   0x8048590 <puts@plt>
	   0x08048904 <+139>:	mov    DWORD PTR [esp],0x8048ad4
	   0x0804890b <+146>:	call   0x8048590 <puts@plt>
	   0x08048910 <+151>:	mov    eax,0x8048b40
	   0x08048915 <+156>:	mov    DWORD PTR [esp],eax
	   0x08048918 <+159>:	call   0x8048510 <printf@plt>
	 */
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	/*
	   0x0804891d <+164>:	mov    eax,0x8048a60
	   0x08048922 <+169>:	lea    edx,[esp+0x28]
	   0x08048926 <+173>:	mov    DWORD PTR [esp+0x4],edx
	   0x0804892a <+177>:	mov    DWORD PTR [esp],eax
	   0x0804892d <+180>:	call   0x80485e0 <__isoc99_scanf@plt>
	 */
	scanf("%u", &serial);
	/*
	   0x08048932 <+185>:	mov    eax,DWORD PTR [esp+0x28]
	   0x08048936 <+189>:	mov    DWORD PTR [esp+0x4],eax
	   0x0804893a <+193>:	lea    eax,[esp+0x2c]
	   0x0804893e <+197>:	mov    DWORD PTR [esp],eax
	   0x08048941 <+200>:	call   0x8048748 <auth>
	   0x08048946 <+205>:	test   eax,eax
	   0x08048948 <+207>:	jne    0x8048969 <main+240>
	 */
	if (auth(buf, serial) != 0)
	{
		/*
		   0x08048969 <+240>:	mov    eax,0x1
		 */
		return (1);
	}
	/*
	   0x0804894a <+209>:	mov    DWORD PTR [esp],0x8048b52
	   0x08048951 <+216>:	call   0x8048590 <puts@plt>
	 */
	puts("Authenticated!");
	/*
	   0x08048956 <+221>:	mov    DWORD PTR [esp],0x8048b61
	   0x0804895d <+228>:	call   0x80485a0 <system@plt>
	   0x08048962 <+233>:	mov    eax,0x0
	 */
	system("/bin/sh");
	return (0);
}
