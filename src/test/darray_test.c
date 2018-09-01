#include "darray.h"
#include <stdio.h>



int main() {

  const size_t num_test_vals = 10;
  DArray *d = darray_init();

  int **d_arr = malloc(num_test_vals * sizeof(int*));

  for(size_t ii = 0; ii < num_test_vals; ii++) {
    d_arr[ii] = malloc(sizeof(int));
    *d_arr[ii] = ii * ii;
    darray_set(d, d_arr[ii], 2 * ii);
  }

  void *tmp = NULL;

  while((tmp = darray_iterate(d,tmp))) {
    int *n = (int*) tmp;
    printf("%d\n",*n);
  }

  free(d_arr);
  darray_destroy(d, NULL);

  return 0;
}
