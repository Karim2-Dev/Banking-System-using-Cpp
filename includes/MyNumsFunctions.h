#pragma once

namespace MyNumsFunctions
{
    void SwapNums(int *Num1, int *Num2)
    {
        int Temp = *Num1;
        *Num1 = *Num2;
        *Num2 = Temp;
    }
    int Sum(int Num1, int Num2)
    {
        return Num1 + Num2;
    }
}