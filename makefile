##
## ATOS PROJECT 2022
## MAKEFILE
## File description:
## Wow, such make, much file!
##

SRC =	src/job_submit_node_limit.c\

CFLAGS = -DHAVE_CONFIG_H -Wall -Wextra -Wpedantic -g -O2 -pthread -fno-gcse -g -O0 -fno-strict-aliasing -MT job_submit_mine.lo -MD -MP -MF .deps/job_submit_node_limit.Tpo -fPIC -DPIC

LDFLAGS = -lslurm

OBJ =	$(SRC:.c=.o)

NAME =	job_submit_node_limit

$(NAME):
		gcc -I ./include -I ~/SLURM/slurm.build -o $(OBJ) -c $(SRC) $(CFLAGS)
		mv src/*.o ./.libs/
		mv -f .deps/job_submit_node_limit.Tpo .deps/job_submit_node_limit.Plo
		rm -fr .libs/job_submit_node_limit.a .libs/job_submit_node_limit.la .libs/job_submit_node_limit.lai job_submit_node_limit.so
		gcc -shared .libs/job_submit_node_limit.o -O2 -pthread -O0 -pthread -Wl,-soname -Wl,job_submit_node_limit.so -o job_submit_node_limit.so

all:	$(NAME)

clean:
		@rm -f $(OBJ)
		@rm -f job_submit_node_limit.so

fclean:	clean
		@rm -f $(NAME)

re:		clean   all
