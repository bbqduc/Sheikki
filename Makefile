CC = g++ -Wall -Wextra -Werror -Wno-write-strings -pedantic -Wall -Wextra -O3 -I/usr/local/include -I.
SFML = -lsfml-window -lsfml-system -lsfml-graphics
CPPS = main.cpp entity.cpp model.cpp graphics.cpp engine.cpp 3ds_loader.cpp projectile.cpp tank.cpp
OBJS = main.o entity.o model.o graphics.o engine.o 3ds_loader.o
.depend: depend
depend: $(CPPS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^>>./.depend;
include .depend
all: main.o entity.o model.o graphics.o engine.o 3ds_loader.o projectile.o tank.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o projectile.o tank.o -framework OpenGL -lGLEW $(SFML)
windows: main.o entity.o model.o graphics.o engine.o 3ds_loader.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o -lmingw32 -lopengl32 -lglu32 -lglew32 $(SFML)
linux: main.o entity.o model.o graphics.o engine.o 3ds_loader.o projectile.o tank.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o projectile.o tank.o -lGL -lGLU -lGLEW -lXrandr $(SFML)
osx: main.o entity.o model.o graphics.o engine.o 3ds_loader.o projectile.o tank.o
	$(CC) -o main main.o entity.o model.o graphics.o engine.o 3ds_loader.o projectile.o tank.o  -lGLEW -framework OpenGL $(SFML)
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
projectile.o:
	$(CC) -c projectile.cpp
tank.o:
	$(CC) -c tank.cpp
clean:
	rm *.o
