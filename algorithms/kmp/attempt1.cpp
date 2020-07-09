// 8 July 2020

#include <iostream>

const int MX = 100111;
const int MXP = 1000;
char str[MX], pat[MXP]; // match string, pattern
int N, P, nxt[MXP];     // size of str and pat

//void set_nxt()
//{   // WRONG WRONG WRONG, should be like failpointers
//    for (int cur=1, pre=0; cur<P; ++cur)
//    {
//        printf("cur %d pre %d ==? %d\n", cur, pre, pat[cur] == pat[pre]);
//        if (pat[cur] == pat[pre])
//            nxt[cur] = ++pre;   // FIX: ++pre not pre++ because we want to jump to the one after the match
//        else
//            pre = pat[cur] == pat[0];   // FIX: set to 1 if its equal to the beginning
//    }
//}

void set_nxt()
{
    memset(nxt, -1, sizeof nxt);
    for (int i=1; i<P; ++i)
    {
        printf("i = %d\n", i);
        int j=nxt[i-1];
        do {
            printf("    j = %d\n", j);
            if (pat[j+1] == pat[i])
            {
                nxt[i] = j+1;
                break;
            }
            j = nxt[j];
        } while (j >= 0);
        //for (; ; j=nxt[j])
        //{
        //    printf("    j = %d\n", j);
        //    if (pat[j+1] == pat[i])
        //    {
        //        nxt[i] = j+1;
        //        break;
        //    }
        //}
    }
}
int panic = -1;
int count()
{
    int tot=0, j=0;
    for (int i=0; i<N; ++i)
    {
        if (!--panic) break;
        printf("i %d j %d\n", i, j);
        if (pat[j] == str[i])
            ++j;
        else
        {
            j = nxt[j-1] +1;
            //j = nxt[j] +1; --i;
            panic = 10;
            printf("messed up! now i=%d j=%d\n", i, j);
        }
        if (j == P) ++tot, j=nxt[j-1]+1;    // FIX: logic--check correct after checking last in pattern
    }
    return tot;
}

int main()
{
    int cs; scanf("%d", &cs);
    while (cs--)
    {
        scanf("%s%s", pat, str);
        P = strlen(pat);
        N = strlen(str);
        set_nxt();
        for (int i=0; i<P; ++i)
            printf("%d ", nxt[i]);
        printf("\n");
        printf("%d\n", count());
    }
}

