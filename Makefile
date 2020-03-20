CC		:= g++
TARGET		:= main
FLAGS		:= -std=c++17
LIBS		:= -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl -lSOIL
SOURCE		:= $(wildcard Source/*.cpp context/*.cpp)
HEADERS		:= $(wildcard Source/*.hpp context/*.hpp)
OBJS		:= $(patsubst %.cpp, %.o, $(SOURCE))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CC) -o $@ -c $< $(FLAGS)

.PHONY: all clean debug
