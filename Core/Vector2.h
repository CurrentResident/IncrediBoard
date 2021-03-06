#ifndef VECTOR_2_T_H_
#define VECTOR_2_T_H_

template <typename ComponentType>
struct Vector2
{
    Vector2() :
        x(),
        y()
    {
    }

    Vector2(const ComponentType& i_x,
            const ComponentType& i_y) :
        x(i_x),
        y(i_y)
    {
    }

    ~Vector2() = default;

    Vector2(const Vector2&) = default;
    Vector2(Vector2&&)      = default;

    Vector2& operator=(const Vector2&) = default;
    Vector2& operator=(Vector2&&)      = default;

    Vector2& operator+=(const Vector2& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    Vector2& operator-=(const Vector2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }

    Vector2& operator*=(const ComponentType& scale)
    {
        x *= scale;
        y *= scale;

        return *this;
    }

    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.x + rhs.x,
                       lhs.y + rhs.y);
    }

    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
    {
        return Vector2(lhs.x - rhs.x,
                       lhs.y - rhs.y);
    }

    friend Vector2 operator*(const Vector2& lhs, const ComponentType& rhs)
    {
        return Vector2(lhs.x * rhs,
                       lhs.y * rhs);
    }

    ComponentType x;
    ComponentType y;
};

#endif
