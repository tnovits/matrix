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

    template<const size_t count, typename = std::enable_if_t<count < dimensionValue>>
    struct Record
    {
        matrix_type& m_Matrix;
        key_type m_Key = {};
        element_type value = defaultValue;

        auto operator[](size_t index)
        {
            m_Key.m_Index[count+1] = index;

            if( count+1 == dimensionValue-1)
            {
                auto element = m_Matrix.find( m_Key );

                if( element != m_Matrix.end() )
                {
                    value = element->second;
                }
            }

            return Record<count+1>{m_Matrix, m_Key, value};
        }

        operator element_type()
        {
            return value;
        }

        auto& operator= (const element_type& newElement)
        {
            // for c++ 17
 //           if constexpr (count+1 == dimensionValue)
            {
                if( newElement == defaultValue )
                {
                    m_Matrix.erase( m_Key );
                    value = defaultValue;
                }
                else
                {
                    m_Matrix[ m_Key ] = newElement;
                }

                value = newElement;


                return *this;
            }
//            else
//            {
//                return 0;
//            }
        }

        auto& operator= (const Record& newRecord)
        {
            // for c++ 17
 //           if constexpr (count+1 == dimensionValue)
            {
                if( newRecord.value == defaultValue )
                {
                    m_Matrix.erase( m_Key );
                    value = defaultValue;
                }
                else
                {
                    m_Matrix[ m_Key ] = newRecord.value;
                }

                value = newRecord.value;
                return *this;
            }
//            else
//            {
//                return 0;
//            }
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

    auto size() const
    {
        return m_Matrix.size();
    }

    auto operator[](size_t index)
    {
        return Record<0>{m_Matrix, index};;
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


