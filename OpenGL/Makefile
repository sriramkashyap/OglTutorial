CC = g++
CFLAGS = -I. -I../glm
LFLAGS = -lGL -lglut -lGLEW -lfreeimage

HDRS = $(shell find *.h)
CPPS = $(shell find *.cpp)
OBJS = $(CPPS:%.cpp=%.o)

%.o: %.cpp $(HDRS)
	$(CC) -c -o $@ $< $(CFLAGS)

ogl: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

.PHONY: clean

clean:
	rm *.o ogl
