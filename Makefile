CC = g++ -Wall -Wextra -Wno-write-strings -pedantic -Wall -Wextra -std=c++0x -O3
SFML = -lsfml-window -lsfml-system -lsfml-graphics
CPPS = main.cpp entity.cpp model.cpp graphics.cpp engine.cpp 3ds_loader.cpp matrix_utils.cpp mymatrix.cpp
OBJS = main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o
.depend: depend
depend: $(CPPS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;
include .depend
all: main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o -framework OpenGL -lGLEW $(SFML)
windows: main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o -lmingw32 -lopengl32 -lglu32 -lglew32 $(SFML)
linux: main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o -lGL -lGLU -lGLEW -lXrandr $(SFML)
osx: main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o matrix_utils.o -lGLEW -framework OpenGL $(SFML)
matrix_test: test_matrix.o
	$(CC) -o matrix_test test_matrix.o
main.o:
	$(CC) -c main.cpp
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
3ds_loader.o:
	$(CC) -c 3ds_loader.cpp
matrix_utils.o:
	$(CC) -c matrix_utils.cpp
clean:
	rm *.o
