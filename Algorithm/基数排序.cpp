#include<stdio.h>
#define MAX 20
//#define SHOWPASS
#define BASE 10

void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d\t", a[i]);
  }
}

void radixsort(int *a, int n) {
  int i, b[MAX], m = a[0], exp = 1;

  for (i = 1; i < n; i++) {
    if (a[i] > m) {
      m = a[i];
    }
  }

  while (m / exp > 0) {
    int bucket[BASE] = { 0 };

    for (i = 0; i < n; i++) {
	//取第i位数
      bucket[(a[i] / exp) % BASE]++;
    }

    for (i = 1; i < BASE; i++) {
	//在该位上,数字比i小的有几个
      bucket[i] += bucket[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
	//在这一位上的又几个比其小,它就排第几-1(自己)
	//由于是从低位到高位,在高位时的排序可以覆盖原来的排序
      b[--bucket[(a[i] / exp) % BASE]] = a[i];
    }

    for (i = 0; i < n; i++) {
      a[i] = b[i];
    }

    exp *= BASE;

#ifdef SHOWPASS
    printf("\nPASS   : ");
    print(a, n);
#endif
  }
}

int main() {
  int arr[MAX];
  int i, n;

  printf("Enter total elements (n <= %d) : ", MAX);
  scanf("%d", &n);
  n = n < MAX ? n : MAX;

  printf("Enter %d Elements : ", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  printf("\nARRAY  : ");
  print(&arr[0], n);

  radixsort(&arr[0], n);

  printf("\nSORTED : ");
  print(&arr[0], n);
  printf("\n");

  return 0;
}