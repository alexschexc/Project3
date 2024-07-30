CPP = g++ -g
CFLAGS = -I. -pthread
LDFLAGS = -pthread

all: pipegrep

pipegrep: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(CPP) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

clean:
	rm -f pipegrep *.o
