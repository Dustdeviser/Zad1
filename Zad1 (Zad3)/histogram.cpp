#pragma once
#include "histogram.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

vector<double> input_numbers(size_t number_count)
{
    cerr << "Enter numbers: ";
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++)
    {
        cin >> numbers[i];
    }
    return numbers;
}

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
if (numbers.empty()) {
        return;
    }
    min = numbers[0];
    max = numbers[0];
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
}

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    vector<size_t> bins(bin_count, 0);
    if (numbers.empty() || bin_count == 0) return bins;
    double min = 0;
    double max = 0;
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++)
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
    return bins;
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_rect(double x, double y, double width, double height,
              string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y
         << "' width='" << width << "' height='" << height
         << "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}


void svg_line(double x1, double y1, double x2, double y2,
              string stroke = "grey", string stroke_dasharray = "")
{
    cout << "<line x1='" << x1 << "' y1='" << y1
         << "' x2='" << x2 << "' y2='" << y2
         << "' stroke='" << stroke << "'";
    if (!stroke_dasharray.empty()) {
        cout << " stroke-dasharray='" << stroke_dasharray << "'";
    }

    cout << " />\n";
}

void show_histogram_svg(const vector<size_t>& bins)
{
    size_t bin_count = bins.size();
    if (bin_count == 0) return;

    cerr << "Enter column labels: ";
    vector<string> labels(bin_count);
    for (size_t i = 0; i < bin_count; i++)
    {
        cin >> labels[i];
    }

    cerr << "Enter dash length and space length: ";
    size_t dash_length, space_length;
    cin >> dash_length >> space_length;

    string stroke_dasharray = to_string(dash_length) + " " + to_string(space_length);

    size_t max_count = bins[0];
    for (size_t count : bins)
    {
        if (count > max_count) {
            max_count = count;
        }
    }

    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_HEIGHT = bin_count * 40;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 25;
    const auto TEXT_WIDTH = 120;
    const auto BIN_HEIGHT = 24;
    const auto MAX_BAR_WIDTH = IMAGE_WIDTH - TEXT_WIDTH - 20;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    for (size_t i = 0; i < bin_count; i++)
    {
        double bin_width = 0;
        if (max_count > 0)
        {
            bin_width = MAX_BAR_WIDTH * (static_cast<double>(bins[i]) / max_count);
        }

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, labels[i]);
        svg_rect(TEXT_WIDTH, top + 4, bin_width, BIN_HEIGHT);

        svg_line(0, top + 40, IMAGE_WIDTH, top + 40, "grey", stroke_dasharray);

        top += 40;
    }
    svg_end();
}
