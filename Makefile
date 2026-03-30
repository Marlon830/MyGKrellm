##
## EPITECH PROJECT, 2022
## Paradigm pool
## File description:
## Makefile
##

SRC = src/Main.cpp \
		src/Krell.cpp \
		src/modules/DateTime.cpp \
		src/modules/Battery.cpp \
		src/modules/NetworkLoad.cpp \
		src/modules/ProcessusInfo.cpp \
		src/displays/SFMLDisplay.cpp \
		src/modules/CpuInfo.cpp \
		src/modules/SystemInfo.cpp \
		src/modules/Ram.cpp \
		src/displays/NcurseDisplay.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I./src/include -I./src/interface

TARGET = MyGKrellm

all : $(TARGET)

$(TARGET) : $(OBJ)
	g++ -o $(TARGET) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lncurses

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(TARGET)

re : fclean all
