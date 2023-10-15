int size(const char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}

int strCompare(const char *str1, const char *str2)
{
    int size1 = size(str1);
    int size2 = size(str2);
    if (size1 != size2)
    {
        return 0;
    }
    for (int i = 0; i < size1; i++)
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}