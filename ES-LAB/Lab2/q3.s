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
    MOV R3,#0

    LDR R1,[R0],#4
	LDR R5,[R0]
    SUBS R3, R1,R5
    STR R2,[R3]
    
STOP 
    B STOP
SRC1 DCD 12,10
     AREA mydata,DATA,READWRITE
DST DCD 0

    END
