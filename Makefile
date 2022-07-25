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
	compute				\
	draw				\
	input               \
	main				\
	render				\
	utils				\
	visualizer			\

SRCS = $(addprefix $(SRCS_DIR),$(addsuffix .c, $(SRC_FILES)))

OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

run: all
	./$(NAME)

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBRARIES) $(DEBUG_FLAGS)

wasm: 
	emcc -O2 -0S$(SRCS) $(INCLUDES) -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 \
	--preload-file srcs/SDLX/defsault.ttf -o $(NAME).js

react:
	emcc -O2 $(SRCS) $(INCLUDES)\
	-s USE_SDL=2 \
	-s USE_SDL_TTF=2 \
	-s WASM=0 \
	-s MODULARIZE=1 \
	-s ENVIRONMENT=web \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s EXPORTED_RUNTIME_METHODS='["cwrap"]' \
	--preload-file srcs/SDLX/default.ttf \
	-o test.js

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Add header files here
$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) $(DEBUG_FLAGS) -c $< -o $@

run: re clean
	./$(NAME)

clean:
	rm -rf $(BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all