mem_segments:
	gcc error_functions.c get_num.c mem_segments.c -o mem_segments.o

ouch:
	gcc error_functions.c get_num.c ouch.c -o ouch.o

real_timer: 
	gcc error_functions.c get_num.c real_timer.c -o real_timer.o
