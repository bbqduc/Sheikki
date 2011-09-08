CC = g++ -Wall -Wextra -Wno-write-strings -pedantic -Wall -Wextra
SFML = -lsfml-window -lsfml-system -lsfml-graphics
CPPS = main.cpp mymatrix.cpp entity.cpp model.cpp graphics.cpp engine.cpp
OBJS = main.o mymatrix.o entity.o model.o graphics.o engine.o
.depend: depend
depend: $(CPPS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;
include .depend
all: main.o mymatrix.o entity.o model.o graphics.o engine.o
	$(CC) -o main main.o mymatrix.o entity.o model.o graphics.o engine.o -framework OpenGL -lGLEW $(SFML)
windows: main.o mymatrix.o entity.o model.o graphics.o engine.o
	$(CC) -o main main.o entity.o model.o graphics.o mymatrix.o engine.o -lmingw32 -lopengl32 -lglu32 -lglew32 $(SFML)
linux: main.o mymatrix.o entity.o model.o graphics.o engine.o
	$(CC) -o main main.o entity.o model.o graphics.o mymatrix.o engine.o -lGL -lGLU -lGLEW -lXrandr $(SFML)
matrix_test: mymatrix.o test_matrix.o
	$(CC) -o matrix_test mymatrix.o test_matrix.o
main.o:
	$(CC) -c main.cpp
mymatrix.o:
	$(CC) -c mymatrix.cpp
test_matrix.o:
	$(CC) -c test_matrix.cpp
entity.o:
	$(CC) -c entity.cpp
model.o: 
	$(CC) -c model.cpp
graphics.o:
	$(CC) -c graphics.cpp
engine.o:
	$(CC) -c engine.cpp
clean:
	rm *.o
