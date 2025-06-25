#include <err.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

static void
print_elapsed_time(void)
{
  int secs, nsecs;
  static int first_call = 1;
  struct timespec curr;
  static struct timespec start;

  if (first_call)
  {
    first_call = 0;
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
      err(EXIT_FAILURE, "clock_gettime");
  }

  if (clock_gettime(CLOCK_MONOTONIC, &curr) == -1)
    err(EXIT_FAILURE, "clock_gettime");

  secs = curr.tv_sec - start.tv_sec;
  nsecs = curr.tv_nsec - start.tv_nsec;
  if (nsecs < 0)
  {
    secs--;
    nsecs += 1000000000;
  }
  printf("%d.%03d: ", secs, (nsecs + 500000) / 1000000);
}

int main(int argc, char *argv[])
{
  int fd;
  ssize_t s;
  uint64_t exp, tot_exp, max_exp;
  struct timespec now;
  struct itimerspec new_value;

  if (argc != 2 && argc != 4)
  {
    fprintf(stderr, "%s init-secs [interval-secs max-exp]\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  if (clock_gettime(CLOCK_REALTIME, &now) == -1)
    err(EXIT_FAILURE, "clock_gettime");

  /* Create a CLOCK_REALTIME absolute timer with initial
     expiration and interval as specified in command line. */

  new_value.it_value.tv_sec = now.tv_sec + atoi(argv[1]);
  new_value.it_value.tv_nsec = now.tv_nsec;
  if (argc == 2)
  {
    new_value.it_interval.tv_sec = 0;
    max_exp = 1;
  }
  else
  {
    new_value.it_interval.tv_sec = atoi(argv[2]);
    max_exp = atoi(argv[3]);
  }
  new_value.it_interval.tv_nsec = 0;

  fd = timerfd_create(CLOCK_REALTIME, 0);
  if (fd == -1)
    err(EXIT_FAILURE, "timerfd_create");

  if (timerfd_settime(fd, TFD_TIMER_ABSTIME, &new_value, NULL) == -1)
    err(EXIT_FAILURE, "timerfd_settime");

  print_elapsed_time();
  printf("timer started\n");

  for (tot_exp = 0; tot_exp < max_exp;)
  {
    s = read(fd, &exp, sizeof(uint64_t));
    if (s != sizeof(uint64_t))
      err(EXIT_FAILURE, "read");

    tot_exp += exp;
    print_elapsed_time();
    printf("read: %" PRIu64 "; total=%" PRIu64 "\n", exp, tot_exp);
  }

  exit(EXIT_SUCCESS);
}