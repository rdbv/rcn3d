#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <limits>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <initializer_list>

#define __RUNTIME_SIZE_CHECK

/* Version 2, SSE removed and much simpler and cleaner than last one (i hope) */

namespace rcn3d {


/* Just base data class */
template<std::size_t H, std::size_t W, typename T>
class Data
{
public:
    Data() {
        memset(&data[0], 0, size * sizeof(T));
    }

    // Begin and end for range-based for
    inline T* begin() {
        return &data[0];
    }

    inline T* end() {
        return &data[size];
    }

    inline const T* begin() const {
        return &data[0];
    }

    inline const T* end() const {
        return &data[size];
    }

    static constexpr std::size_t size = H*W;

    T data[size];

} __attribute__((packed));



/* Vector base */
template<std::size_t L, typename P>
class Vec : public Data<L, 1, P>
{
public:
    Vec() {
    }

    // Init all values
    Vec(const P& a) {
        for(std::size_t i=0;i<L;++i)
            this->data[i] = a;
    }
    
    Vec(const P& a, const P& b) {
        static_assert(L == 2, "Only for Vec2");
        this->data[0] = a, this->data[1] = b;
    }

    Vec(const P& a, const P& b, const P& c) {
        static_assert(L == 3, "Only for Vec3");
        this->data[0] = a, this->data[1] = b;
        this->data[2] = b;
    }

    Vec(const P& a, const P& b, const P& c, const P& d) {
        static_assert(L == 4, "Only for Vec4");
        this->data[0] = a, this->data[1] = b;
        this->data[2] = b, this->data[3] = d;
    }
    
    // Access operators
    inline P& operator()(std::size_t i) {
        return this->data[i];
    }

    const inline P& operator()(std::size_t i) const {
        return this->data[i];
    }

    // Getters/Setters
    inline P& x() {
        return this->data[0];
    }

    inline P& y() {
        return this->data[1];
    }

    inline P& z() {
        static_assert(L >= 3, "");
        return this->data[2];
    }

    inline P& w() {
        static_assert(L >= 4, "");
        return this->data[3];
    }

    // ==================== Operators ==================== 

    /* Scalar */
    const inline Vec<L, P> operator+(const P& rhs) const {
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i)
            v.data[i] = this->data[i] + rhs;
        return v;
    }

    const inline Vec<L, P>& operator+=(const P& rhs) {
        *this = *this + rhs;
        return *this;
    }

    const inline Vec<L, P> operator-(const P& rhs) const {
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i)
            v.data[i] = this->data[i] - rhs;
        return v;
    }

    const inline Vec<L, P>& operator-=(const P& rhs) {
        *this = *this - rhs;
        return *this;
    }

    const inline Vec<L, P> operator*(const P& rhs) const{
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i)
            v.data[i] = this->data[i] * rhs;
        return v;
    }

    const inline Vec<L, P>& operator*=(const P& rhs) {
        *this = *this * rhs;
        return *this;
    }

    const inline Vec<L, P> operator/(const P& rhs) const {
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i)
            v.data[i] = this->data[i] / rhs;
    }

    const inline Vec<L, P>& operator/=(const P& rhs) {
        *this = *this / rhs;
        return *this;
    }


    /* Vector */
    const inline Vec<L, P> operator+(const Vec<L, P>& rhs) const {
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i)
            v.data[i] = this->data[i] + rhs.data[i];
        return v;
    }

    const inline Vec<L, P>& operator+=(const Vec<L, P>& rhs) {
        *this = *this + rhs;
        return *this;
    }

    const inline Vec<L, P> operator-(const Vec<L, P>& rhs) const {
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i)
            v.data[i] = this->data[i] - rhs.data[i];
        return v;
    }

    const inline Vec<L, P>& operator-=(const Vec<L, P>& rhs) {
        *this = *this - rhs;
        return *this;
    }

    const inline Vec<L, P> operator*(const Vec<L, P>& rhs) const {
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i)
            v.data[i] = this->data[i] * rhs.data[i];
        return v;
    }

    const inline Vec<L, P>& operator*=(const Vec<L, P>& rhs) {
        *this = *this * rhs;
        return *this;
    }

    const inline Vec<L, P> operator/(const Vec<L, P>& rhs) const {
        Vec<L, P> v;
        for(std::size_t i=0;i<L;++i) 
            v.data[i] = this->data[i] / rhs.data[i];
        return v;
    }

    const inline Vec<L, P>& operator/=(const Vec<L, P>& rhs) {
        *this = *this / rhs;
        return *this;
    }

};

template<std::size_t W, std::size_t H, typename T>
class Mat : public Data<W, H, T>
{
public:
    Mat() {
    }

    Mat(const std::initializer_list<T>& list) {
#ifdef __RUNTIME_SIZE_CHECK
        assert(list.size() == this->size);
#endif
        std::size_t i=0;
        for(const auto&v : list)
            this->data[i] = v, ++i;
    }
    
    Mat(const Mat<W, H, T>& rhs) {
        for(std::size_t i=0;i<W;++i)
            for(std::size_t j=0;j<H;++j)
                this->data[i*H+j] = rhs.data[i*H+j];
    }

};

/*
// Matrix
template<std::size_t I, std::size_t J, typename T>
class Mat : public Data<I, J, T>
{
public:
    Mat() {
    }

    Mat(const std::initializer_list<T>& list) {
#ifdef __RUNTIME_SIZE_CHECK
        assert(list.size() == this->size);
#endif
        std::size_t i=0;
        for(const auto&v : list)
            this->data[i] = v, ++i;
    }
    
    Mat(const Mat<I, J, T>& rhs) {
        for(std::size_t i=0;i<I;++i)
            for(std::size_t j=0;j<J;++j)
                this->data[i*I+j] = rhs.data[i*I+j];
    }

    // Set/Get
    inline T& operator()(std::size_t row, std::size_t col) {
        return this->data[I*row+col];
    }

    const inline T& operator()(std::size_t row, std::size_t col) const {
        return this->data[I*row+col];
    }



};
*/

template<std::size_t L, typename P>
std::ostream& operator<<(std::ostream& os, const Vec<L, P>& v) {
    os.precision(3);
    os << std::fixed;
    os << "[";
    int i=0;
    for(const auto &q : v) {
        os << q;
        if(i != L-1) os << ", ";
        ++i;
    }
    os << "]";
 
    return os;
}

template<std::size_t W, std::size_t H, typename T>
std::ostream& operator<<(std::ostream& os, const Mat<W, H, T>& v) {
    os.precision(3);
    os << std::fixed;
    
    for(std::size_t i=0;i<W;i++) {
        os << "[";
        for(std::size_t j=0;j<H-1;j++) 
            os << v.data[W*i+j] << ", ";
        os << v.data[W*i+H-1] << "]\n";
    }
    return os;
}

typedef rcn3d::Vec<2, int>    Vec2i;
typedef rcn3d::Vec<2, float>  Vec2f;
typedef rcn3d::Vec<2, double> Vec2d;

typedef rcn3d::Vec<3, int>    Vec3i;
typedef rcn3d::Vec<3, float>  Vec3f;
typedef rcn3d::Vec<3, double> Vec3d;

typedef rcn3d::Vec<4, int>    Vec4i;
typedef rcn3d::Vec<4, float>  Vec4f;
typedef rcn3d::Vec<4, double> Vec4d;


typedef rcn3d::Mat<3, 4, int>     Mat3x4i;

typedef rcn3d::Mat<3, 3, int>     Mat3x3i;
typedef rcn3d::Mat<3, 3, float>   Mat3x3f;
typedef rcn3d::Mat<3, 3, double>  Mat3x3d;

typedef rcn3d::Mat<4, 4, int>     Mat4x4i;
typedef rcn3d::Mat<4, 4, float>   Mat4x4f;
typedef rcn3d::Mat<4, 4, double>  Mat4x4d;


} // namespace rcn3d


#endif
