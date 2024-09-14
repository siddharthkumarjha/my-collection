#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

// A long enough bar to account for dynamic widths
static char bar[] = "======================================="
                    "======================================";

int main() {
  struct winsize w;
  int progress = 0; // Progress index for the loading bar
  int bar_width;    // The dynamic width of the loading bar

  // Main loading bar loop
  while (progress <= 100) {
    // Get the current terminal width
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // Calculate loading bar width based on terminal size (e.g., 70% of terminal
    // width)
    bar_width = w.ws_col * 70 / 100;

    // Make sure the bar_width is not greater than the size of the bar array
    if (bar_width > sizeof(bar) - 1) {
      bar_width = sizeof(bar) - 1;
    }

    // Print the loading bar with dynamic size
    const int width = progress * bar_width / 100;
    printf("[%-*.*s>%-*s] %d%% : Terminal width %d\r", width, width, bar,
           bar_width - width - 1, "", progress, w.ws_col);
    fflush(stdout);

    // Sleep for 100 ms
    usleep(100000);

    // Increment the progress (simulate loading)
    progress++;
  }

  // Print a newline after completion
  printf("\n");

  return 0;
}
