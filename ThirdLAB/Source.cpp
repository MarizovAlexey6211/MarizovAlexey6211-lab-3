#include<iostream>
#include<time.h>
#include"BinaryImage.h"


int main()
{
    setlocale(LC_ALL, "rus");
    try {
        /*BinaryImage<int, 3, 7> image(3, 3);

        image(0, 0) = true;
        image(1, 1) = 7;

        for (auto& a : image) {
            std::cout << a << " ";
        }

        std::cout << std::endl;

        !image;

        for (auto it = image.begin(); it != image.end(); it++) {
            std::cout << *it << " ";
        */
        //������ ������ � ����������� 
        int flag = 1;
        while (flag) {
            std::cout << "������� ����������� ��������� �����������: ";
            int rows, cols;
            std::cin >> rows >> cols;
            BinaryImage<int, 0, 1> image(rows, cols);
            std::cout << image;
            std::cout << "�������� �������� �����������? ������� 1 ��� ������ ��� 0 ��� �����������\n";
            int choice;
            std::cin >> choice;
            while (choice != 0)
            {
                int i, j;
                do {
                    std::cout << "������� ������ ��� ������ � �������:";
                    std::cin >> i >> j;
                } while (i >= rows || j >= cols);
                std::cout << "������� �������� ";
                bool value;
                std::cin >> value;
                image(i, j) = value;
                std::cout << image;
                std::cout << "���� ������ �������� ��� ������ �� ������� 1, ���� ��� �� 0:\n ";
                std::cin >> choice;
            }
            std::cout << image;
            std::cout << "������� ����� �����������? �������  1 ��� ��������������  0 ��� ������ �� ���������: ";
            std::cin >> flag;
        }



    }
    catch (const char* msg) {
        std::cout << msg << '\n';
    }


}
