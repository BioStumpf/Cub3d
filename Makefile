# Colors
RESET  = \033[0m
BOLD   = \033[1m
GREEN  = \033[32m
BLUE   = \033[34m

NAME := cub3D
CC := cc

DEP_DIR := dep/
OBJ_DIR := obj/
LIBFT_DIR := libft/
SRCS_DIR := src/
HEADER_DIR := headers/

SRCS = main.c dummy_map_generator.c
SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
OBJS := $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
DEPS := $(patsubst $(SRCS_DIR)%.c, $(DEP_DIR)%.d, $(SRCS))
LIBFT := $(addprefix $(LIBFT_DIR), libft.a)

CFLAGS_OBJS = -Wall -Wextra -Werror -g -c $< -o $@ -I$(LIBFT_DIR) -I$(HEADER_DIR)
CFLAGS_NAME = -Wall -Wextra -Werror -g -o $@ $(OBJS) $(LIBFT) -lm -lXext -lX11 -lmlx
DEP_FLAGS = -MMD -MP -MT $@ -MF $(DEP_DIR)$*.d

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	@printf "\n"
	@printf "$(GREEN)==$(BOLD)$(BLUE)Executable$(GREEN)==$(RESET)\n"
	$(CC) $(CFLAGS_NAME)

$(LIBFT): FORCE
	@printf "$(GREEN)==$(BOLD)$(BLUE)Libft/Objs$(GREEN)==$(RESET)\n"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR)

FORCE:
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       Compile Project          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"

norm:
	./norm.sh

test:
	@cc tests/base_test.c -Ilibft -Llibft -lft -lcriterion -o test
	@./test
	rm -rf test

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)$*.d)
	$(CC) $(CFLAGS_OBJS) $(DEP_FLAGS)

$(DEP_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

localclean:
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       LOCAL CLEANING          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"
	rm -rf $(OBJ_DIR)
	rm -rf $(DEP_DIR)
	@printf "\n"

clean: localclean
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       CLEANING          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) clean
	@printf "\n"

fclean: localclean
	@printf "$(GREEN)======================================$(RESET)\n"
	@printf "$(BOLD)$(BLUE)       FULL CLEANING          $(RESET)\n"
	@printf "$(GREEN)======================================$(RESET)\n"
	rm -rf $(NAME)
	$(MAKE) --no-print-directory -sC $(LIBFT_DIR) fclean
	@printf "\n"

#re: fclean all
re:
	$(MAKE) fclean
	$(MAKE) all

-include $(DEPS)

.PHONY: all clean fclean re FORCE test
