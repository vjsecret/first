#include <stdio.h>
#include <stdlib.h>

#define  Comp(A,B) ((heapMode==MINHEAP)?(A<B):(A>B))
const int Max = 32;
const int MAXHEAP = 2;
const int MINHEAP = 1;
#define int heap[Max+1];
#define int heapSize=0;
int heapMode = 0;
#define void Heap_init(int);

// 上升
int HeapUp(int i, int mode=0)
{
  if (heapMode==0 || (heapMode!=mode && mode!=0)) Heap_init(mode);
  int y = heap[i];
  for (int c=i/2; c>0 && Comp(y,heap[c]); c/=2)
  {
    heap[i] = heap[c];
    i = c;
  }
  heap[i] = y;
  return i;
}
// 下降
int HeapDown(int i, int mode=0)
{
  if (heapMode==0 || (heapMode!=mode && mode!=0)) Heap_init(mode);
  int y = heap[i];
  for (int c = 2*i; c <= heapSize; c*=2)
  {
    if (c < heapSize && Comp(heap[c+1],heap[c])) c++;
    if (Comp(y,heap[c])) break;
    heap[i] = heap[c];
    i = c;
  }
  heap[i] = y;
  return i;
}
// 調整為 Heap
void Heap_init(int mode=0)
{
  if (mode==0 && heapMode==0) heapMode=MAXHEAP;
  else if(mode!=0) heapMode = mode;
  for (int i = heapSize/2; i >= 1; i--)
     HeapDown(i);
}
// 插入
int Heap_insert(int d, int mode=0)
{
  if (heapMode==0 || (heapMode!=mode && mode!=0)) Heap_init(mode);
  if (heapSize == Max) return 0;
  heap[++heapSize]=d;
  return HeapUp(heapSize);
}
// 刪除
int Heap_delete(int d, int mode=0)
{
  if (heapMode==0 || (heapMode!=mode && mode!=0)) Heap_init(mode);
  for(int i=1; i<=heapSize; i++)
     if ( heap[i]==d )
     {
        heap[i] = heap[heapSize--];
        if (i==HeapUp(i)) HeapDown(i);
        return i;
     }
  return -1;
}
// 排序 -- 交換
void swap(int *i, int *j) { int t=*i; *i = *j; *j = t; }
// 排序
void Heap_sort(int mode=0)
{
   if (heapMode==0 || (heapMode!=mode && mode!=0)) Heap_init(mode);
   int size = heapSize;
   while (heapSize>1)
   {
      swap(&heap[1], &heap[heapSize--]);
      HeapDown(1);
   }
   for(int k=size; heapSize<k; k--)
      swap(&heap[heapSize++], &heap[k]);
   heapSize = size;
}
// 以樹狀顯示
void ShowTree(char *t)
{
  int p=1;
  while(p<=heapSize) p*=2;
  printf( "%s\n%*s", t, --p, "");
  for(int i=1, n=1; i<=heapSize; i++, n=p*2-1)
  {
    printf( "%3d%*s", heap[i], n, "");
    if (!(i&(i+1))) printf ("\n%*s", p=(p-1)/2, "");
  }
  printf ("\n");
}
// 主程式 ===
int main()
{
  int A[] = { 15, 23, 10, 40, 30 };
  int B[] = { 20, 30, 10, 50, 60, 40, 45, 5 };
  int i, sizeA = sizeof(A)/sizeof(int), sizeB = sizeof(B)/sizeof(int);
  // -- 由 A陣列資料為二元樹, 調整為 MaxHeap
  for(i=0, heapSize=sizeA; i<sizeA; i++) heap[i+1]=A[i];
  ShowTree("\n\n(A.1) 顯示調整前 二元樹:");
  Heap_init();
  ShowTree("\n      顯示調整後 MaxHeap:");
  //    再調整為 MinHeap 並排序
  //Heap_init(MINHEAP);
  Heap_sort(MINHEAP);
  ShowTree("\n      顯示Sort後 MinHeap:");
  // -- 由 B陣列資料為二元樹, 調整為 MaxHeap
  for(i=0, heapSize=sizeB; i<sizeB; i++) heap[i+1]=B[i];
  ShowTree("\n\n(B.1) 顯示調整前 二元樹:");
  Heap_init(MAXHEAP);
  ShowTree("\n      顯示調整後 MaxHeap:");
  //    再刪除兩筆資料
  Heap_delete(30);
  Heap_delete(60);
  ShowTree("\n\n(B.2) 刪除了 30 60 後 MaxHeap:");
  // -- 由 B陣列資料建立 MinHeap
  for(i=0, heapSize=0; i<sizeB; i++)
      Heap_insert(B[i], MINHEAP);
  ShowTree("\n\n(B.3) 由資料所建立的 MinHeap :");
  //    再刪除兩筆資料
  Heap_delete(10);
  Heap_delete(30);
  ShowTree("\n\n(B.4) 刪除了 10 30 後 MinHeap:");
  //    再增加 55 並調整為 MaxHeap
  Heap_insert(55, MAXHEAP);
  Heap_insert(35);
  ShowTree("\n\n(B.5) 調整為 MaxHeap 並增加 55 35:");
  Heap_sort();
  ShowTree("\n\n(B.6) 排序後的 MaxHeap:");
  system("pause");
  return 0;
}
