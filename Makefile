NAME = Rush

DEBUG_FLAGS = -fsanitize=address
FLAGS = -g $(DEBUG_FLAGS)
INCLUDES = -I includes/ -I includes/SDL2/ -I includes/SDLX/ -I includes/MT -I includes/structs/

LIB_DIR = libs/
LIBRARIES = $(LIB_DIR)libSDL2-2.0.0.dylib $(LIB_DIR)libSDL2_image-2.0.0.dylib $(LIB_DIR)libSDL2_ttf-2.0.0.dylib
STATIC_LIB = -L -l $(LIB_DIR)libSDLX.a

MT_DIR = MT/
SDLX_DIR = SDLX/
BUTTON_DIR = buttons/
SCREEN_DIR = screens/
SPELL_DIR = spells/
ENEMY_DIR = enemies/
AREAS_DIR = areas/
SRCS_DIR = srcs/

BIN_DIR = bin/


SDLX_NAMES = 			\
	SDLX_anim			\
	SDLX_collision		\
	SDLX_editor			\
	SDLX_input			\
	SDLX_LevelManager	\
	SDLX_render			\
	SDLX_UI				\
	SDLX_utils			\
	SDLX				\

MT_NAMES = 				\
	MT_v2				\
	MT					\

AREAS_NAMES = 			\
	areas_init			\

BUTTON_NAMES =			\
	b_main_level		\
	b_main_menu			\

ENEMY_NAMES = 			\
	enemies_fn			\

INIT_NAMES = 			\
	init_buttons		\
	init_enemies		\
	init_game			\
	init_level			\
	init_spells			\

SCREEN_NAMES =			\
	main_level			\
	main_menu			\
	start_menu			\
	test_lvl			\
	utils				\

SPELL_NAMES =			\
	fireball			\
	spells_utils		\


SRCS_NAMES =									\
	$(addprefix $(SDLX_DIR),	$(SDLX_NAMES))	\
	$(addprefix $(MT_DIR),		$(MT_NAMES))	\
	$(addprefix $(BUTTON_DIR),	$(BUTTON_NAMES))\
	$(addprefix $(SCREEN_DIR),	$(SCREEN_NAMES))\
	$(addprefix $(SPELL_DIR),	$(SPELL_NAMES))	\
	$(addprefix $(ENEMY_DIR),	$(ENEMY_NAMES))	\
	$(addprefix $(AREAS_DIR),	$(AREAS_NAMES))	\
	debug				\
	init				\
	main 				\
	utils				\

C_FILES =				\
	$(SRCS_NAMES) 		\

C_FILES =				\
	$(addprefix $(SRCS_DIR), $(SRCS_NAMES))		\

SRCS = $(addsuffix .c, $(C_FILES))

OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all : $(NAME)

editor :
	gcc $(FLAGS) $(INCLUDES) -o editor srcs/editor_main.c srcs/SDLX/*.c	$(LIBRARIES)

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBRARIES)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

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

e_clean :
	rm -f editor
e_re : e_clean editor
