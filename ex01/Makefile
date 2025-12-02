
NAME	 =  RPN
CXX		 = 	c++
CXXFLAGS =	-Wall -Wextra -Werror -std=c++98

SRC		 = 	main.cpp RPN.cpp
OBJ		 = 	$(SRC:.cpp=.o)
HEADER	 = 	RPN.hpp

GREEN	 =	\033[0;32m
YELLOW	 =	\033[1;33m
RED		 =	\033[0;31m
RESET	 =	\033[0m

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo "$(YELLOW)[Executing...]$(RESET)"
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo	"$(GREEN) Done!!!:$(NAME) built successfully!$(RESET)"

clean:
	@echo "$(RED)[Cleaning object files...]$(RESET)"
	@rm -f $(OBJ)

fclean: clean
	@echo "$(RED)[Rmoving Executable...]$(RESET)"
	@rm -f $(NAME)

re: fclean all

%.o: %.cpp $(HEADER)
	@echo "$(YELLOW)[Compiling $<...]$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean fclean re run