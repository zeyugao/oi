
void getRange(int *arr, int size, int *max, int *min)
{
  int *p = arr, *endp = arr + size;
  if (size % 2 != 0)
  {
    *max = *min = *p++;
  }
  else
  {
    if (*p > *(p + 1))
    {
      *max = *p;
      *min = *(p + 1);
    }
    else
    {
      *max = *(p + 1);
      *min = *p;
    }
    p += 2;
  }
  while (p != endp)
  {
    if (*p > *(p + 1))
    {
      if (*p > *max) *max = *p;
      if (*(p + 1) < *min) *min = *(p + 1);
    }
    else
    {
      if (*(p + 1) > *max) *max = *(p + 1);
      if (*(p) < *min) *min = *p;
    }
    p += 2;
  }
}