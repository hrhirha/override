#include <stdio.h>
#include <string.h>

void	secret_backdoor()
{
	char	buf[0x80];		/* rbp-0x80 */

	/*
	   0x0000000000000894 <+8>:	mov    rax,QWORD PTR [rip+0x20171d]        # 0x201fb8
	   0x000000000000089b <+15>:	mov    rax,QWORD PTR [rax]
	   0x000000000000089e <+18>:	mov    rdx,rax
	   0x00000000000008a1 <+21>:	lea    rax,[rbp-0x80]
	   0x00000000000008a5 <+25>:	mov    esi,0x80
	   0x00000000000008aa <+30>:	mov    rdi,rax
	   0x00000000000008ad <+33>:	call   0x770 <fgets@plt>
	*/
	fgets(buf, 0x80, stdin);
	/*
	   0x00005555555548b2 <+38>:	lea    rax,[rbp-0x80]
	   0x00005555555548b6 <+42>:	mov    rdi,rax
	   0x00005555555548b9 <+45>:	call   0x555555554740 <system@plt>
	*/
	system(buf);
}

void	set_username(char *buf /*rbp-0x98*/)
{
	int		i;				/* rbp-0x4 */
	char	s[0x80];		/* rbp-0x90 */

	/*
	   0x00005555555549df <+18>:	lea    rax,[rbp-0x90]
	   0x00005555555549e6 <+25>:	mov    rsi,rax
	   0x00005555555549e9 <+28>:	mov    eax,0x0
	   0x00005555555549ee <+33>:	mov    edx,0x10
	   0x00005555555549f3 <+38>:	mov    rdi,rsi
	   0x00005555555549f6 <+41>:	mov    rcx,rdx
	   0x00005555555549f9 <+44>:	rep stos QWORD PTR es:[rdi],rax
	*/
	memset(s, 0x0, 0x10);
	/*
	   0x00005555555549fc <+47>:	lea    rdi,[rip+0x1e1]        # 0x555555554be4
	   0x0000555555554a03 <+54>:	call   0x555555554730 <puts@plt>
	*/
	puts(">: Enter your username");
	/*
	   0x0000555555554a08 <+59>:	lea    rax,[rip+0x1d0]        # 0x555555554bdf
	   0x0000555555554a0f <+66>:	mov    rdi,rax
	   0x0000555555554a12 <+69>:	mov    eax,0x0
	   0x0000555555554a17 <+74>:	call   0x555555554750 <printf@plt>
	*/
	printf(">>: ");
	/*
	   0x0000555555554a1c <+79>:	mov    rax,QWORD PTR [rip+0x201595]        # 0x555555755fb8
	   0x0000555555554a23 <+86>:	mov    rax,QWORD PTR [rax]
	   0x0000555555554a26 <+89>:	mov    rdx,rax
	   0x0000555555554a29 <+92>:	lea    rax,[rbp-0x90]
	   0x0000555555554a30 <+99>:	mov    esi,0x80
	   0x0000555555554a35 <+104>:	mov    rdi,rax
	   0x0000555555554a38 <+107>:	call   0x555555554770 <fgets@plt>
	*/
	fgets(s, 0x80, stdin);
	/*
	   0x0000555555554a3d <+112>:	mov    DWORD PTR [rbp-0x4],0x0
	*/
	i = 0x0;
	/*
	   0x0000555555554a6a <+157>:	cmp    DWORD PTR [rbp-0x4],0x28
	   0x0000555555554a6e <+161>:	jg     0x555555554a81 <set_username+180>
	   0x0000555555554a70 <+163>:	mov    eax,DWORD PTR [rbp-0x4]
	   0x0000555555554a73 <+166>:	cdqe
	   0x0000555555554a75 <+168>:	movzx  eax,BYTE PTR [rbp+rax*1-0x90]
	   0x0000555555554a7d <+176>:	test   al,al
	   0x0000555555554a7f <+178>:	jne    0x555555554a46 <set_username+121>
	*/
	while (i <= 0x28 && s[i] != 0x0)
	{
		/*
		   0x0000555555554a46 <+121>:	mov    eax,DWORD PTR [rbp-0x4]
		   0x0000555555554a49 <+124>:	cdqe
		   0x0000555555554a4b <+126>:	movzx  ecx,BYTE PTR [rbp+rax*1-0x90]
		   0x0000555555554a53 <+134>:	mov    rdx,QWORD PTR [rbp-0x98]
		   0x0000555555554a5a <+141>:	mov    eax,DWORD PTR [rbp-0x4]
		   0x0000555555554a5d <+144>:	cdqe
		   0x0000555555554a5f <+146>:	mov    BYTE PTR [rdx+rax*1+0x8c],cl
		   0x0000555555554a66 <+153>:	add    DWORD PTR [rbp-0x4],0x1
		*/
		buf[i + 0x8c] = s[i];
		++i;
	}
	/*
	   0x0000555555554a81 <+180>:	mov    rax,QWORD PTR [rbp-0x98]
	   0x0000555555554a88 <+187>:	lea    rdx,[rax+0x8c]
	   0x0000555555554a8f <+194>:	lea    rax,[rip+0x165]        # 0x555555554bfb
	   0x0000555555554a96 <+201>:	mov    rsi,rdx
	   0x0000555555554a99 <+204>:	mov    rdi,rax
	   0x0000555555554a9c <+207>:	mov    eax,0x0
	   0x0000555555554aa1 <+212>:	call   0x555555554750 <printf@plt>
	*/
	printf(">: Welcome, %s", buf + 0x8c);
}

void	set_msg(char *buf /*rbp-0x408*/)
{
	char	s[0x400];		/* rbp-0x400 */

	/*
	   0x0000555555554944 <+18>:	lea    rax,[rbp-0x400]
	   0x000055555555494b <+25>:	mov    rsi,rax
	   0x000055555555494e <+28>:	mov    eax,0x0
	   0x0000555555554953 <+33>:	mov    edx,0x80
	   0x0000555555554958 <+38>:	mov    rdi,rsi
	   0x000055555555495b <+41>:	mov    rcx,rdx
	   0x000055555555495e <+44>:	rep stos QWORD PTR es:[rdi],rax
	*/
	memset(s, 0x0, 0x80);
	/*
	   0x0000555555554961 <+47>:	lea    rdi,[rip+0x265]        # 0x555555554bcd
	   0x0000555555554968 <+54>:	call   0x555555554730 <puts@plt>
	*/
	puts(">: Msg @Unix-Dude");
	/*
	   0x000055555555496d <+59>:	lea    rax,[rip+0x26b]        # 0x555555554bdf
	   0x0000555555554974 <+66>:	mov    rdi,rax
	   0x0000555555554977 <+69>:	mov    eax,0x0
	   0x000055555555497c <+74>:	call   0x555555554750 <printf@plt>
	*/
	printf(">>: ");
	/*
	   0x0000555555554981 <+79>:	mov    rax,QWORD PTR [rip+0x201630]        # 0x555555755fb8
	   0x0000555555554988 <+86>:	mov    rax,QWORD PTR [rax]
	   0x000055555555498b <+89>:	mov    rdx,rax
	   0x000055555555498e <+92>:	lea    rax,[rbp-0x400]
	   0x0000555555554995 <+99>:	mov    esi,0x400
	   0x000055555555499a <+104>:	mov    rdi,rax
	   0x000055555555499d <+107>:	call   0x555555554770 <fgets@plt>
	*/
	fgets(s, 0x400, stdin);
	/*
	   0x00005555555549a2 <+112>:	mov    rax,QWORD PTR [rbp-0x408]
	   0x00005555555549a9 <+119>:	mov    eax,DWORD PTR [rax+0xb4]
	   0x00005555555549af <+125>:	movsxd rdx,eax
	   0x00005555555549b2 <+128>:	lea    rcx,[rbp-0x400]
	   0x00005555555549b9 <+135>:	mov    rax,QWORD PTR [rbp-0x408]
	   0x00005555555549c0 <+142>:	mov    rsi,rcx
	   0x00005555555549c3 <+145>:	mov    rdi,rax
	   0x00005555555549c6 <+148>:	call   0x555555554720 <strncpy@plt>
	*/
	strncpy(buf, s, (size_t)*((int*)(buf+0xb4)));
}

void	handle_msg()
{
	int		var;			/* rbp-0xc */
	char	buf[0xb4];		/* rbp-0xc0 */

	/*
	   0x00005555555548cb <+11>:	lea    rax,[rbp-0xc0]
	   0x00005555555548d2 <+18>:	add    rax,0x8c
	   0x00005555555548d8 <+24>:	mov    QWORD PTR [rax],0x0
	   0x00005555555548df <+31>:	mov    QWORD PTR [rax+0x8],0x0
	   0x00005555555548e7 <+39>:	mov    QWORD PTR [rax+0x10],0x0
	   0x00005555555548ef <+47>:	mov    QWORD PTR [rax+0x18],0x0
	   0x00005555555548f7 <+55>:	mov    QWORD PTR [rax+0x20],0x0
	*/
	memset(buf+0x8c, 0x0, 0x28);
	/*
	   0x00005555555548ff <+63>:	mov    DWORD PTR [rbp-0xc],0x8c
	*/
	var = 0x8c;
	/*
	   0x0000555555554906 <+70>:	lea    rax,[rbp-0xc0]
	   0x000055555555490d <+77>:	mov    rdi,rax
	   0x0000555555554910 <+80>:	call   0x5555555549cd <set_username>
	*/
	set_username(buf);
	/*
	   0x0000555555554915 <+85>:	lea    rax,[rbp-0xc0]
	   0x000055555555491c <+92>:	mov    rdi,rax
	   0x000055555555491f <+95>:	call   0x555555554932 <set_msg>
	*/
	set_msg(buf);
	/*
	   0x0000555555554924 <+100>:	lea    rdi,[rip+0x295]        # 0x555555554bc0
	   0x000055555555492b <+107>:	call   0x555555554730 <puts@plt>
	*/
	puts(">: Msg sent!");
}

int	main()
{
	/*
	   0x0000555555554aac <+4>:		lea    rdi,[rip+0x15d]        # 0x555555554c10
	   0x0000555555554ab3 <+11>:	call   0x555555554730 <puts@plt>
	*/
	puts("--------------------------------------------\n"
		"|   ~Welcome to l33t-m$n ~    v1337        |\n"
		"--------------------------------------------");
	/*
	   0x0000555555554ab8 <+16>:	call   0x5555555548c0 <handle_msg>
	*/
	handle_msg();
	return (0x0);
}
