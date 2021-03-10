  AREA RESET, DATA, READONLY
    EXPORT __Vectors
    
__Vectors
    DCD 0x40001000
    DCD Reset_Handler
    ALIGN
    AREA mycode, CODE, READONLY
    ENTRY
    EXPORT Reset_Handler

 

Reset_Handler
    LDR R0,=SRC1
    LDR R2,=DST
    MOV R4,#10
    MOV R3,#0
BACK
    LDR R1,[R0],#4
    ADD R3,R3,R1
    SUBS R4,#1 ;If we remove s from subs then the z flag will not change and hence the cmp instruction is necessary 
    CMP R4,#0 ; if we use subs instruction, then when r4 becomes 0, z flag is automatically made 0 and hence cmp instruction is not required
    BNE BACK
    STR R3,[R2]
    
STOP 
    B STOP
SRC1 DCD 1,2,3,4,5,6,7,8,9,10
     AREA mydata,DATA,READWRITE
DST DCD 0

 

    END