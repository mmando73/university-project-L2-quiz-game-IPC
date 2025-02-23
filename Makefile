CC = gcc
CFLAGS = -Wall -I./include
LDLIBS = -lncursesw
SRCDIR = src
EXTERNALDIR = externals

# Noms des exécutables
QUIZ = quiz
SUCCESS = success
FAILURE = failure

# Fichiers source et objet
SRCS = $(SRCDIR)/main.c $(SRCDIR)/questions.c $(SRCDIR)/game.c $(SRCDIR)/ipc.c $(SRCDIR)/options.c $(SRCDIR)/ui.c
OBJS = $(SRCS:.c=.o)


all: $(QUIZ) $(SUCCESS) $(FAILURE)

$(QUIZ): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(SUCCESS):
	$(CC) $(CFLAGS) -o $@ $(EXTERNALDIR)/success.c $(LDLIBS)

$(FAILURE):
	$(CC) $(CFLAGS) -o $@ $(EXTERNALDIR)/failure.c $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(QUIZ) $(SUCCESS) $(FAILURE)

.PHONY: all clean
