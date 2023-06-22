# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akatfi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 19:01:17 by akatfi            #+#    #+#              #
#    Updated: 2023/06/14 19:01:19 by akatfi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = mini_shell.o ft_splitline.o \
		ft_utils.o ft_utils2.o symbol.o input.o \
		commands.o here_doc.o quotes.o pipe.o\
		ft_itoa.o get_vars.o builtins.o builtins_utils.o minishell_utills1.o signals.o\
		t_command.o t_command_utils.o minishell_utills2.o  export.o export_utils.o minishell_utills.o linked_list.o\

NAME= minishell
CFLAGS= -Wall -Wextra -Werror
readline_flags = -I ~/Users/akatfi/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/akatfi/goinfre/homebrew/Cellar/readline/8.2.1/lib -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	cc $(readline_flags) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
