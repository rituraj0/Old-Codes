void mergesort(Item a[], int start, int stop)
{
int i, m;
for (m = 1; m < stop – start; m += m)
for (i = start; i < stop; i += m + m)
{
int from = i;
int mid = i + m – 1;
int to = min(i + m + m – 1, stop);
merge(a, from, mid, to);
}
}
