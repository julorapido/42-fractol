NAME = fractol
SRCS_ = fractol.c window.c draw.c
SRCS_OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra

LIBFT_DIR = ./Libft 

UNAME =$(shell uname -s)
ifeq ($(shell uname -s), Linux)
	INCLUDES = -I/usr/include -Imlx -I$(LIBFT_DIR)/libft.h
else
	INCLUDES = -I/opt/X11/include -Imlx -I$(LIBFT_DIR)/libft.h
endif
 
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname -s), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
 

all: $(MLX_LIB) $(NAME)

ifeq (1, 1)
.c.o:
	gcc $(CFLAGS) -c -o $@ $< $(INCLUDES) -I./includes
endif

$(NAME): $(SRCS_OBJ)
	gcc $(CFLAGS) $(SRCS_) $(INCLUDES) -I./includes -o $(NAME) $(SRCS_OBJ) $(MLX_FLAGS) 

$(MLX_LIB):
	@echo "Making MiniLibX..."
	@make -C $(MLX_DIR)

$(LIBFT_):
	@echo "Making Libft"
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(SRCS_OBJ)
	rm	$(NAME)

.PHONY: clean all
