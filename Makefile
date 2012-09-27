CC= gcc
EXEC= p1
OBJS= main.o shape.o
ifeq ($(shell uname), Linux)
    LIBS= -lglut -lGLEW -lGL
else ifeq ($(shell uname), Darwin)
    LIBS= -lGLEW -framework GLUT -framework OpenGL
else
    LIBS= -lfreeglut -lglew32 -lopengl32 -lwinmm -lgdi32
endif
$(EXEC) : $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LIBS)
%.o : %.c
	$(CC) -c $<
clean :
	rm $(EXEC) $(OBJS)
