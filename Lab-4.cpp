#include <iostream>
#include <iomanip>

using namespace std;

float dayAverage(float* row, int h) {
    float sum = 0;
    for (int i = 0; i < h; i++) {
        sum += *(row + i);
    }
    return sum / h;
}

float overallAverage(float** p, int d, int h) {
    float total = 0;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < h; j++) {
            total += *(*(p + i) + j);
        }
    }
    return total / (d * h);
}

void showHotDays(float** p, int d, int h) {
    float overall = overallAverage(p, d, h);
    cout << "\nТеплые дни:" << endl;
    bool found = false;
    
    for (int i = 0; i < d; i++) {
        float avg = dayAverage(*(p + i), h);
        if (avg > overall) {
            cout << "День " << i + 1 << " (среднее = " << fixed << setprecision(1) << avg << ")" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "Нет дней со средней температурой выше общей" << endl;
    }
}

int main() 
{
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    int d, h;
    
    cout << "Введите количество дней: ";
    cin >> d;
    
    if (d <= 0 || d > 30) {
        cout << "Количество дней должно быть от 1 до 30!" << endl;
        return 1;
    }
    
    cout << "Введите количество измерений в дне: ";
    cin >> h;
    
    if (h <= 0 || h > 24) {
        cout << "Количество измерений должно быть от 1 до 24!" << endl;
        return 1;
    }
    
    float** data = new float*[d];
    for (int i = 0; i < d; i++) {
        *(data + i) = new float[h];
    }
    
    for (int i = 0; i < d; i++) {
        cout << "День " << i + 1 << ": ";
        for (int j = 0; j < h; j++) {
            cin >> *(*(data + i) + j);
        }
    }
    
    float overall = overallAverage(data, d, h);
    cout << fixed << setprecision(1);
    cout << "\nОбщая средняя температура: " << overall << endl;
    
    showHotDays(data, d, h);
    
    for (int i = 0; i < d; i++) {
        delete[] *(data + i);
    }
    delete[] data;
    
    return 0;
}