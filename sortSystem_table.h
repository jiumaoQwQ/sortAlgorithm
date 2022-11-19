#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

#ifndef RANDOM_MAX_VALUE
#define RANDOM_MAX_VALUE 100
#endif

#ifndef ITERATIONS
#define ITERATIONS 10
#endif

class SortSystem
{
public:
    enum Type
    {
        POSITIVE,
        REVERSE,
        RANDOM
    };

    void init(int n, Type type, std::vector<std::string> *_pres)
    {
        pres = _pres;

        size = n;
        m_vec.resize(0);
        m_vec.reserve(size);
        switch (type)
        {
        case Type::POSITIVE:
            col = 1;

            for (int i = 0; i < size; i++)
                m_vec.emplace_back(i);
            break;
        case Type::REVERSE:
            col = 2;

            for (int i = size - 1; i >= 0; i--)
                m_vec.emplace_back(i);
            break;
        case Type::RANDOM:
            col = 3;

            for (int i = 0; i < size; i++)
                m_vec.emplace_back(rand() % RANDOM_MAX_VALUE);
            break;
        default:
            std::cout << "Please input the correct type." << std::endl;
            exit(0);
        }
    }

    void run()
    {
        testTime(insertionSort, c_insertionSort);
        pres->at(2 * 4 + col) = std::string(std::to_string(timeExpense) + " " + std::to_string(timesOfComparison) + " " + std::to_string(timesOfMoves) + "|");

        testTime(selectionSort, c_selectionSort);
        pres->at(3 * 4 + col) = std::string(std::to_string(timeExpense) + " " + std::to_string(timesOfComparison) + " " + std::to_string(timesOfMoves) + "|");

        testTime(mergeSort, c_mergeSort);
        pres->at(4 * 4 + col) = std::string(std::to_string(timeExpense) + " " + std::to_string(timesOfComparison) + " " + std::to_string(timesOfMoves) + "|");

        testTime(heapSort, c_heapSort);
        pres->at(5 * 4 + col) = std::string(std::to_string(timeExpense) + " " + std::to_string(timesOfComparison) + " " + std::to_string(timesOfMoves) + "|");

        testTime(quickSort, c_quickSort);
        pres->at(6 * 4 + col) = std::string(std::to_string(timeExpense) + " " + std::to_string(timesOfComparison) + " " + std::to_string(timesOfMoves) + "|");
    }

private:
    int size{};
    std::vector<int> m_vec, new_vec;
    std::vector<std::string> *pres;

    int col, row;

    float timeExpense;
    int timesOfComparison, timesOfMoves;

    template <class Func1, class Func2>
    void testTime(Func1 &&func1, Func2 &&func2)
    {
        std::chrono::microseconds m_time{};
        int comparisonTimes = 0, moveTimes = 0;

        for (int i = 0; i < ITERATIONS; i++)
        {
            new_vec = m_vec;
            auto t1 = std::chrono::steady_clock::now();
            func1(new_vec);
            m_time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - t1);
        }

        new_vec = m_vec;
        func2(new_vec, comparisonTimes, moveTimes);

        timeExpense = m_time.count() * 1.0 / ITERATIONS;
        timesOfComparison = comparisonTimes;
        timesOfMoves = moveTimes;
    }

    static void insertionSort(std::vector<int> &vec)
    {
        for (int i = 1; i < vec.size(); i++)
        {
            int key = vec[i];
            int j = i - 1;
            while (j >= 0 && vec[j] > key)
            {
                vec[j + 1] = vec[j];
                j--;
            }
            vec[j + 1] = key;
        }
    }
    static void c_insertionSort(std::vector<int> &vec, int &comparisonTimes, int &moveTimes)
    {
        for (int i = 1; i < vec.size(); i++)
        {
            moveTimes++;
            int key = vec[i];
            int j = i - 1;
            comparisonTimes++;
            while (j >= 0 && vec[j] > key)
            {
                comparisonTimes++;
                moveTimes++;
                vec[j + 1] = vec[j];
                j--;
            }
            moveTimes++;
            vec[j + 1] = key;
        }
    }

    static void selectionSort(std::vector<int> &vec)
    {
        for (int i = 0; i < vec.size() - 1; i++)
        {
            int index = i;
            for (int j = i + 1; j < vec.size(); j++)
            {
                if (vec[j] < vec[index])
                {
                    index = j;
                }
            }
            std::swap(vec[i], vec[index]);
        }
    }
    static void c_selectionSort(std::vector<int> &vec, int &comparisonTimes, int &moveTimes)
    {
        for (int i = 0; i < vec.size() - 1; i++)
        {
            int index = i;
            for (int j = i + 1; j < vec.size(); j++)
            {
                comparisonTimes++;
                if (vec[j] < vec[index])
                {
                    index = j;
                }
            }
            moveTimes++;
            std::swap(vec[i], vec[index]);
        }
    }

    static void mergeSort(std::vector<int> &vec)
    {
        int first = 0, end = vec.size() - 1;
        std::vector<int> tmp_vec = vec;
        rec_mergeSort(vec, tmp_vec, first, end);
    }
    static void rec_mergeSort(std::vector<int> &vec, std::vector<int> &tmp_vec, int first, int end)
    {
        if (first >= end)
            return;
        int mid = (first + end) / 2;
        int first1 = first, end1 = mid;
        int first2 = mid + 1, end2 = end;
        int k = first;

        rec_mergeSort(vec, tmp_vec, first1, end1);
        rec_mergeSort(vec, tmp_vec, first2, end2);

        while (first1 <= end1 && first2 <= end2)
        {
            if (vec[first1] > vec[first2])
            {
                tmp_vec[k++] = vec[first2++];
            }
            else
            {
                tmp_vec[k++] = vec[first1++];
            }
        }

        while (first1 <= end1)
            tmp_vec[k++] = vec[first1++];
        while (first2 <= end2)
            tmp_vec[k++] = vec[first2++];

        for (int i = first; i <= end; i++)
        {
            vec[i] = tmp_vec[i];
        }
    }
    static void c_mergeSort(std::vector<int> &vec, int &comparisonTimes, int &moveTimes)
    {
        int first = 0, end = vec.size() - 1;
        std::vector<int> tmp_vec = vec;
        c_rec_mergeSort(vec, tmp_vec, first, end, comparisonTimes, moveTimes);
    }
    static void c_rec_mergeSort(std::vector<int> &vec, std::vector<int> &tmp_vec, int first, int end, int &comparisonTimes, int &moveTimes)
    {
        if (first >= end)
            return;
        int mid = (first + end) / 2;
        int first1 = first, end1 = mid;
        int first2 = mid + 1, end2 = end;
        int k = first;

        rec_mergeSort(vec, tmp_vec, first1, end1);
        rec_mergeSort(vec, tmp_vec, first2, end2);

        while (first1 <= end1 && first2 <= end2)
        {
            comparisonTimes++;
            moveTimes++;
            if (vec[first1] > vec[first2])
            {
                tmp_vec[k++] = vec[first2++];
            }
            else
            {
                tmp_vec[k++] = vec[first1++];
            }
        }

        while (first1 <= end1)
        {
            tmp_vec[k++] = vec[first1++];
            moveTimes++;
        }
        while (first2 <= end2)
        {
            tmp_vec[k++] = vec[first2++];
            moveTimes++;
        }
        for (int i = first; i <= end; i++)
        {
            vec[i] = tmp_vec[i];
            moveTimes++;
        }
    }

    static void heapSort(std::vector<int> &vec)
    {
        for (int i = vec.size() / 2 - 1; i >= 0; i--)
        {
            sift(vec, i, vec.size() - 1);
        }
        for (int i = vec.size() - 1; i > 0; i--)
        {
            std::swap(vec[0], vec[i]);
            sift(vec, 0, i - 1);
        }
    }
    static void sift(std::vector<int> &vec, int start, int last)
    {
        int i = start, j = 2 * i + 1;
        while (j <= last)
        {
            if (j < last && vec[j] < vec[j + 1])
                j++;
            if (vec[i] > vec[j])
                break;
            else
            {
                std::swap(vec[i], vec[j]);
                i = j;
                j = 2 * i + 1;
            }
        }
    }
    static void c_heapSort(std::vector<int> &vec, int &comparisonTimes, int &moveTimes)
    {
        for (int i = vec.size() / 2 - 1; i >= 0; i--)
        {
            c_sift(vec, i, vec.size() - 1, comparisonTimes, moveTimes);
        }
        for (int i = vec.size() - 1; i > 0; i--)
        {
            std::swap(vec[0], vec[i]);
            c_sift(vec, 0, i - 1, comparisonTimes, moveTimes);
        }
    }
    static void c_sift(std::vector<int> &vec, int start, int last, int &comparisonTimes, int &moveTimes)
    {
        int i = start, j = 2 * i + 1;
        while (j <= last)
        {
            comparisonTimes++;
            if (j < last && vec[j] < vec[j + 1])
                j++;
            comparisonTimes++;
            if (vec[i] > vec[j])
                break;
            else
            {
                moveTimes++;
                std::swap(vec[i], vec[j]);
                i = j;
                j = 2 * i + 1;
            }
        }
    }
    static void quickSort(std::vector<int> &vec)
    {
        rec_quickSort(vec, 0, vec.size() - 1);
    }

    static void rec_quickSort(std::vector<int> &vec, int l, int r)
    {
        if (l >= r)
            return;
        int i = l, j = r;
        while (i < j)
        {
            while (i < j && vec[i] <= vec[j])
                j--;
            if (i < j)
                std::swap(vec[i++], vec[j]);
            while (i < j && vec[j] >= vec[i])
                i++;
            if (i < j)
                std::swap(vec[j--], vec[i]);
        }
        rec_quickSort(vec, l, i - 1);
        rec_quickSort(vec, i + 1, r);
    }

    static void c_quickSort(std::vector<int> &vec, int &comparisonTimes, int &moveTimes)
    {
        c_rec_quickSort(vec, 0, vec.size() - 1, comparisonTimes, moveTimes);
    }

    static void c_rec_quickSort(std::vector<int> &vec, int l, int r, int &comparisonTimes, int &moveTimes)
    {
        if (l >= r)
            return;
        int i = l, j = r;
        while (i < j)
        {
            while (i < j && vec[i] <= vec[j])
            {
                comparisonTimes++;
                j--;
            }
            if (i < j)
            {
                moveTimes++;
                std::swap(vec[i++], vec[j]);
            }
            while (i < j && vec[j] >= vec[i])
            {
                comparisonTimes++;
                i++;
            }
            if (i < j)
            {
                moveTimes++;
                std::swap(vec[j--], vec[i]);
            }
        }
        c_rec_quickSort(vec, l, i - 1, comparisonTimes, moveTimes);
        c_rec_quickSort(vec, i + 1, r, comparisonTimes, moveTimes);
    }

    void print()
    {
        for (auto i : new_vec)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};