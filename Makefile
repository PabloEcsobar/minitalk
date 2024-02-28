# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 17:12:08 by blackrider        #+#    #+#              #
#    Updated: 2024/02/28 18:41:24 by blackrider       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENTSERVER = 0

N_SERVER = server
N_CLIENT = client

SRCSERVER = server.c utils.c
SRCCLIENT = client.c utils.c

SERVEROBJDIR = serverobjs
CLIENTOBJDIR = clientobjs
SERVEROBJS = $(patsubst %.c, $(SERVEROBJDIR)/%.o, $(SRCSERVER))
CLIENTOBJS = $(patsubst %.c, $(CLIENTOBJDIR)/%.o, $(SRCCLIENT))

FTPRINTFDIR = ft_printf
FTPRINTF = ftprintffull

CC = gcc
CFLAGS = -Wall -Wextra
CFLAGSO = -c -Wall -Wextra

.PHONY: all, re, fclean, clean, bonus

all: $(CLIENTSERVER)

bonus: $(CLIENTSERVER)

srv: $(N_SERVER)

clnt: $(N_CLIENT)

clean:
	rm -rf $(SERVEROBJDIR) $(CLIENTOBJDIR)
	$(MAKE) -C $(FTPRINTFDIR) clean

fclean: clean
	rm -f $(N_CLIENT) $(N_SERVER)
	$(MAKE) -C $(FTPRINTFDIR) fclean

re: fclean all

$(CLIENTSERVER): $(N_SERVER) $(N_CLIENT)

$(N_SERVER): $(SERVEROBJS)
	$(MAKE) -C $(FTPRINTFDIR) bonus
	$(CC) $(CFLAGS) $(SERVEROBJS) -L$(FTPRINTFDIR) -l$(FTPRINTF) -o $@

$(N_CLIENT): $(CLIENTOBJS)
	$(MAKE) -C $(FTPRINTFDIR) bonus
	$(CC) $(CFLAGS) $(CLIENTOBJS) -L$(FTPRINTFDIR) -l$(FTPRINTF) -o $@

$(CLIENTOBJDIR)/%.o: %.c 
	@mkdir -p $(CLIENTOBJDIR)
	$(CC) $(CFLAGSO) $< -o $@

$(SERVEROBJDIR)/%.o: %.c 
	@mkdir -p $(SERVEROBJDIR)
	$(CC) $(CFLAGSO) $< -o $@

$(FTPRINTF):
	$(MAKE) -C $(FTPRINTFDIR) bonus

