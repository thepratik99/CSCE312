@17
D=A
@SP
AM=M+1
A=A-1
M=D
@17
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT1
D;JEQ
@SP
A=M-1
M=0
@VAR1
0;JMP
(NEXT1)
@SP
A=M-1
M=-1
(VAR1)
@17
D=A
@SP
AM=M+1
A=A-1
M=D
@16
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT2
D;JEQ
@SP
A=M-1
M=0
@VAR2
0;JMP
(NEXT2)
@SP
A=M-1
M=-1
(VAR2)
@16
D=A
@SP
AM=M+1
A=A-1
M=D
@17
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT3
D;JEQ
@SP
A=M-1
M=0
@VAR3
0;JMP
(NEXT3)
@SP
A=M-1
M=-1
(VAR3)
@892
D=A
@SP
AM=M+1
A=A-1
M=D
@891
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT4
D;JLT
@SP
A=M-1
M=0
@VAR4
0;JMP
(NEXT4)
@SP
A=M-1
M=-1
(VAR4)
@891
D=A
@SP
AM=M+1
A=A-1
M=D
@892
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT5
D;JLT
@SP
A=M-1
M=0
@VAR5
0;JMP
(NEXT5)
@SP
A=M-1
M=-1
(VAR5)
@891
D=A
@SP
AM=M+1
A=A-1
M=D
@891
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT6
D;JLT
@SP
A=M-1
M=0
@VAR6
0;JMP
(NEXT6)
@SP
A=M-1
M=-1
(VAR6)
@32767
D=A
@SP
AM=M+1
A=A-1
M=D
@32766
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT7
D;JGT
@SP
A=M-1
M=0
@VAR7
0;JMP
(NEXT7)
@SP
A=M-1
M=-1
(VAR7)
@32766
D=A
@SP
AM=M+1
A=A-1
M=D
@32767
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT8
D;JGT
@SP
A=M-1
M=0
@VAR8
0;JMP
(NEXT8)
@SP
A=M-1
M=-1
(VAR8)
@32766
D=A
@SP
AM=M+1
A=A-1
M=D
@32766
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
D=M-D
@NEXT9
D;JGT
@SP
A=M-1
M=0
@VAR9
0;JMP
(NEXT9)
@SP
A=M-1
M=-1
(VAR9)
@57
D=A
@SP
AM=M+1
A=A-1
M=D
@31
D=A
@SP
AM=M+1
A=A-1
M=D
@53
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=D+M
@112
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=M-D
@SP
A=M-1
D=M
M=-D
@SP
AM=M-1
D=M
A=A-1
M=D&M
@82
D=A
@SP
AM=M+1
A=A-1
M=D
@SP
AM=M-1
D=M
A=A-1
M=D|M
@SP
A=M-1
D=M
M=!D
