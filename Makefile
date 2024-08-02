CC= cc
Flags= 

SRC= ./external_functions/ft_free.c ./external_functions/ft_split.c ./parsing/ft_parsing.c ./parsing/divide_cmd.c parsing/ft_syntax.c parsing/heredoc_expand.c ./external_functions/ft_strchr.c \
	./external_functions/ft_lst_add_back.c ./external_functions/ft_lstnew.c ./parsing/ft_split_cmd.c ./parsing/ft_addspace.c \
	./external_functions/ft_free2.c ./parsing/ft_split_cmd_utils.c minishell.c execution/signals.c execution/execution.c execution/redirection.c execution/pipex/pipex.c \
	./execution/builtins/execute_bin.c ./execution/builtins/change_dir.c ./execution/builtins/echo.c ./execution/builtins/env.c \
	./execution/builtins/exit.c ./execution/builtins/export.c ./execution/builtins/unset.c ./execution/builtins/built_ins_utils.c ./external_functions/ft_split_v2.c ./external_functions/ft_strdup.c ./external_functions/ft_atoi.c \
	./external_functions/ft_strncmp.c ./external_functions/ft_strlen.c ./external_functions/ft_strjoin.c ./external_functions/ft_memcpy.c ./external_functions/ft_memmove.c ./external_functions/ft_strlcat.c ./external_functions/ft_strlcpy.c \
	init.c execution/builtins/cd_utils2.c ./execution/builtins/execute_bin_utils_1.c ./execution/redirection_tools.c ./execution/execution_utils_3.c \
	./execution/pipex/pipex_utils.c ./execution/builtins/cd_utils1.c ./execution/builtins/env_utils.c ./gnl/get_next_line.c ./gnl/get_next_line_utils.c \
	./execution/builtins/built_ins_utils2.c ./parsing/ft_tolower.c ./parsing/ft_strrchr.c ./parsing/ft_itoa.c parsing/expand.c \
	parsing/ft_splitcmdutils2.c ./external_functions/ft_strcpy.c ./external_functions/ft_putstr_fd.c ./external_functions/ft_putchar_fd.c ./external_functions/ft_putendl_fd.c ./external_functions/ft_malloc.c ./external_functions/ft_bzero.c \
	./external_functions/ft_isalpha.c ./external_functions/ft_isdigit.c ./external_functions/ft_substr.c ./external_functions/ft_strtrim.c ./execution/execution_utils.c ./execution/execution_utils_2.c \
	./execution/signals_utils.c  ./execution/builtins/export_utils.c ./execution/builtins/errors.c ./execution/builtins/execute_bin_utils.c init_utils.c parsing/expand_utils.c parsing/delimiter_utils.c

O_SRC=$(SRC:.c=.o)

NAME= minishell
READLINE= $(shell brew --prefix readline)

%.o: %.c
	$(CC) $(Flags) -c -g $< -o $@ -I $(READLINE)/include

all: $(NAME)

$(NAME): $(O_SRC)
	$(CC) $(Flags) -g -lreadline -L $(READLINE)/lib $(O_SRC) -o $(NAME)


clean:
	rm -f $(O_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all clean