#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
static const int MAX_LEN = 1000;
 
char a[MAX_LEN+2], b[MAX_LEN+2];
int aLen, bLen;
 
void readStrings() {
   scanf("%s %s", a, b);
   aLen = strlen(a);
   bLen = strlen(b);
  
 int i;
  for(i=aLen;i>0;i--)
    a[i]=a[i-1];

  for(i=bLen;i>0;i--)
    b[i]=b[i-1];
}
 
void dld() {
   int INF = aLen + bLen;
   int H[aLen+2][bLen+2];
   H[0][0] = INF;
   for (int i = 0; i <= aLen; ++i) {
      H[i+1][1] = i;
      H[i+1][0] = INF;
   }
   for (int j = 0; j <= bLen; ++j) {
      H[1][j+1] = j;
      H[0][j+1] = INF;
   }
   int C = 'z'+1;

   int DA[C];

   for (int d = 0; d < C; ++d) 
       DA[d] = 0;

   for (int i = 1; i <= aLen; ++i) {
      int DB = 0;
      for (int j = 1; j <= bLen; ++j) {
         int i1 = DA[b[j-1]];
         int j1 = DB;
         int d = ((a[i-1] == b[j-1]) ? 0 : 1);
         if (d == 0) DB = j;
         H[i+1][j+1] = min(H[i][j]+d, H[i+1][j]+1);
         H[i+1][j+1] = min(H[i+1][j+1], H[i][j+1]+1);
         H[i+1][j+1] = min(H[i+1][j+1], H[i1][j1] + (i-i1-1) + 1 + (j-j1-1));
      }
      DA[a[i-1]] = i;
   }
   printf("%d\n", H[aLen+1][bLen+1]);
}
 
int main() {
   for (; ;) {
     
    readStrings();
   
     if (a[0]=='*')
      break;
      dld();
   }
}
