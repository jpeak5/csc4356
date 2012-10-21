VPATH = Util3d/

CC= gcc -Wall
EXEC= p2
OBJS= main.o shape.o plane.o image.o shader.o

ifeq ($(shell uname), Linux)
    LIBS= -lglut -lGLEW -lGL -ltiff -ljpeg -lpng
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
