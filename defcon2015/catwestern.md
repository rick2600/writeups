# Defcon Quals 2015 - catwestern (writeup)

####Description

 - catwestern (1 pts)
 - catwestern_631d7907670909fc4df2defc13f2057c.quals.shallweplayaga.me 9999
 - [Code to solve](https://github.com/rick2600/writeups/blob/master/defcon2015/defcon_catwestern.c)

####Playing
The server sends an initial state for registers and some bytes, this bytes are opcodes for instructions. Setting the state for the registers, executing the instructions and send back the register values to the server we can get the flag.

```
nc catwestern_631d7907670909fc4df2defc13f2057c.quals.shallweplayaga.me 9999
****Initial Register State****
rax=0xbe4c81b073ceb686
rbx=0x53d27b5a52b6304d
rcx=0x2f9c2d306829d925
rdx=0x23426a76826e5d6e
rsi=0xb4b5635595a5e59a
rdi=0x6200156657a17ed4
r8=0x75e7839df88278e5
r9=0xa523cfa74bfebcd
r10=0x7f07fbbdc8e58883
r11=0xc3fcd68acc5f5ad0
r12=0x103d0f438c899688
r13=0xedcf1c1ccc545c74
r14=0x6127c994d475185a
r15=0x371a24a18f04e1ca
****Send Solution In The Same Format****
About to send 84 bytes: 
I1�I��  ��>H��Hr��yI��I��H��U�Hi�+�FHM���H��H�Ǔ_k+L��H��L��H�3(H��I��L1�H�u�d


rick@rland:defcon-2015$ ./defcon_catwestern 
The flag is: Cats with frickin lazer beamz on top of their heads!
```


###The flag: Cats with frickin lazer beamz on top of their heads!
