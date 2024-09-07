## level06

	username: level06
	password: h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq

### Mitigations applied:

```
$ checksec --file level06
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   level06
```

### Usage:

```
$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: 123123
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 123
```

### Analysis:

It takes the `login` using `fgets()`,

```
/*
   0x080488cf <+86>:	mov    eax,ds:0x804a060
   0x080488d4 <+91>:	mov    DWORD PTR [esp+0x8],eax
   0x080488d8 <+95>:	mov    DWORD PTR [esp+0x4],0x20
   0x080488e0 <+103>:	lea    eax,[esp+0x2c]
   0x080488e4 <+107>:	mov    DWORD PTR [esp],eax
   0x080488e7 <+110>:	call   0x8048550 <fgets@plt>
 */
fgets(buf, 0x20, stdin);
```

and the serial using `scanf()`.

```
/*
   0x0804891d <+164>:	mov    eax,0x8048a60
   0x08048922 <+169>:	lea    edx,[esp+0x28]
   0x08048926 <+173>:	mov    DWORD PTR [esp+0x4],edx
   0x0804892a <+177>:	mov    DWORD PTR [esp],eax
   0x0804892d <+180>:	call   0x80485e0 <__isoc99_scanf@plt>
 */
scanf("%u", &serial);
```

Then `auth()` is called with the login and serial as arguments.

```
/*
   0x08048932 <+185>:	mov    eax,DWORD PTR [esp+0x28]
   0x08048936 <+189>:	mov    DWORD PTR [esp+0x4],eax
   0x0804893a <+193>:	lea    eax,[esp+0x2c]
   0x0804893e <+197>:	mov    DWORD PTR [esp],eax
   0x08048941 <+200>:	call   0x8048748 <auth>
   0x08048946 <+205>:	test   eax,eax
   0x08048948 <+207>:	jne    0x8048969 <main+240>
 */
if (auth(buf, serial) != 0) {...}
```

And if it returns `0`, `system("/bin/sh")` is called.

```
/*
   0x08048956 <+221>:	mov    DWORD PTR [esp],0x8048b61
   0x0804895d <+228>:	call   0x80485a0 <system@plt>
   0x08048962 <+233>:	mov    eax,0x0
 */
system("/bin/sh");
```

auth function verifies that the length of the login is greater than 5.

```
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

```

Then it calls `ptrace()` and returns `1` if it fails.

```
/*
   0x08048796 <+78>:	mov    DWORD PTR [esp+0xc],0x0
   0x0804879e <+86>:	mov    DWORD PTR [esp+0x8],0x1
   0x080487a6 <+94>:	mov    DWORD PTR [esp+0x4],0x0
   0x080487ae <+102>:	mov    DWORD PTR [esp],0x0
   0x080487b5 <+109>:	call   0x80485f0 <ptrace@plt>
   0x080487ba <+114>:	cmp    eax,0xffffffff
   0x080487bd <+117>:	jne    0x80487ed <auth+165>
 */
if (ptrace(PTRACE_TRACEME, 0x0, 0x1, 0x0) == -1) {...}
```

After that, for each character in the login, some calculations are made and added together.

```
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
```

The result is compared to the serial, if they're equal `0` is return.

### Exploit

To exploit this binary, we tried to run it in `gdb` and note the result being compared with our serial, then run the program agin outside `gdb` with the same `login` and the serial revealed in `gdb`.

```
$ gdb -q ./level06
```

In gdb the call to `ptrace()` fails.

```
(gdb) r < <(echo -e "123123\n123")
Starting program: /home/users/level06/level06 < <(echo -e "123123\n123")
...
.---------------------------.
| !! TAMPERING DETECTED !!  |
'---------------------------'
```

To bypass this, we set a beak point after `ptrace()` returns, and a breakpoint at the instruction whre the comparison is made. Then rerun the program

```
(gdb) b *auth+114
(gdb) b *auth+286
(gdb) r < <(echo -e "123123\n123")
```

After hitting the first breakpoint, we changed the value of `eax` which contains the return of `ptrace()`

```
Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax = 0
(gdb) c
```

At the second breakpoint, we examined the value being compared with our serial.

```
(gdb) x/i $pc
=> 0x8048866 <auth+286>:	cmp    eax,DWORD PTR [ebp-0x10]
(gdb) x/d $ebp-0x10
0xffffd6a8:	6231528
```

Now that we have the right serial, we moved out of gdb and ran the program with the same login `123123` and the serial `6231528`

```
$ (echo -e "123123\n6231528";cat) | ./level06
...
whoami
level07
```
