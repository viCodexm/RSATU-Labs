// thanks to Ilya Zimarev (@FGTRK) for providing this code
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct SampleArray{
    int dimension, l, B;
    vector<vector<int>> borders;
    vector<char> data;
};

struct Descriptor{
    int zero_component;
    vector<int> ind_multipliers;
};

void enter_sample_array(SampleArray &arr){
    cout << "Введите размерность массива: ";
    cin >> arr.dimension;

    arr.borders.resize(arr.dimension, vector<int>(2));
    cout << "Введите " << arr.dimension << " пар границ:\n";
    for (int i = 0; i < arr.dimension; ++i)
        cin >> arr.borders[i][0] >> arr.borders[i][1];

    cout << "Введите размер одного слота: ";
    cin >> arr.l;
    cout << "Введите адрес первого элемента: ";
    cin >> arr.B;

    // Сколько памяти нужно выделить под массив
    int size_array = arr.l;
    for (int i = 0; i < arr.dimension; ++i)
        size_array *= arr.borders[i][1] - arr.borders[i][0] + 1;
    arr.data.resize(size_array);
    // cout << size_array << endl;
    cout << endl;
}

void set_descriptor(SampleArray &arr, Descriptor &desc){
    desc.ind_multipliers.resize(arr.dimension);

    // Индексные множители
    desc.ind_multipliers[arr.dimension - 1] = arr.l;
    for (int i = arr.dimension - 2; i >= 0; --i)
        desc.ind_multipliers[i] = (arr.borders[i + 1][1] - arr.borders[i + 1][0] + 1) * desc.ind_multipliers[i + 1];

    // Нулевая компонента
    desc.zero_component = arr.B;
    for (int i = 0; i < arr.dimension; ++i)
        desc.zero_component -= arr.borders[i][0] * desc.ind_multipliers[i];
}

void print_descriptor(Descriptor &desc){
    int step = 10;
    cout << "Дескриптор введенного массива:\n";
    cout.setf(ios::fixed);
    cout << setw(step) << "A0";
    for (int i = 1; i <= desc.ind_multipliers.size(); ++i)
        cout << setw(step - 1) << "D" << i;
    cout << endl << setw(step) << desc.zero_component;

    for (int i = 0; i < desc.ind_multipliers.size(); ++i)
        cout << setw(step) << desc.ind_multipliers[i];
    cout << endl;
}

int calc_address(SampleArray &arr, Descriptor &desc){
    vector<int> input_indexes(arr.dimension);
    cout << "Введите индексы (" << arr.dimension <<  " штук) через пробел: ";
    for (int i = 0; i < arr.dimension; ++i)
        cin >> input_indexes[i];
    int start_index = desc.zero_component;
    for (int i = 0; i < arr.dimension; ++i)
        start_index += desc.ind_multipliers[i] * input_indexes[i];
    return start_index;
}

int main()
{

    SampleArray test_array;
    Descriptor desc;

    enter_sample_array(test_array);
    set_descriptor(test_array, desc);

    int key = 1, number_of_byte, start_index;
    string input_str;

    while (key){
        cout << string(60, '=');
        cout << "\nВведите номер операции из предложенных:\n";
        cout << "0 - выход из программы\n";
        cout << "1 - показать дескриптор массива\n";
        cout << "2 - запись в память значения элемента массива по индексам\n";
        cout << "3 - запись по номеру байта массива\n";
        cout << "4 - чтение из памяти значения элемента массива по индексам\n";
        cout << "5 - чтение по номеру байта массива\n>>> ";
        cin >> key;
        cout << endl;

        switch (key){
            case 0:
                break;

            case 1: {
                print_descriptor(desc);
                break;
            }

            case 2: {
                start_index = calc_address(test_array, desc);

                cout << "Введите значение (строку) из " << test_array.l << " символов: " ;
                cin >> input_str;
                for (int i = 0; i < test_array.l; ++i)
                    test_array.data[start_index + i - test_array.B] = input_str[i];
                break;
            }

            case 3: {
                cout << "Введите номер байта: ";
                cin >> number_of_byte;
                cout << "Введите значение (символ), которое хотите записать: ";
                cin >> test_array.data[number_of_byte - test_array.B];
                break;
            }

            case 4: {
                start_index = calc_address(test_array, desc);

                cout << "Значение: ";
                for (int i = 0; i < test_array.l; ++i)
                    cout << test_array.data[start_index + i - test_array.B];
                cout << endl;
                break;
            }

            case 5: {
                cout << "Введите номер байта: ";
                cin >> number_of_byte;
                cout << "Значение: " << test_array.data[number_of_byte - test_array.B];
                cout << endl;
                break;
            }
        }
    }
    return 0;
}