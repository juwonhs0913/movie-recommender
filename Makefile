CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TARGET = movie
SRCS = main.cpp Movie.cpp Rating.cpp User.cpp MovieManager.cpp RatingManager.cpp UserManager.cpp SimilarityCalculator.cpp
OBJS = $(SRCS:.cpp=.o)	

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: Movie.h
Movie.o: Movie.h
Rating.o: Rating.h
User.o: User.h
MovieManager.o: MovieManager.h
RatingManager.o: RatingManager.h
UserManager.o: UserManager.h
SimilarityCalculator.o = SimilarityCalculator.h


clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
