#include <iostream>
using namespace std;

template <typename T>
void sort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                T t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
}

template <typename T>
void show(const T arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    int n;
    cout << "Number of integers: "; cin >> n;
    if (!cin || n <= 0) { cout << "Nothing to sort.\n"; return 0; }
    int *ia = new int[n];
    for (int i = 0; i < n; i++) cin >> ia[i];
    sort(ia, n);
    cout << "Sorted integers: "; show(ia, n);
    delete[] ia;

    cout << "Number of floats: "; cin >> n;
    if (!cin || n <= 0) { cout << "Nothing to sort.\n"; return 0; }
    float *fa = new float[n];
    for (int i = 0; i < n; i++) cin >> fa[i];
    sort(fa, n);
    cout << "Sorted floats: "; show(fa, n);
    delete[] fa;
    return 0;
}
