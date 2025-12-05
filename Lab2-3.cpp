#include <iostream>

using namespace std;

void inputData(float* p, int n) {
    cout << "Введите значения: ";
    for (int i = 0; i < n; i++) {
        cin >> *(p + i);
    }
}

float average(const float* p, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *(p + i);
    }
    return sum / n;
}

float minValue(const float* p, int n) {
    float minVal = *(p);
    for (int i = 1; i < n; i++) {
        if (*(p + i) < minVal) {
            minVal = *(p + i);
        }
    }
    return minVal;
}

float maxValue(const float* p, int n) {
    float maxVal = *(p);
    for (int i = 1; i < n; i++) {
        if (*(p + i) > maxVal) {
            maxVal = *(p + i);
        }
    }
    return maxVal;
}

float* filterAboveAverage(float* p, int n, int& newCount) {
    float avg = average(p, n);
    
    newCount = 0;
    for (int i = 0; i < n; i++) {
        if (*(p + i) > avg) {
            newCount++;
        }
    }
    
    if (newCount == 0) {
        return nullptr;
    }
    
    float* newArray = new float[newCount];
    
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (*(p + i) > avg) {
            *(newArray + index) = *(p + i);
            index++;
        }
    }
    
    return newArray;
}

int main() 
{
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    cout << "=== Анализ сенсора ====" << endl;
    
    int n;
    cout << "Введите количество измерений: ";
    cin >> n;
    
    if (n <= 0) {
        cout << "Количество измерений должно быть положительным числом!" << endl;
        return 1;
    }
    
    float* data = new float[n];
    
    inputData(data, n);
     float avg = average(data, n);
    float minVal = minValue(data, n);
    float maxVal = maxValue(data, n);
    
    cout << "\nСреднее значение: " << avg << endl;
    cout << "Минимум: " << minVal << endl;
    cout << "Максимум: " << maxVal << endl;
    
    int newCount = 0;
    float* aboveAverageData = filterAboveAverage(data, n, newCount);
    
    cout << "\nЗначения выше среднего:" << endl;
    if (aboveAverageData == nullptr || newCount == 0) {
        cout << "Нет значений выше среднего" << endl;
    } else {
        for (int i = 0; i < newCount; i++) {
            cout << *(aboveAverageData + i) << " ";
        }
        cout << endl;
    }
    
    delete[] data;
    if (aboveAverageData != nullptr) {
        delete[] aboveAverageData;
    }
    
    return 0;
}