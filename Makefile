hard: codewars.c
	cc -o codewars -std=c99 -lm -Wall -Werror codewars.c

easy: codewars.c
	cc -o codewars -std=c99 -lm codewars.c

debug: codewars.c
	cc -g -o codewars -std=c99 -lm codewars.c

hdebug: codewars.c
	cc -g -o codewars -std=c99 -lm -Wall -Werror codewars.c

purgecore:
	rm vg*
