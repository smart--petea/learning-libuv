intquit:
	gcc -O error_functions.c get_num.c intquit.c -o intquit.o

uv_signal:
	gcc uv_signal.c -luv -o uv_signal.o

setjmp_returned:
	gcc -O error_functions.c get_num.c setjmp_returned.c -o setjmp_returned.o

setjmp_vars_optimized:
	gcc -O error_functions.c get_num.c setjmp_vars.c -o setjmp_vars_optimized.o

setjmp_vars:
	gcc error_functions.c get_num.c setjmp_vars.c -o setjmp_vars.o

longjmp:
	gcc error_functions.c get_num.c longjmp.c -o longjmp.o

mem_segments:
	gcc error_functions.c get_num.c mem_segments.c -o mem_segments.o

ouch_uv:
	gcc ouch_uv.c -luv -o ouch_uv.o

ouch:
	gcc error_functions.c get_num.c ouch.c -o ouch.o

real_timer: 
	gcc error_functions.c get_num.c real_timer.c -o real_timer.o
