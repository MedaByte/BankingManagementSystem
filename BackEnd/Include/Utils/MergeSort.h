#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>
#include <cctype>   // for std::toupper
#include <string>

namespace Utils {

    // Helper: Convert a string to uppercase without modifying the original
    inline std::string ToUpper(const std::string& str) {
        std::string result = str;
        for (char& c : result) c = std::toupper(static_cast<unsigned char>(c));
        return result;
    }

    // Merge two sorted subarrays in-place (case-insensitive) | Mescla dois subarrays ordenados
    template<typename T>
    inline void Merge(T* arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        T* L = new T[n1];
        T* R = new T[n2];

        for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
        for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            std::string LNameUpper = ToUpper(L[i].Name);
            std::string RNameUpper = ToUpper(R[j].Name);

            if (LNameUpper == RNameUpper) {
                std::string LLastUpper = ToUpper(L[i].LastName);
                std::string RLastUpper = ToUpper(R[j].LastName);
                arr[k++] = (LLastUpper <= RLastUpper) ? L[i++] : R[j++];
            } else {
                arr[k++] = (LNameUpper <= RNameUpper) ? L[i++] : R[j++];
            }
        }

        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];

        delete[] L;
        delete[] R;
    }

    // MergeSort recursive implementation in-place | Implementação recursiva in-place
    template<typename T>
    inline void MergeSort(T* arr, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }

}

#endif
