CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
SRCS = main.cpp fcfs.cpp sjf.cpp srt.cpp rr.cpp hrrn.cpp feedback.cpp util.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = scheduler

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

test: $(TARGET)
	./run_tests.sh

pytest: $(TARGET)
	python3 run_tests.py

docker-build:
	docker build -t scheduler:latest .

.PHONY: test pytest docker-build
