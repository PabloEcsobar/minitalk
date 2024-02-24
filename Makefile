# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 17:12:08 by blackrider        #+#    #+#              #
#    Updated: 2024/02/24 13:17:44 by blackrider       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

N_SERVER = server
N_CLIENT = client

SRCSERVER = server.c utils.c
SRCCLIENT = client.c utils.c

SERVEROBJDIR = serverobjs
CLIENTOBJDIR = clientobjs
SERVEROBJS = $(patsubst %.c, $(SERVEROBJDIR)/%.o, $(SRCSERVER))
CLIENTOBJS = $(patsubst %.c, $(CLIENTOBJDIR)/%.o, $(SRCCLIENT))

# CLIENTOBJS = $(SRCCLIENT:%.c=$(CLIENTOBJDIR)/%.o)
# SERVEROBJS = $(SRCSERVER:%.c=$(SERVEROBJDIR)/%.o)

FTPRINTFDIR = ft_printf
FTPRINTF = ftprintf

CC = gcc
CFLAGS = -Wall -Wextra
CFLAGSO = -c -Wall -Wextra

.PHONY: all, re, fclean, clean

all: $(N_SERVER) $(N_CLIENT)

srv: $(N_SERVER)

clnt: $(N_CLIENT)

$(N_SERVER): $(SERVEROBJS) $(FTPRINTF)
	$(CC) $(CFLAGS) $(SERVEROBJS) -L$(FTPRINTFDIR) -l$(FTPRINTF) -o $@

$(N_CLIENT): $(CLIENTOBJS) $(FTPRINTF)
	$(CC) $(CFLAGS) $(CLIENTOBJS) -L$(FTPRINTFDIR) -l$(FTPRINTF) -o $@

$(CLIENTOBJDIR)/%.o: %.c 
	@mkdir -p $(CLIENTOBJDIR)
	$(CC) $(CFLAGSO) $< -o $@

$(SERVEROBJDIR)/%.o: %.c 
	@mkdir -p $(SERVEROBJDIR)
	$(CC) $(CFLAGSO) $< -o $@

$(FTPRINTF):
	$(MAKE) -C $(FTPRINTFDIR) bonus

clean:
	rm -rf $(SERVEROBJDIR) $(CLIENTOBJDIR)
	$(MAKE) -C $(FTPRINTFDIR) clean

fclean: clean
	rm -f $(N_CLIENT) $(N_SERVER)
	$(MAKE) -C $(FTPRINTFDIR) fclean

re: fclean all
