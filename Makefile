CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
TARGET = movie
SRCDIR = src
OBJDIR = obj

OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/MovieManager.o \
       $(OBJDIR)/Movie.o \
       $(OBJDIR)/User.o \
       $(OBJDIR)/UserManager.o \
       $(OBJDIR)/Rating.o \
       $(OBJDIR)/RatingManager.o \
       $(OBJDIR)/Recommender.o

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(TARGET) $(OBJDIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run