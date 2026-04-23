CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = movie
SRCS = main.cpp Movie.cpp Rating.cpp User.cpp MovieManager.cpp UserManager.cpp
OBJS = $(SRCS:.cpp=.o)	

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: Movie.h
Movie.o: Movie.h
Rating.o: Movie.h
User.o: Movie.h
Manager.o: Manager.h


clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
