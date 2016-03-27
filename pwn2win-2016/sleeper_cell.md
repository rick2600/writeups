# Pwn2Win 2016 Sleeper Cell [Rev - 70]

## Challenge
The challenge was to reverse a binary (ELF 64-bit) and find the right input. 

# Solving
The first thing I did was to run strings and see what information I could get, for my surprise there was a suspicous strings embedded: **FYM-OI}olte_zi_wdqedd_djrzuj_shgmEDFqo{**

After processing the user input the binary keeps the result in memory, with the string in hand I decided to take the easiest approach and try to bruteforce it.

**Idea**

1. Patch the binary at 0x400ebb with int3 (0xcc), it will make it stop after processing the input.

2. Force coredump (ulimit -c unlimited)

3. Write a python script to compare data in coredump

```python

import string
import os
 
flag = 'CTF-BR{'
expected = 'FYM-OI}olte_zi_wdqedd_djrzuj_shgmEDFqo{'
 
while True:
  print flag
  for ch in (string.letters + '_' + '}'): 
    os.system('echo %s |./sleeper_cell_patched' %(flag + ch)) 
    os.system('strings ./core|grep "FYM-OI" > out') 
    with open('out', 'r') as f:
      res = f.readlines()[-1].rstrip()
 
      if expected.startswith(res):
        flag += ch
        break
 
  if res == expected:
    print flag
    exit(0)        
```

$ python brute.py 2> /dev/null

...

**CTF-BR{riot_in_public_square_vgzdLIEjd}**


