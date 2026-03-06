#pragma once

class Vector2
{
public:
    float x, y;

public:
    Vector2() : x(0), y(0)
    {
    }
    Vector2(const float x, const float y) : x(x), y(y)
    {
    }

    // Vector math
    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Left-hand scalar multiply: 2.0f * v
    friend Vector2 operator*(float scalar, const Vector2& v)
    {
        return v * scalar;
    }

    // Equality
    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2& other) const
    {
        return !(*this == other);
    }

    // Comparison
    bool operator<(const Vector2& other) const
    {
        return x < other.x && y < other.y;
    }
    bool operator>(const Vector2& other) const
    {
        return x > other.x && y > other.y;
    }

    bool operator<=(const Vector2& other) const
    {
        return x <= other.x && y <= other.y;
    }
    bool operator>=(const Vector2& other) const
    {
        return x >= other.x && y >= other.y;
    }
};
