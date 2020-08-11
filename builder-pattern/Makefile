CXX			:= g++
CXX_FLAGS	:= -Wall -Wextra -std=c++17

BIN			:= bin
EXECUTABLE	:= person

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): *.cpp *.hpp
	@echo "🚧 Building..."
	-mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) $^ -o $@

clean:
	@echo "🧹 Cleaning ..."
	-rm $(BIN)/*