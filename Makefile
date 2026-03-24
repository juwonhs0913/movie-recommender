CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
# 파일 설정
TARGET = movie
SRCS = main.cpp Movie.cpp
OBJS = $(SRCS:.cpp=.o)	# main.cpp → main.o 자동 변환
# 기본 타겟
all: $(TARGET)
# 링크: 모든 .o 파일을 합쳐서 실행 파일 생성
$(TARGET): $(OBJS)
	@echo "링크 중: $^"
	$(CXX) $(CXXFLAGS) -o $@ $^
# 패턴 규칙: 모든 .o 파일 생성 규칙
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# 헤더 의존성
main.o: Movie.h
Movie.o: Movie.h
# 정리
clean:
	rm -f $(TARGET) $(OBJS)
# 실행
run: $(TARGET)
	./$(TARGET)
.PHONY: all clean run