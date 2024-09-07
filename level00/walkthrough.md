## level00

	username: level00
	password: level00

### Mitigations applied:

```
$ checksec --file level00
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   level00
```

### Usage:

The program prompt the user for a password, and exits if invalid.

```
$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:test

Invalid Password!
```

### Analysis:

`scanf` is used with the flag `%u` to get a number from the user.

```
	/*
	   0x080484ce <+58>:	mov    eax,0x8048636	// "%d"
	   0x080484d3 <+63>:	lea    edx,[esp+0x1c]	// var1
	   0x080484d7 <+67>:	mov    DWORD PTR [esp+0x4],edx
	   0x080484db <+71>:	mov    DWORD PTR [esp],eax
	   0x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
	 */
	scanf("%d", &var1);
```

This number is compared to `0x149c` which is equal to `5276` in decimal.

```
	/*
	   0x080484e3 <+79>:	mov    eax,DWORD PTR [esp+0x1c]
	   0x080484e7 <+83>:	cmp    eax,0x149c
	   0x080484ec <+88>:	jne    0x804850d <main+121>
	 */
	if (var1 != 0x149c) /* 5276 */
	{...}
```

If they are equal `system("/bin/sh") is called.

```
	/*
	   0x080484fa <+102>:	mov    DWORD PTR [esp],0x8048649
	   0x08048501 <+109>:	call   0x80483a0 <system@plt>
	 */
	system("/bin/sh");
```

### Exploit

To exploit this binary we simply insert the number `5276` as the password

```
$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
```
