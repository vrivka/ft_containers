NAME = test_ft

NAME_S = test_std

HEADER = ft_map.hpp				\
         ft_pair.hpp			\
         ft_reverse_iterator.hpp\
         ft_set.hpp				\
         ft_stack.hpp			\
         ft_tree_iterator.hpp	\
         ft_utilities.hpp		\
         ft_vec_iterator.hpp	\
         ft_vector.hpp			\
         RBNode.hpp

SRCS =	main.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -std=c++98 -Wall -Werror -Wextra

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADER)
		clang++ $(CFLAGS) -o $(NAME) $(OBJS)
		clang++ $(CFLAGS) -o $(NAME_S) $(OBJS) -D _NMSPC=std

test:	$(NAME) $(NAME_S)
		./$(NAME) > ft.txt
		./$(NAME_S) > std.txt
		diff ft.txt std.txt

%.o:	%.cpp
		clang++ $(CFLAGS) -c $< -o $@ -I.

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME) $(NAME_S)
		$(RM) ft.txt std.txt

re:		fclean all

.PHONY: all bonus clean fclean re