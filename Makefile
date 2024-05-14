NAME = fractol
SRCS_ = fractol.c
SRCS_OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall

UNAME =$(shell uname -s)
ifeq ($(shell uname -s), Linux)
	INCLUDES = -I/usr/include -Imlx\
			   -I ./includes/
else
	INCLUDES = -I/opt/X11/include -Imlx
endif
 
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname -s), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif
 
INCLUDES += ./includes/*.h
 
all: $(MLX_LIB) $(NAME)
 
.c.o:
	gcc $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
$(NAME): $(SRCS_OBJ)
	gcc $(CFLAGS) fractol.c $(INCLUDES) -o $(NAME) $(SRCS_OBJ) $(MLX_FLAGS)
 
$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	rm -f $(SRCS_OBJ)
	rm	$(NAME)

.PHONY: clean all
