#include <cs50.h>
#include <stdio.h>

string check(long number);
bool luhn(long number, long c);

int main(void)
{
    long n = get_long("Number: ");
    printf("%s", check(n));
}

string check(long number)
{
    long count = 0;
    long i = number;
    while (i != 0) 
    {
        i /= 10;
        ++count;
    }
    if (count == 15 && luhn(number, count))
    {
        long t = number / 10000000000000;
        if (t == 34 || t == 37)
        {
            return "AMEX\n";
        }
    } 
    else if (count == 16 && luhn(number, count)) 
    {
        long t = number / 100000000000000;
        if (t >= 51 && t <= 55)
        {
            return "MASTERCARD\n";
        } 
        else if (t >= 40 && t <= 49 && luhn(number, count))
        {
            return "VISA\n";
        }
    } 
    else if (count == 13 && luhn(number, count))
    {
        long t = number / 1000000000000;
        if (t == 4) 
        {
            return "VISA\n";
        }
    }
    return "INVALID\n";
}

bool luhn(long number, long c)
{
    bool check = false;
    int digit = 0;
    int uneven = 0;
    int even = 0;
    for (int i = 1; i <= c; i++) 
    {
        digit = number % 10;
        number = number / 10;

        if (i % 2 != 0) 
        {
            uneven += digit;
        } 
        else if (i % 2 == 0)
        {
            digit = digit * 2;
            if (digit > 9)
            {
                digit = digit % 10;
                digit += 1;
            }
            even += digit;
        }    
    }
    if ((even + uneven) % 10 == 0)
    {
        check = true;
    } 
    else
    {
        check = false;
    }
    return check;
}
