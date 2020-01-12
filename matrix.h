#pragma once

#include <map>
#include <memory>
#include <array>

template< typename T, const T defaultValue, const size_t dimensionValue = 2>
class Matrix
{
private:
    struct Index;

private:
    using element_type = T;
    using index_type = std::array<size_t, dimensionValue>;
    using key_type = Index;
    using matrix_type = std::map<key_type, element_type>;

private:
    struct Index
    {
        index_type m_Index = {};

        bool operator<(const Index& index) const
        {
            return  m_Index < index.m_Index;
        }
    };

    struct Record
    {
        matrix_type& m_Matrix;
        key_type m_Key = {};
        element_type value = defaultValue;
        size_t count = 0;

        auto& operator[](size_t index)
        {
            if( count < dimensionValue )
            {
                m_Key.m_Index[count++] = index;

                auto element = m_Matrix.find( m_Key );

                if( element != m_Matrix.end() )
                {
                    value = element->second;
                }
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
                m_Matrix.erase(m_Key);
                value = defaultValue;
            }
            else
            {
                m_Matrix[m_Key] = newElement;
            }

            value = newElement;

            return *this;
        }

        Record& operator= (const Record& newRecord)
        {
            if( newRecord.value == defaultValue )
            {
                m_Matrix.erase(m_Key);
                value = defaultValue;
            }
            else
            {
                m_Matrix[m_Key] = newRecord.value;
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

    Record operator[](size_t index)
    {
        auto record = Record{m_Matrix};
        record.m_Key.m_Index[record.count++] = index;

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

    friend std::ostream& operator<< (std::ostream& out, const typename matrix_type::value_type & point)
    {
        for( const auto& element : point.first.m_Index)
        {
            out << element << " ";
        }

        out << point.second;

        return out;
    }

private:
    matrix_type m_Matrix;
};


