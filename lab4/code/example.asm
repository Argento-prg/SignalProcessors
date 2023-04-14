w 		.def	_dotp
_dotp:
;cycle1:
		MVK		.S1 256,A1
	||	ZERO	.L1 A7
	||	LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
;cycle2:
		LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
;	|| [A1] SUB .S1   A1, 1,A1
;cycle3:
		LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
;	|| [A1] SUB .S1   A1, 1,A1
;	|| 	[A1]	B	.S2	loop
;cycle4:
		LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
	|| [A1] SUB .S1   A1, 1,A1
;	|| [A1]	B	.S2	loop
;cycle5:
		LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
    || [A1] SUB .S1   A1, 1,A1
;	|| [A1]	B	.S2	loop
;    ||  MPY .M1x  A2, B2, A6
;cycle6:
		LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
    || [A1] SUB .S1   A1, 1,A1
;	|| [A1]	B	.S2	loop
;    ||  MPY .M1x  A2, B2, A6
;cycle7:
		LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
    ||  ADD .L1   A6, A7, A7
    || [A1] SUB .S1   A1, 1,A1
	|| [A1]	B	.S2	loop
    ||  MPY .M1x  A2, B2, A6
;cycle8:
loop:
		LDH .D1   *A4++, A2
	||	LDH .D2   *B4++, B2
    || [A1] SUB .S1   A1, 1,A1
	|| [A1]	B	.S2	loop
    ||  MPY .M1x  A2, B2, A6
    ||  ADD .L1   A6, A7, A7
;cycles9:
           MPY .M1x  A2, B2, A6
    ||    ADD .L1   A6, A7, A7
	|| [A1]	B	.S2	loop
;	|| 	[A1]	B	.S2	loop
;cycles10:
           MPY .M1x  A2, B2, A6
   ||      ADD .L1   A6, A7, A7
;cycles11:
          MPY .M1x  A2, B2, A6
   ||      ADD .L1   A6, A7, A7
;cycles12:
          MPY .M1x  A2, B2, A6
   ||      ADD .L1   A6, A7, A7
;cycles13:
           MPY .M1x  A2, B2, A6
   ||      ADD .L1   A6, A7, A7 
;cycles14-15:	
			B  .S2	B3
	||		ADD .L1   A6, A7, A7
			ADD .L1   A6, A7, A7
    ||      MV		.S1 A7,A4
           nop	3				