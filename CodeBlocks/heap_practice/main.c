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

// �W��
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
// �U��
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
// �վ㬰 Heap
void Heap_init(int mode=0)
{
  if (mode==0 && heapMode==0) heapMode=MAXHEAP;
  else if(mode!=0) heapMode = mode;
  for (int i = heapSize/2; i >= 1; i--)
     HeapDown(i);
}
// ���J
int Heap_insert(int d, int mode=0)
{
  if (heapMode==0 || (heapMode!=mode && mode!=0)) Heap_init(mode);
  if (heapSize == Max) return 0;
  heap[++heapSize]=d;
  return HeapUp(heapSize);
}
// �R��
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
// �Ƨ� -- �洫
void swap(int *i, int *j) { int t=*i; *i = *j; *j = t; }
// �Ƨ�
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
// �H�����
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
// �D�{�� ===
int main()
{
  int A[] = { 15, 23, 10, 40, 30 };
  int B[] = { 20, 30, 10, 50, 60, 40, 45, 5 };
  int i, sizeA = sizeof(A)/sizeof(int), sizeB = sizeof(B)/sizeof(int);
  // -- �� A�}�C��Ƭ��G����, �վ㬰 MaxHeap
  for(i=0, heapSize=sizeA; i<sizeA; i++) heap[i+1]=A[i];
  ShowTree("\n\n(A.1) ��ܽվ�e �G����:");
  Heap_init();
  ShowTree("\n      ��ܽվ�� MaxHeap:");
  //    �A�վ㬰 MinHeap �ñƧ�
  //Heap_init(MINHEAP);
  Heap_sort(MINHEAP);
  ShowTree("\n      ���Sort�� MinHeap:");
  // -- �� B�}�C��Ƭ��G����, �վ㬰 MaxHeap
  for(i=0, heapSize=sizeB; i<sizeB; i++) heap[i+1]=B[i];
  ShowTree("\n\n(B.1) ��ܽվ�e �G����:");
  Heap_init(MAXHEAP);
  ShowTree("\n      ��ܽվ�� MaxHeap:");
  //    �A�R���ⵧ���
  Heap_delete(30);
  Heap_delete(60);
  ShowTree("\n\n(B.2) �R���F 30 60 �� MaxHeap:");
  // -- �� B�}�C��ƫإ� MinHeap
  for(i=0, heapSize=0; i<sizeB; i++)
      Heap_insert(B[i], MINHEAP);
  ShowTree("\n\n(B.3) �Ѹ�Ʃҫإߪ� MinHeap :");
  //    �A�R���ⵧ���
  Heap_delete(10);
  Heap_delete(30);
  ShowTree("\n\n(B.4) �R���F 10 30 �� MinHeap:");
  //    �A�W�[ 55 �ýվ㬰 MaxHeap
  Heap_insert(55, MAXHEAP);
  Heap_insert(35);
  ShowTree("\n\n(B.5) �վ㬰 MaxHeap �üW�[ 55 35:");
  Heap_sort();
  ShowTree("\n\n(B.6) �Ƨǫ᪺ MaxHeap:");
  system("pause");
  return 0;
}
