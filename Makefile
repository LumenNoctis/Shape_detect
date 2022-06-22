NAME = draw

DEBUG_FLAGS = -fsanitize=address -g
FLAGS = 
INCLUDES = -I includes/ -I includes/SDL2/ -I includes/MT/ -I includes/SDLX/ 

LIB_DIR = libs/
LIBRARIES= -l SDL2 -l SDL2_image -l SDL2_ttf -lm

MT_DIR = MT/
SDLX_DIR = SDLX/
SRCS_DIR = srcs/

BIN_DIR = bin/

MT_NAMES =			\
		MT_v2		\
		MT			\

SDLX_NAMES =		\
		SDLX_debug	\
		SDLX_init	\
		SDLX_input	\
		SDLX_render	\
		SDLX_utils	\

SRC_FILES =			\
	$(addprefix $(MT_DIR), $(MT_NAMES))		\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))	\
	main				\
	draw				\
	compute				\
	visualizer			\

SRCS = $(addprefix $(SRCS_DIR),$(addsuffix .c, $(SRC_FILES)))

OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBRARIES) $(DEBUG_FLAGS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Add header files here
$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

run: re clean
	./$(NAME)

clean:
	rm -rf $(BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all