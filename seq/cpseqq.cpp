#include <vector>
#include <algorithm>
#include <cstdio>
using std::vector;
#define SIZ (1<<20)
 
int power (int i) {
    int p = 1;
    while (p < i) p <<= 1;
    return p<<3;
}
char v2[SIZ*8], v3[SIZ];
 
 
int main() {
     
    int temp, te;
    v2[0] = 0;
     
    int p, t, k, i, vs, size = 1;
     
    scanf("%d", &p);
     
    while (p--) {
        scanf("%d", &t);
        vs = 0;
        while (t--) {
            scanf("%d", &i);
            v3[vs++] = i;
        }
         
        temp = power(vs);
        if (size < temp) {
            te = 1;
            while (size > te) te <<= 1;
            for (k = size - te>>1; k < te; k++)
                v2[size+k] = v2[k] ^ 1;
            for (; k < temp; k<<=1) {
                for (i = k; i < (k<<1); i++)
                    v2[i] = v2[i-k] ^ 1;
            }
        }
         
        if (v3[0] == 1) {
            printf("1 ");
            t = 1;
        }
        else {
            printf("0 ");
            t = 0;
        }
         
        if (vs == 1) {
            putchar('\n');
            continue;
        }
         
        i = 1;
         
         
        while (i < vs) {
            k = power(i+1) - i;
            while (t < k) {
                for (temp = 0; temp < i+1; temp++) {
                    if (v3[temp] != v2[temp+t]) break;
                    if (temp == i) {
                        printf("%d ", t);
                        i++;
                        if (i >= vs) break;
                        k = power(i+1) - i;
                    }
                }
                if (i >= vs) break;
                t++;
            }
             
            if (t >= k) {
                while (i < vs) {
                    printf("-1 ");
                    i++;
                }
                break;
            }
            i++;
        }
        putchar('\n');
    }
     
    return 0;
}
