#include <stdio.h>
#include <stdlib.h>

#include "deq.h"

static void test(int conditional, char *test_name)
{
  if (conditional) printf("TEST PASSED: %s\n", test_name);
  else printf("TEST FAILED: %s\n", test_name);
}

int main() {
  //New deque length test
  Deq d = deq_new();

  void* i1;
  void* i2;
  void* i3;
  void* i4;
  void* i5;

  test(deq_len(d) == 0, "New deque length is zero?");
  deq_head_put(d, i1); //insert one item at head
  test(deq_len(d) == 1, "Deque length 1 after inserting at head?");
  test(deq_head_ith(d, 0) == i1, "First item inserted at head accessible at head?");
  test(deq_tail_ith(d, 0) == i1, "First item inserted at head accessible at tail?");

  deq_del(d, 0);
  d = deq_new();

  deq_tail_put(d, i1); //insert one item at head
  test(deq_len(d) == 1, "Deque length 1 after inserting at tail?");
  test(deq_head_ith(d, 0) == i1, "First item inserted at tail accessible at head?");
  test(deq_tail_ith(d, 0) == i1, "First item inserted at tail accessible at tail?");

  deq_del(d, 0);
  d = deq_new();

  deq_head_put(d, i1);
  deq_head_put(d, i2);
  deq_head_put(d, i3);
  deq_head_put(d, i4);
  test(deq_len(d) == 4, "Deque length 4 after inserting 4 at head?");
  test(deq_head_ith(d, 0) == i4, "i4 in correct order from head after 4 head insert?");
  test(deq_head_ith(d, 1) == i3, "i3 in correct order from head after 4 head insert?");
  test(deq_head_ith(d, 2) == i2, "i2 in correct order from head after 4 head insert?");
  test(deq_head_ith(d, 3) == i1, "i1 in correct order from head after 4 head insert?");
  test(deq_tail_ith(d, 0) == i1, "i1 in correct order from tail after 4 head insert?");
  test(deq_tail_ith(d, 1) == i2, "i2 in correct order from tail after 4 head insert?");
  test(deq_tail_ith(d, 2) == i3, "i3 in correct order from tail after 4 head insert?");
  test(deq_tail_ith(d, 3) == i4, "i4 in correct order from tail after 4 head insert?");

  deq_del(d, 0);
  d = deq_new();

  deq_tail_put(d, i1);
  deq_tail_put(d, i2);
  deq_tail_put(d, i3);
  deq_tail_put(d, i4);
  test(deq_len(d) == 4, "Deque length 4 after inserting 4 at tail?");
  test(deq_head_ith(d, 0) == i1, "i1 in correct order from head after 4 tail insert?");
  test(deq_head_ith(d, 1) == i2, "i2 in correct order from head after 4 tail insert?");
  test(deq_head_ith(d, 2) == i3, "i3 in correct order from head after 4 tail insert?");
  test(deq_head_ith(d, 3) == i4, "i4 in correct order from head after 4 tail insert?");
  test(deq_tail_ith(d, 0) == i4, "i4 in correct order from tail after 4 tail insert?");
  test(deq_tail_ith(d, 1) == i3, "i3 in correct order from tail after 4 tail insert?");
  test(deq_tail_ith(d, 2) == i2, "i2 in correct order from tail after 4 tail insert?");
  test(deq_tail_ith(d, 3) == i1, "i1 in correct order from tail after 4 tail insert?");

  deq_del(d, 0);
  d = deq_new();

  deq_head_put(d, i2);
  deq_head_put(d, i1);
  deq_tail_put(d, i3);
  deq_tail_put(d, i4);
  test(deq_head_ith(d, 0) == i1, "i1 in correct order from head after mixed tail/head insert?");
  test(deq_head_ith(d, 1) == i2, "i2 in correct order from head after mixed tail/head insert?");
  test(deq_head_ith(d, 2) == i3, "i3 in correct order from head after mixed tail/head insert?");
  test(deq_head_ith(d, 3) == i4, "i4 in correct order from head after mixed tail/head insert?");

  test(deq_head_get(d) == i1, "i1 gotten from head after mixed tail/head insert?");
  test(deq_len(d) == 3, "Deque length is 3 after removing head from mixed tail/head insert?");
  test(deq_head_ith(d, 0) == i2, "Head is correctly i2 after removing head of mixed tail/head insert?");
  test(deq_tail_ith(d, 0) == i4, "Tail is correctly i4 after removing head of mixed tail/head insert?");
  test(deq_tail_get(d) == i4, "i4, gotten from tail after mixed tail/head insert?");
  test(deq_len(d) == 2, "Deque length is 2 after removing tail from mixed tail/head insert?");
  test(deq_head_get(d) == i2, "i2 gotten from head after mixed tail/head insert?");
  test(deq_len(d) == 1, "Deque length is 1 after removing head from mixed tail/head insert?");
  test(deq_head_ith(d, 0) == i3, "i3 correctly is head after it is last element in deque?");
  test(deq_tail_ith(d, 0) == i3, "i3 correctly is tail after it is last element in deque?");
  test(deq_tail_get(d) == i3, "i3, gotten from tail after mixed tail/head insert?");
  test(deq_len(d) == 0, "Deque length is 0 after removing tail from mixed tail/head insert?");

  deq_del(d, 0);
  d = deq_new();

  deq_head_put(d, i2);
  deq_head_put(d, i1);
  deq_tail_put(d, i3);
  deq_tail_put(d, i4);

  test(deq_head_rem(d, i3) == i3, "Remove method succesfully returned i3 after mixed head/tail insert?");

  test(deq_tail_ith(d, 0) == i4, "Tail correctly remains i4 after removing i3 from mixed head/tail insert?");
  test(deq_tail_ith(d, 1) == i2, "Tail i=1 element correctly i2 after removing i3 from mixed head/tail insert?");
  test(deq_tail_ith(d, 2) == i1, "Tail i=2 element correctly i1 after removing i3 from mixed head/tail insert?");
  test(deq_head_ith(d, 0) == i1, "Head correctly remains i1 after removing i3 from mixed head/tail insert?");
  test(deq_head_ith(d, 1) == i2, "Head i=1 correctly remains i2 after removing i3 from mixed head/tail insert?");
  test(deq_head_ith(d, 2) == i4, "Head i=2 correctly is i4 after removing i3 from mixed head/tail insert?");

  test(deq_tail_rem(d, i2) == i2, "Remove method succesfully returned i2 after mixed head/tail insert?");

  test(deq_tail_ith(d, 0) == i4, "Tail from tail correctly remains i4 after removing i2?");
  test(deq_tail_ith(d, 1) == i1, "Head from tail correctly remains i1 after removing i2?");
  test(deq_head_ith(d, 0) == i1, "Head from head correctly remains i1 after removing i2?");
  test(deq_head_ith(d, 1) == i4, "Tail from head correctly remains i4 after removing i2?");

  test(deq_head_rem(d, i4) == i4, "Remove method succesfully returned i4?");

  test(deq_head_ith(d, 0) == i1, "Head correctly i1 after removing i4?");
  test(deq_tail_ith(d, 0) == i1, "Tail correctly i1 after removing i4?");

  test(deq_head_rem(d, i2) == NULL, "Remove method successfully returned NULL on element not in deque?");
  test(deq_tail_rem(d, i1) == i1, "Remove method successfully returned i1?");
  
  test(deq_len(d) == 0, "Deque length correctly 0 after removing i1?");

  deq_del(d, 0);
  d = deq_new();

  deq_head_put(d, i1);
  deq_tail_put(d, i2);
}
