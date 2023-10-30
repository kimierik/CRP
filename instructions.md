# Quide

all instructions are formatted as such  
|XX|XXXXXX|
|:--:|:--:|
|CMD| params|

CMD the 2 most significant bits determine the instruction that will be run  

## instructions 
00 PRINT  
01 command instruction  
10 inc pointer  
11 inc value  


## print
|00|0|0|0|000|
|:---:|:---:|:---:|:---:|:---:|
|CMD|p|f| a| b|

p = pointer that is used  
 - 0 freePointer
 - 0 instructionPointer

f = format
 - 0 prints the value as char
 - 1 prints the value as int

a = pointer or value
 - 0 prints the value at the pointer
 - 1 prints the pointers value

b= if all b bits are 0 the instruction will not print  
 - this is to prevent un assigned instructions from spamming  





## command instruction
runs an instruction X amount of times  
  
|01|0|00000|
|:---:|:---:|:------:|
|CMD|p|amount|

p(pointer)= execute command at what pointer
 - 0 freePointer  
 - 1 instructionPointer  

amount= amount of times this instruction is ran 
 - 0000 means its ran once


the command will execute the instruction that is at the pointer. Meaning that moving the pointer while this instruction is runnig will change what instruction is going to be ran  
if the instruction at the pointer changes during the execution the command will interpret the new instruction  
  
the instruction pointer does not move automatically when this command is being run   


## increment pointer
moves a pointer  
  
|10|0|00000|
|:---:|:---:|:------:|
|CMD|p|amount|

p(pointer)= what pointer to increment  
 - 0 freePointer  
 - 1 instructionPointer  

amount = how much to increment 
 - 00000 means 1

## increment value
increments a value at pointer  
  
|11|0|00000|
|:---:|:---:|:------:|
|CMD|p|amount|

p(pointer)= increment value at pointer
 - 0 freePointer  
 - 1 instructionPointer  

amount = how much to increment 
 - 00000 means 1


