#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    const size_t SCREEN_WIDTH = 80;
//    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers(number_count);
    cerr << "Enter numbers: ";
    for (int i = 0; i < number_count; i++)
    {
        cin >> numbers[i];
    }

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    vector<size_t> bins(bin_count);

    cerr << "Enter column labels: ";
    vector<string> labels(bin_count);

    string dummy;
    getline(cin, dummy);

    size_t max_label_length = 0;
    for (size_t i = 0; i < bin_count; i++)
    {
        getline(cin, labels[i]);
        if (labels[i].length() > max_label_length)
        {
            max_label_length = labels[i].length();
        }
    }

    double min = numbers[0];
    double max = numbers[0];
    for (double x : numbers)
    {
        if (x < min)
        {
            min = x;
        }
        else if (x > max)
        {
            max = x;
        }
    }

    double bin_size = (max - min) / bin_count;

    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }

    size_t max_count = bins[0];
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }

    for (size_t i = 0; i < bin_count; i++)
    {
        size_t spaces_to_print = max_label_length - labels[i].length();
        size_t MAX_ASTERISK = SCREEN_WIDTH - max_label_length - 1;
        for (size_t j = 0; j < spaces_to_print; j++)
        {
            cout << " ";
        }
        cout << labels[i] << "|";
        size_t count = bins[i];
        size_t height = count;
        if (max_count > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(count) / max_count);
        }

        for (size_t j = 0; j < height; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
}
