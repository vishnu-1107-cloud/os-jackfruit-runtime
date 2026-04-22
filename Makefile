
all:
	gcc engine.c -o engine
	gcc supervisor.c -o supervisor
	gcc cpu_hog.c -o cpu_hog
	gcc memtest.c -o memtest
	gcc logging.c -lpthread -o logging
