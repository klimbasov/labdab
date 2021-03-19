.model small

.const
POLE_X		equ	1
POLE_y		equ	2
POLE_SIZE_X	equ	3
POLE_SIZE_Y	equ	4

MAX_SPEED	equ	5
ACCELERATION	equ	6

raw_pos		equ	0
collumn_pos	equ	1

MAX_PLAIN_QUANTITY	equ	7

.data

DOODLE_POINT	dw	2 dup(?)
ARR_PLAIN_POINT	dw	MAX_PLAIN_QUANTITY+MAX_PLAIN_QUANTITY dup(?)
MONSTER_POINT	dw	2 dup(?)

SPEED_X		db	?
SPEED_Y		db	?

SCORE		dw	0


doodle_sprite	dw	0h,1fh,'_',1fh,0h,1fh,
			'^',1fh,0h,1fh, '^',1fh,'_',1fh,
			'|',1fh,'|',1fh,'|',1fh


monster_sprite	dw	0h,1fh,'_',1fh,0h,1fh,'_',ifh,0h,1fh
			'<',1fh,'0',1fh,'_',1fh,'0',1fh,'>',1fh,
			0h,1fh,'-',1fh,0h,1fh,'-',1fh,0h,1fh

plain_g_sprite	dw	'_',1fh,'_',1fh,'_',1fh,'_',1fh
plain_b_sprite	dw	'_',1fh,'_',1fh,'_',1fh,'_',1fh
plain_r_sprite	dw	'_',1fh,'_',1fh,'_',1fh,'_',1fh

		



.stack	100h

.code

start:

mov ax,@data
mov ds, ax
mov es, ax




end start
