# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall
#CXXFLAGS = -std=c++11 -O3 -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
DIRS = $(OBJ_FOLDER) $(OBJ_FOLDER)modulo1 

# all sources, objs, and header files
MAIN = Main
TARGET = tp1.out
SRC = $(wildcard $(SRC_FOLDER)*.cpp) \
	  $(wildcard $(SRC_FOLDER)modulo1/*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp $(DIRS)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

$(DIRS):
	@mkdir -p $(OBJ_FOLDER)modulo1

all: $(DIRS) $(OBJ) 
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*
