#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	log_wrapper(FILE *log_f /*rbp-0x118*/, char *s /*rbp-0x120*/, char *av1 /*rbp-0x128*/)
{
	char	msg[0xfe];		/* rbp-0x110 */

	/*
	   0x00000000004008f3 <+47>:	mov    rdx,QWORD PTR [rbp-0x120]
	   0x00000000004008fa <+54>:	lea    rax,[rbp-0x110]
	   0x0000000000400901 <+61>:	mov    rsi,rdx
	   0x0000000000400904 <+64>:	mov    rdi,rax
	   0x0000000000400907 <+67>:	call   0x4006f0 <strcpy@plt>
	*/
	strcpy(msg, s);
	/*
	   0x000000000040090c <+72>:	mov    rsi,QWORD PTR [rbp-0x128]
	   0x0000000000400913 <+79>:	lea    rax,[rbp-0x110]
	   0x000000000040091a <+86>:	mov    QWORD PTR [rbp-0x130],0xffffffffffffffff
	   0x0000000000400925 <+97>:	mov    rdx,rax
	   0x0000000000400928 <+100>:	mov    eax,0x0
	   0x000000000040092d <+105>:	mov    rcx,QWORD PTR [rbp-0x130]
	   0x0000000000400934 <+112>:	mov    rdi,rdx
	   0x0000000000400937 <+115>:	repnz scas al,BYTE PTR es:[rdi]
	   0x0000000000400939 <+117>:	mov    rax,rcx
	   0x000000000040093c <+120>:	not    rax
	   0x000000000040093f <+123>:	lea    rdx,[rax-0x1]
	   0x0000000000400943 <+127>:	mov    eax,0xfe
	   0x0000000000400948 <+132>:	mov    r8,rax
	   0x000000000040094b <+135>:	sub    r8,rdx
	
		Calculates 0xfe - strlen(msg)
	*/
	/*
	   0x000000000040094e <+138>:	lea    rax,[rbp-0x110]
	   0x0000000000400955 <+145>:	mov    QWORD PTR [rbp-0x130],0xffffffffffffffff
	   0x0000000000400960 <+156>:	mov    rdx,rax
	   0x0000000000400963 <+159>:	mov    eax,0x0
	   0x0000000000400968 <+164>:	mov    rcx,QWORD PTR [rbp-0x130]
	   0x000000000040096f <+171>:	mov    rdi,rdx
	   0x0000000000400972 <+174>:	repnz scas al,BYTE PTR es:[rdi]
	   0x0000000000400974 <+176>:	mov    rax,rcx
	   0x0000000000400977 <+179>:	not    rax
	   0x000000000040097a <+182>:	lea    rdx,[rax-0x1]

		Calculates strlen(msg)
	*/
	/*
	   0x000000000040097e <+186>:	lea    rax,[rbp-0x110]
	   0x0000000000400985 <+193>:	add    rax,rdx
	   0x0000000000400988 <+196>:	mov    rdx,rsi
	   0x000000000040098b <+199>:	mov    rsi,r8
	   0x000000000040098e <+202>:	mov    rdi,rax
	   0x0000000000400991 <+205>:	mov    eax,0x0
	*/
	snprintf(msg+strlen(msg), 0xfe - strlen(msg), av1);
	/*
	   0x000000000040099b <+215>:	lea    rax,[rbp-0x110]
	   0x00000000004009a2 <+222>:	mov    esi,0x400d4c
	   0x00000000004009a7 <+227>:	mov    rdi,rax
	   0x00000000004009aa <+230>:	call   0x400780 <strcspn@plt>
	   0x00000000004009af <+235>:	mov    BYTE PTR [rbp+rax*1-0x110],0x0
	*/
	msg[strcspn(msg, "\n")] = 0x0;
	/*
	   0x00000000004009b7 <+243>:	mov    ecx,0x400d4e
	   0x00000000004009bc <+248>:	lea    rdx,[rbp-0x110]
	   0x00000000004009c3 <+255>:	mov    rax,QWORD PTR [rbp-0x118]
	   0x00000000004009ca <+262>:	mov    rsi,rcx
	   0x00000000004009cd <+265>:	mov    rdi,rax
	   0x00000000004009d0 <+268>:	mov    eax,0x0
	   0x00000000004009d5 <+273>:	call   0x4007a0 <fprintf@plt>
	*/
	fprintf(log_f, "LOG: %s\n", msg);
}

int	main(int ac /*rbp-0x94*/, char **av /*rbp-0xa0*/)
{
	char	path[0x63];			/* rbp-0x70 */
	int		c;					/* rbp-0x71 */
	int		fd;					/* rbp-0x78 */
	FILE	*f;					/* rbp-0x80 */
	FILE	*log_f;				/* rbp-0x88 */

	/*
	   0x0000000000400a22 <+50>:	cmp    DWORD PTR [rbp-0x94],0x2
	   0x0000000000400a29 <+57>:	je     0x400a4a <main+90>
	 */
	if (ac != 0x2)
	{
		/*
		   0x0000000000400a2b <+59>:	mov    rax,QWORD PTR [rbp-0xa0]
		   0x0000000000400a32 <+66>:	mov    rdx,QWORD PTR [rax]
		   0x0000000000400a35 <+69>:	mov    eax,0x400d57
		   0x0000000000400a3a <+74>:	mov    rsi,rdx
		   0x0000000000400a3d <+77>:	mov    rdi,rax
		   0x0000000000400a40 <+80>:	mov    eax,0x0
		   0x0000000000400a45 <+85>:	call   0x400730 <printf@plt>
		 */
		printf("Usage: %s filename\n", *av);
	}
	/*
	   0x0000000000400a4a <+90>:	mov    edx,0x400d6b
	   0x0000000000400a4f <+95>:	mov    eax,0x400d6d
	   0x0000000000400a54 <+100>:	mov    rsi,rdx
	   0x0000000000400a57 <+103>:	mov    rdi,rax
	   0x0000000000400a5a <+106>:	call   0x4007c0 <fopen@plt>
	   0x0000000000400a5f <+111>:	mov    QWORD PTR [rbp-0x88],rax
	 */
	log_f = fopen("./backups/.log", "w");
	/*
	   0x0000000000400a66 <+118>:	cmp    QWORD PTR [rbp-0x88],0x0
	   0x0000000000400a6e <+126>:	jne    0x400a91 <main+161>
	 */
	if (log_f == NULL)
	{
		/*
		   0x0000000000400a70 <+128>:	mov    eax,0x400d7c
		   0x0000000000400a75 <+133>:	mov    esi,0x400d6d
		   0x0000000000400a7a <+138>:	mov    rdi,rax
		   0x0000000000400a7d <+141>:	mov    eax,0x0
		   0x0000000000400a82 <+146>:	call   0x400730 <printf@plt>
		   0x0000000000400a87 <+151>:	mov    edi,0x1
		   0x0000000000400a8c <+156>:	call   0x4007d0 <exit@plt>
		 */
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(0x1);
	}
	/*
	   0x0000000000400a91 <+161>:	mov    rax,QWORD PTR [rbp-0xa0]
	   0x0000000000400a98 <+168>:	add    rax,0x8
	   0x0000000000400a9c <+172>:	mov    rdx,QWORD PTR [rax]
	   0x0000000000400a9f <+175>:	mov    rax,QWORD PTR [rbp-0x88]
	   0x0000000000400aa6 <+182>:	mov    esi,0x400d96
	   0x0000000000400aab <+187>:	mov    rdi,rax
	   0x0000000000400aae <+190>:	call   0x4008c4 <log_wrapper>
	 */
	log_wrapper(log_f, "Starting back up: ", av[1]);
	/*
	   0x0000000000400ab3 <+195>:	mov    edx,0x400da9
	   0x0000000000400ab8 <+200>:	mov    rax,QWORD PTR [rbp-0xa0]
	   0x0000000000400abf <+207>:	add    rax,0x8
	   0x0000000000400ac3 <+211>:	mov    rax,QWORD PTR [rax]
	   0x0000000000400ac6 <+214>:	mov    rsi,rdx
	   0x0000000000400ac9 <+217>:	mov    rdi,rax
	   0x0000000000400acc <+220>:	call   0x4007c0 <fopen@plt>
	 */
	f = fopen(av[1], "r");
	/*
	   0x0000000000400ad5 <+229>:	cmp    QWORD PTR [rbp-0x80],0x0
	   0x0000000000400ada <+234>:	jne    0x400b09 <main+281>
	 */
	if (f == 0x0)
	{
		/*
		   0x0000000000400adc <+236>:	mov    rax,QWORD PTR [rbp-0xa0]
		   0x0000000000400ae3 <+243>:	add    rax,0x8
		   0x0000000000400ae7 <+247>:	mov    rdx,QWORD PTR [rax]
		   0x0000000000400aea <+250>:	mov    eax,0x400d7c
		   0x0000000000400aef <+255>:	mov    rsi,rdx
		   0x0000000000400af2 <+258>:	mov    rdi,rax
		   0x0000000000400af5 <+261>:	mov    eax,0x0
		   0x0000000000400afa <+266>:	call   0x400730 <printf@plt>
		   0x0000000000400aff <+271>:	mov    edi,0x1
		   0x0000000000400b04 <+276>:	call   0x4007d0 <exit@plt>
		 */
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(0x1);
	}
	/*
	   0x0000000000400b09 <+281>:	mov    edx,0x400dab
	   0x0000000000400b0e <+286>:	lea    rax,[rbp-0x70]
	   0x0000000000400b12 <+290>:	mov    rcx,QWORD PTR [rdx]
	   0x0000000000400b15 <+293>:	mov    QWORD PTR [rax],rcx
	   0x0000000000400b18 <+296>:	movzx  ecx,WORD PTR [rdx+0x8]
	   0x0000000000400b1c <+300>:	mov    WORD PTR [rax+0x8],cx
	   0x0000000000400b20 <+304>:	movzx  edx,BYTE PTR [rdx+0xa]
	   0x0000000000400b24 <+308>:	mov    BYTE PTR [rax+0xa],dl
	   0x0000000000400b27 <+311>:	lea    rax,[rbp-0x70]
	 */
	strcpy(path, "./backups/");
	/*
	   0x0000000000400b2b <+315>:	mov    QWORD PTR [rbp-0xa8],0xffffffffffffffff
	   0x0000000000400b36 <+326>:	mov    rdx,rax
	   0x0000000000400b39 <+329>:	mov    eax,0x0
	   0x0000000000400b3e <+334>:	mov    rcx,QWORD PTR [rbp-0xa8]
	   0x0000000000400b45 <+341>:	mov    rdi,rdx
	   0x0000000000400b48 <+344>:	repnz scas al,BYTE PTR es:[rdi]
	   0x0000000000400b4a <+346>:	mov    rax,rcx
	   0x0000000000400b4d <+349>:	not    rax
	   0x0000000000400b50 <+352>:	lea    rdx,[rax-0x1]
	   0x0000000000400b54 <+356>:	mov    eax,0x63
	   0x0000000000400b59 <+361>:	mov    rcx,rax
	   0x0000000000400b5c <+364>:	sub    rcx,rdx
	   0x0000000000400b5f <+367>:	mov    rdx,rcx
	   0x0000000000400b62 <+370>:	mov    rax,QWORD PTR [rbp-0xa0]
	   0x0000000000400b69 <+377>:	add    rax,0x8
	   0x0000000000400b6d <+381>:	mov    rax,QWORD PTR [rax]
	   0x0000000000400b70 <+384>:	mov    rcx,rax
	   0x0000000000400b73 <+387>:	lea    rax,[rbp-0x70]
	   0x0000000000400b77 <+391>:	mov    rsi,rcx
	   0x0000000000400b7a <+394>:	mov    rdi,rax
	   0x0000000000400b7d <+397>:	call   0x400750 <strncat@plt>
	 */
	strncat(path, av[1], 0x63 - strlen("./backups/"));
	/*
	   0x0000000000400b82 <+402>:	lea    rax,[rbp-0x70]
	   0x0000000000400b86 <+406>:	mov    edx,0x1b0
	   0x0000000000400b8b <+411>:	mov    esi,0xc1
	   0x0000000000400b90 <+416>:	mov    rdi,rax
	   0x0000000000400b93 <+419>:	mov    eax,0x0
	   0x0000000000400b98 <+424>:	call   0x4007b0 <open@plt>
	   0x0000000000400b9d <+429>:	mov    DWORD PTR [rbp-0x78],eax
	 */
	fd = open(path, O_CREAT|O_WRONLY|O_EXCL, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
	/*
	   0x0000000000400ba0 <+432>:	cmp    DWORD PTR [rbp-0x78],0x0
	   0x0000000000400ba4 <+436>:	jns    0x400bed <main+509>
	 */
	if (fd == 0x0)
	{
		/*
		   0x0000000000400ba6 <+438>:	mov    rax,QWORD PTR [rbp-0xa0]
		   0x0000000000400bad <+445>:	add    rax,0x8
		   0x0000000000400bb1 <+449>:	mov    rdx,QWORD PTR [rax]
		   0x0000000000400bb4 <+452>:	mov    eax,0x400db6
		   0x0000000000400bb9 <+457>:	mov    esi,0x400dab
		   0x0000000000400bbe <+462>:	mov    rdi,rax
		   0x0000000000400bc1 <+465>:	mov    eax,0x0
		   0x0000000000400bc6 <+470>:	call   0x400730 <printf@plt>
		   0x0000000000400bcb <+475>:	mov    edi,0x1
		   0x0000000000400bd0 <+480>:	call   0x4007d0 <exit@plt>
		 */
		printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
		exit(0x1);
	}
	puts(path);
	while (1)
	{
		/*
		   0x0000000000400bed <+509>:	nop
		   0x0000000000400bee <+510>:	mov    rax,QWORD PTR [rbp-0x80]
		   0x0000000000400bf2 <+514>:	mov    rdi,rax
		   0x0000000000400bf5 <+517>:	call   0x400760 <fgetc@plt>
		   0x0000000000400bfa <+522>:	mov    BYTE PTR [rbp-0x71],al
		   0x0000000000400bfd <+525>:	movzx  eax,BYTE PTR [rbp-0x71]
		   0x0000000000400c01 <+529>:	cmp    al,0xff
		   0x0000000000400c03 <+531>:	jne    0x400bd5 <main+485>
		 */
		c = fgetc(f);
		if (c == -1)
			break ;
		/*
		   0x0000000000400bd5 <+485>:	lea    rcx,[rbp-0x71]
		   0x0000000000400bd9 <+489>:	mov    eax,DWORD PTR [rbp-0x78]
		   0x0000000000400bdc <+492>:	mov    edx,0x1
		   0x0000000000400be1 <+497>:	mov    rsi,rcx
		   0x0000000000400be4 <+500>:	mov    edi,eax
		   0x0000000000400be6 <+502>:	call   0x400700 <write@plt>
		 */
		write(fd, &c, 0x1);
	}
	/*
	   0x0000000000400c05 <+533>:	mov    rax,QWORD PTR [rbp-0xa0]
	   0x0000000000400c0c <+540>:	add    rax,0x8
	   0x0000000000400c10 <+544>:	mov    rdx,QWORD PTR [rax]
	   0x0000000000400c13 <+547>:	mov    rax,QWORD PTR [rbp-0x88]
	   0x0000000000400c1a <+554>:	mov    esi,0x400dd2
	   0x0000000000400c1f <+559>:	mov    rdi,rax
	   0x0000000000400c22 <+562>:	call   0x4008c4 <log_wrapper>
	 */
	log_wrapper(log_f, "Finished back up ", av[1]);
	/*
	   0x0000000000400c27 <+567>:	mov    rax,QWORD PTR [rbp-0x80]
	   0x0000000000400c2b <+571>:	mov    rdi,rax
	   0x0000000000400c2e <+574>:	call   0x400710 <fclose@plt>
	 */
	fclose(f);
	/*
	   0x0000000000400c33 <+579>:	mov    eax,DWORD PTR [rbp-0x78]
	   0x0000000000400c36 <+582>:	mov    edi,eax
	   0x0000000000400c38 <+584>:	call   0x400770 <close@plt>
	 */
	close(fd);
	return (0);
}
