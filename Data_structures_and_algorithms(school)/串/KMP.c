void GetNext(SqString t, int next[])
{
    int j, k;
    j = 0;
    k = -1;
    next[0] = -1;
    while (j < t.length - 1)
    {
        if (k == -1 || t.data[j] == t.data[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else
            k = next[k]; // k回退
    }
}

int KMPIndex(SqString s, SqString t)
{
    int next[MaxSize], i = 0, j = 0;
    GetNext(t, next);
    while (i < s.length && j < t.length)
    {
        if (j == -1 || s.data[i] == t.data[j])
        {
            i++;
            j++; // i、j各增1
        }
        else
            j = next[j]; // i不变，j后退   }
        if (j >= t.length)
            return (i - t.length);
        else
            return (-1); // 返回不匹配标志}
