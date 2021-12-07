#ifndef BinaryImage_h
#define BinaryImage_h


#include <vector>

template<typename T, T falseValue, T trueValue>
class BinaryImage {
private:
    class TT {
    public:
        T data;
        TT& operator=(bool value) {
            if (value)
                data = trueValue;
            else
                data = falseValue;
            return *this;
        }
        TT& operator=(T value) {
            if (value != trueValue && value != falseValue)
                throw "invalid value assignment";
            data = value;
            return *this;
        }
        bool operator==(T value) {
            if (value == data)
                return true;
            else
                return false;
        }//смотрим какое значение в €чейке ()

        friend std::ostream& operator<<(std::ostream& out, const TT& rhs)
        {
            if (rhs.data == trueValue)
                out << true;
            else
                out << false;
            return out;
        }

    };
    class MyIterator {//ѕодкласс итераторов
        int currRow;
        int currCol;
        BinaryImage& parent;
    public:
        MyIterator(BinaryImage& img) : currRow(0), currCol(0), parent(img) {}//1-
        MyIterator(BinaryImage& img, int currRow) : currRow(currRow), currCol(0), parent(img) {}//1
        MyIterator(const MyIterator& rhs) : currRow(rhs.currRow), currCol(rhs.currCol), parent(rhs.parent) {}//1
        MyIterator& operator++() {//сдвиг на следующий элемент класса (переход к следующей €чейке)
            if (currCol < parent.cols)
                currCol++;
            if (currCol == parent.cols) {
                currCol = 0;
                currRow++;
            }
            return *this;
        }
        MyIterator operator++(int) {
            MyIterator tmp(*this); operator++(); return tmp;
        }
        bool operator==(const MyIterator& rhs) const {
            return currRow == rhs.currRow && currCol == rhs.currCol;
        }
        bool operator!=(const MyIterator& rhs) const {//данные €чеек итератора совпадают с данными €чеек объекта класса
            return !(currRow == rhs.currRow && currCol == rhs.currCol);
        }
        TT& operator*() {
            return parent.data[currRow][currCol];
        }
    };
    std::vector<std::vector<TT>> data;//первый пункт
    int cols;
    int rows;
public:

    BinaryImage() : rows(1), cols(1)
    {
        for (int i = 0; i < rows; ++i)
        {
            std::vector<TT> d(cols);//0
            for (int i = 0; i < cols; ++i)
                d[i] = falseValue;
            data.push_back(d);
        }
    }
    BinaryImage(int rows, int cols) : rows(rows), cols(cols) {//1
        for (int i = 0; i < rows; ++i) {
            std::vector<TT> d(cols);//0
            for (int i = 0; i < cols; ++i)
                d[i] = falseValue;
            data.push_back(d);
        }
    }
    MyIterator begin() {
        return MyIterator(*this);
    }
    MyIterator end() {
        return MyIterator(*this, rows);
    }
    double Ratio() {
        int count = 0;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j].data == trueValue)
                    count++;
        return (double)count / (rows * cols);
    }
    bool operator==(const BinaryImage& rhs) {
        if (cols != rhs.cols || rows != rhs.rows)
            return false;
        bool res = true;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j].data != rhs.data[i][j].data) {
                    res = false;
                    break;
                }
        return res;
    }
    bool operator!=(const BinaryImage& rhs) {
        return !(*this == rhs);

    }
    bool operator()(int i, int j) const {//дл€ констант
        if (!(i >= 0 && i < rows && j >= 0 && j < cols)) {
            throw "Error";
        }
        return data[i][j].data == trueValue;
    }

    TT& operator()(int i, int j) {
        if (!(i >= 0 && i < rows && j >= 0 && j < cols)) {
            throw "Error";
        }
        return data[i][j];
    }

    void operator!() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] == trueValue)//bool(26 строка)
                    data[i][j] = falseValue;//TT&(20 строка )
                else
                    data[i][j] = trueValue;//TT&(20 строка)
            }
        }
    }

    BinaryImage& operator*(const BinaryImage& rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw "Error";
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j].data == trueValue && rhs.data[i][j].data == trueValue)
                    data[i][j].data = trueValue;
                else
                    data[i][j].data = falseValue;
            }
        }
        return *this;
    }

    BinaryImage& operator*(bool value) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j].data == trueValue && value == trueValue)
                    data[i][j].data = trueValue;
                else
                    data[i][j].data = falseValue;
            }
        }
        return *this;
    }


    BinaryImage& operator+(const BinaryImage& rhs) {
        if (rows != rhs.rows || cols != rhs.cols) {
            throw"Error";
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j].data == falseValue && rhs.data[i][j].data == falseValue)
                    data[i][j].data = falseValue;
                else
                    data[i][j].data = trueValue;
            }
        }
        return *this;
    }

    BinaryImage& operator+(bool value) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j].data == falseValue && value == falseValue)
                    data[i][j].data = falseValue;
                else
                    data[i][j].data = trueValue;
            }
        }
        return *this;
    }

    void Print() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j].data == falseValue)
                    std::cout << '.';
                else
                    std::cout << '1';
            }
            std::cout << '\n';
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const BinaryImage<T, falseValue, trueValue>& img)
    {
        for (int i = 0; i < img.rows; ++i) {
            for (int j = 0; j < img.cols; ++j) {
                if (img.data[i][j].data == falseValue)
                    out << '.';
                else
                    out << '1';
            }
            out << '\n';
        }

        return out;
    }

};

#endif
