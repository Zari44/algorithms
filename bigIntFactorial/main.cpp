#include <bits/stdc++.h>

using namespace std;

class BigInteger
{
    public:
    BigInteger(int value) {digits.push_front(value);}
    void print() {
        for (deque<int>::iterator digit = digits.begin(); digit != digits.end(); ++digit)
            cout << *digit;// << " ";
        // cout << endl;
    }
    BigInteger &operator=(const BigInteger &rhs)
    {
        if (this == &rhs)
            return *this;
        digits = rhs.digits;
        return *this;
    }
    BigInteger& operator * (const int& rhs)
    {
        convertIntToDigits(rhs);
        tableMultiply();
        makeTablesEqualSize();
        tableAdd();
        delete multiply_table;
        return *this;
    }
    private:
    deque<int> digits;
    deque<int> int_digits;
    vector<deque<int>>* multiply_table;
    int longest_number;

    void convertIntToDigits(int value)
    {
        int_digits.clear();
        while (value > 0)
        {
            int_digits.push_front(value % 10);
            value = value / 10;
        }
    }

    void tableMultiply()
    {
        longest_number = 0;
        multiply_table = new vector<deque<int>>(int_digits.size());

        for (int i = 0; i < int_digits.size(); ++i)
        {
            for (int z = 0; z < i; ++z)
                (multiply_table->at(i)).push_front(0);

            int rest = 0;
            for (int j = 0; j < digits.size(); ++j)
            {
                int result = int_digits[int_digits.size()-1-i] * digits[digits.size()-1-j];
                result += rest;

                rest = result / 10;
                result = result % 10;

                // cout << int_digits[int_digits.size()-1-i] << " * " << digits[digits.size()-1-j];
                // cout << " = rest: " << rest << " result: " << result << endl;
                (multiply_table->at(i)).push_front(result);
            }
            if (rest > 0)
                (multiply_table->at(i)).push_front(rest);

            if (multiply_table->at(i).size() > longest_number)
                longest_number = multiply_table->at(i).size();
        }
        // cout << "longest number " << longest_number << endl;
    }

    void tableAdd()
    {
        digits.clear();
        int rest = 0;
        for (int j = longest_number - 1; j >= 0; --j)
        {
            int digit = 0;
            for (int i = 0; i < multiply_table->size(); ++i)
            {
                // cout << "Multiply table: " << (multiply_table->at(i)).at(j) << endl;
                digit += (multiply_table->at(i)).at(j);
            }
            digit += rest;

            rest = digit / 10;
            digit = digit % 10;

            digits.push_front(digit);
        }
        if (rest > 0)
            digits.push_front(rest);
    }

    void makeTablesEqualSize()
    {
        for (int i = 0; i < multiply_table->size(); ++i)
            while((multiply_table->at(i)).size() < longest_number)
                multiply_table->at(i).push_front(0);
    }


};

// Complete the extraLongFactorials function below.
void extraLongFactorials(int n) {
    BigInteger bint(1);
    for (int i = 1; i <= n; ++i)
    {
        // cout << " ------ " << endl;
        bint = bint * i;

    }
    bint.print();
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    extraLongFactorials(n);

    return 0;
}
