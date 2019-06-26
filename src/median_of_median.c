#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}

int quick_select(int A[], int n, int k){
    int i, j, l, pivot, medians[(n+4)/5];

  if(n <= 5) {
      i = 0;
      while(++i<n) {
	  if(A[i] < A[i-1]) {
	      j = i;
	      while(--j >= 0 && A[j] > A[j+1]) swap(A+j, A+j+1);
	  }
      }
      return A[k];
  }
  
  for(i=0; i<(n/5); i++) medians[i] = quick_select(A+i*5, 5, 2);
  if(i*5 < n) medians[i] = quick_select(A+i*5, n%5, n%5/2);
  pivot = quick_select(medians, (n+4)/5, (n+4)/10);

  for(i=j=l=0; i<n; i++){
    if(A[i] <= pivot){
      swap(A+i, A+j);
      if(A[i] == pivot) {
	  swap(A+l, A+j);
	  l++;
      }
      j++;
    }
  }

  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else if(j-l-1 < k) return pivot;
  else return quick_select(A+l, j-l, k);
}


int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
