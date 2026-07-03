#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Вспомогательные функции для работы с SVG ---

// Выводит начало SVG-документа
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

// Выводит текст в SVG с заданными координатами
void svg_text(double left, double baseline, string text)
{
    // Вместо фиксированных 20, 35 и "anything you want"
    // подставляем реальные параметры, переданные в функцию
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}



// Выводит конец SVG-документа
void svg_end()
{
    cout << "</svg>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='" << x << "' y='" << y
         << "' width='" << width << "' height='" << height
         << "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}


void show_histogram_svg(const vector<size_t>& bins)
{
    // Настройки размеров и отступов из методички
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    // Открываем холст, используя наши константы
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    for (size_t bin : bins)
    {
        // Вычисляем ширину текущего прямоугольника (количество элементов * шаг)
        const double bin_width = BLOCK_WIDTH * bin;

        // Выводим текст. top плавно увеличивается, сдвигая текст вниз на каждой итерации
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));

        // Выводим прямоугольник с новыми параметрами цвета (красная граница, розовая заливка)
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "red", "#ffeeee");

        // Сдвигаем координату top вниз для следующей корзины
        top += BIN_HEIGHT;
    }

    // Закрываем холст
    svg_end();
}




// --- Основная функция отрисовки гистограммы ---




int main()
{
    // Имитируем данные, которые могли прийти из прошлых шагов
    // Допустим, у нас 3 корзины со значениями 5, 10 и 3
    vector<size_t> bins = {5, 10, 3};

    // Вызываем графический вывод вместо текстового
    show_histogram_svg(bins);

    return 0;
}

