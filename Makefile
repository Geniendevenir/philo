# Standard
NAME				= philo

# Directories
INC					= inc/
SRC_DIR				= srcs/
OBJ_DIR				= obj/

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Wextra -Werror -I$(INC)
RM					= rm -f

# Concatenate all source files
SRCS 				=	srcs/main.c\
						srcs/philo_check_arg.c\
						srcs/philo_init_arg.c\
						srcs/philo_init_threads.c\
						srcs/philosopher.c\
						srcs/philo_alone.c\
						srcs/philo_sync.c\
						srcs/philo_time.c\
						srcs/philo_set_get.c\
						srcs/philo_finish.c\
						srcs/philo_utils.c\
						srcs/philo_free.c\

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
start:				
					make all

all: 				$(NAME)

$(NAME):			$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@

clean:
					$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Phony targets represent actions not files
.PHONY: 			start all clean fclean re
