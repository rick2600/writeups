#Defcon Quals 2015 - matwiz (writeup)


####Description

 - matwiz (1 pts)
 - mathwhiz_c951d46fed68687ad93a84e702800b7a.quals.shallweplayaga.me 21249

####Playing

The challenge is to solve some math operations sent by the server. Instead of write our own interpreter, we can use the good, old and unsafe :p eval()

```
rick@rland:defcon-2015$ python defcon_matwiz.py 
3 - 2 
3 - 1 
1 + 1 
2 - 1 
...
3 + 2 - 2 
(1 + 2) 
2 + {2 - 1} 
You won!!!
The flag is: Farva says you are a FickenChucker and you'd better watch Super Troopers 2
```

### Farva says you are a FickenChucker and you'd better watch Super Troopers 2
