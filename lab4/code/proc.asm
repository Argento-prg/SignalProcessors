;		.def	_proc
;_proc:
;		MVK		.S1 256,A1
;	||	MVK		.S2 2,B6
;		ZERO	.L1 A7
;loop:	LDH		.D1 *A4++,A2
;	||	LDH 	.D2 *B4++,B2
;		NOP		4
;		MPY		.M1x A2,B2,A6
;		NOP
;	||	MPY		.M2 B2,B6,B7
;		NOP
;		ADD		.L1 A6,A7,A7
;		SUB		.L2 A7,B7,A7
;	||	SUB		.S1 A1,1,A1
;	[A1]	B		.S2 loop
;		NOP		3
;		MV		.S1 A7,A4
;	||	B 		.S2 B3	
;		NOP		5
		.def	_proc
_proc:
	MVK .S1 256,A1
	MVK .S2 2,B6
	ZERO  .L1 A7
loop:  LDH .D1 *A4++,A2
	LDH .D2 *B4++,B2
	NOP 4
	MPY .M2 A2,B2,B5
	NOP
	||MPY .M2 B2,B6,B7
	NOP
	||ADD .L1 A7,B5,A7
	SUB .L1x A7,B7,A7
	SUB .S1 A1,1,A1
	[A1]  B  .S2 loop
	NOP 5
	MV .S1 A7,A4
	B .S2 B3
	NOP 5


