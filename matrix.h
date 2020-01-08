#pragma once

#include <map>
#include <memory>


class frend;
template< typename T, const T defaultValue>
class Matrix
{
private:
    struct Index;

private:
    using element_type = T;
    using key_type = Index;
    using matrix_type = std::map<key_type, element_type>;

private:
    struct Index
    {
        int i = -1;
        int j = -1;

        bool operator<(const Index& index) const
        {
            if( i == index.i )
            {
                return j < index.j;
            }
            else
            {
                return i < index.i;
            }
        }
    };

    struct Record
    {
        matrix_type& m_Matrix;
        key_type index;
        element_type value = defaultValue;

        Record& operator[](int j)
        {
            index.j = j;

            auto element = m_Matrix.find(index);

            if( element != m_Matrix.end() )
            {
                value = element->second;
            }

            return *this;
        }

        operator element_type()
        {
            return value;
        }

        Record& operator= (const element_type& newElement)
        {
            if( newElement == defaultValue )
            {
                m_Matrix.erase(index);
                index.i = -1;
                index.j = -1;
                value = defaultValue;
            }
            else
            {
                m_Matrix[index] = newElement;
            }

            value = newElement;

            return *this;
        }

        Record& operator= (const Record& newRecord)
        {
            if( newRecord.value == defaultValue )
            {
                m_Matrix.erase(index);
                index.i = -1;
                index.j = -1;
                value = defaultValue;
            }
            else
            {
                m_Matrix[index] = newRecord.value;
            }

            value = newRecord.value;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, Record& point)
        {
            out << point.value;
            return out;
        }
    };

public:
    Matrix() = default;
    virtual ~Matrix() = default;

    size_t size() const
    {
        return m_Matrix.size();
    }

    Record operator[](int i)
    {
        auto record = Record{m_Matrix, i};

        return record;
    }

    auto begin()
    {
        return m_Matrix.begin();
    }

    auto end()
    {
        return m_Matrix.end();
    }

    friend std::ostream& operator<< (std::ostream& out, const std::pair< const key_type, element_type >& point)
    {
        out << point.first.i << " " << point.first.j << "   " << point.second;

        return out;
    }

private:
    matrix_type m_Matrix;
};

