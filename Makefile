CXXFLAGS =	-std=c++11 -O2 -g -Wall -fmessage-length=0 

OBJS =	include/glad/glad.o	include/draw.o 00_Tesis.o

LIBS = -lSDL2 -lGL -lGLU -lglut -lARX -ldl -lGLEW -Iinclude

TARGET =	00_Tesis

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
