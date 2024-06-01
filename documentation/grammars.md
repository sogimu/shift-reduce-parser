// F
N          -> F
--N        -> F
BOL -N EOL -> F

// SUM
F+F   -> SUM
CE+CE -> SUM

// DIFF
F-F   -> DIFF
CE-CE -> DIFF

// E
SUM       -> E
DIFF      -> E
BOL E EOL -> E

//CE
E      -> CE
F      -> CE
(NAME) -> CE

//VA
NAME=CE -> VA

//P
PRINT(CE); -> P

//CondE
CE==CE -> CondE
CE<CE  -> CondE
CE>CE  -> CondE

//Exp
IfExp  -> Exp
P      -> Exp
CE;    -> Exp
CondE; -> Exp
VA;    -> Exp

//S
{E*}        -> S
BOL S EOL   -> S
BOL Exp EOL -> S

//IfExp
if CondE S -> IfExp