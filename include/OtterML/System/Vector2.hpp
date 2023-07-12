#ifndef OTER_VECTOR2_HPP
#define OTER_VECTOR2_HPP

#include <glm/vec2.hpp>
#include <yaml-cpp/yaml.h>

#include <OtterML/Common.hpp>

namespace oter
{
template <typename T, unsigned Tx, unsigned Ty>
class Matrix;

template <typename T>
struct Vector2
{
public:
	T X = static_cast<T>(0);
	T Y = static_cast<T>(0);

	/**
	 * @brief Construct a new default Vector2
	 */
	Vector2();

	/**
	 * @brief Construct a new Vector2 from coordinates
	 * @param x X coordinate
	 * @param y Y coordinate
	 */
	Vector2(T x, T y);

	/**
	 * @brief Construct a new Vector2 from a scalar value
	 * @param scalar Scalar value for both coordinates
	 */
	explicit Vector2(T scalar);

	/**
	 * @brief Construct a new Vector2 from a different Vector2
	 *
	 * Does not replace copy constructor
	 * @param other Vector to convert
	 */
	template <typename U>
	explicit Vector2(const Vector2<U>& other);

	/**
	 * @brief Copy constructor
	 */
	Vector2(const Vector2& other);

	/**
	 * @brief Construct a new Vector2 from a C-style array
	 * @param array Array to convert
	 */
	explicit Vector2(T array[2]);

	/**
	 * @brief Construct a new Vector2 from an std::array<T, 2>
	 * @param array Array to convert
	 */
	explicit Vector2(std::array<T, 2> array);

	/**
	 * @brief Construct a new Vector2 from a 2x1 oter::Matrix
	 *
	 * @param matrix
	 */
	explicit Vector2(Matrix<T, 1, 2> matrix);

	explicit Vector2(Matrix<T, 2, 1> matrix);

	/**
	 * @brief Construct a Vector2 from a glm::vec<2, U>
	 * @param glmVec glm::vec<2, U> to convert
	 */
	template <typename U>
	explicit Vector2(const glm::vec<2, U>& glmVec);

	/**
	 * @brief Convert to a std::array<
	 */
	explicit operator std::array<T, 2>() const;

	/**
	 * @brief Convert to a 2x1 oter::Matrix
	 */
	explicit operator Matrix<T, 1, 2>() const;

	/**
	 * @brief Convert to a glm::vec<2, U>
	 */
	template <typename U>
	explicit operator glm::vec<2, U>() const
	{
		return glm::vec<2, U>(static_cast<U>(this->X), static_cast<U>(this->Y));
	}

	[[nodiscard]] T operator[](size_t index) const
	{
		switch (index)
		{
		case 0:
			return this->X;
		case 1:
			return this->Y;
		default:
			throw std::out_of_range("Vector2 only contains 2 values.");
		}
	}

	/**
	 * @brief Compares two Vector2s
	 * @param right Vector2 to compare to
	 * @return True if Vector2s are equal
	 */
	[[nodiscard]] constexpr bool operator==(const Vector2& right) const;

	[[nodiscard]] constexpr f32 GetLength();
	[[nodiscard]] constexpr f32 GetLengthSquared();

	[[nodiscard]] Vector2 GetNormalized();

	[[nodiscard]] T Dot(const Vector2& right);
	[[nodiscard]] T Cross(const Vector2& right);

	// Member operators
	// Unary operators
	Vector2 operator-(const Vector2& right);

	// Binary scalar operators
	Vector2& operator+=(const T& right);
	Vector2& operator-=(const T& right);
	Vector2& operator*=(const T& right);
	Vector2& operator/=(const T& right);

	// Binary vector operators
	template <typename U>
	Vector2& operator+=(const Vector2<U>& right);
	template <typename U>
	Vector2& operator-=(const Vector2<U>& right);
	template <typename U>
	Vector2& operator*=(const Vector2<U>& right);
	template <typename U>
	Vector2& operator/=(const Vector2<U>& right);

	// Friend operators
	// Binary scalar operators
	friend Vector2 operator+(Vector2 left, const T& right)
	{
		left += right;
		return left;
	}
	friend Vector2 operator-(Vector2 left, const T& right)
	{
		left -= right;
		return left;
	}
	friend Vector2 operator*(Vector2 left, const T& right)
	{
		left *= right;
		return left;
	}
	friend Vector2 operator/(Vector2 left, const T& right)
	{
		left /= right;
		return left;
	}

	// Binary vector operators
	template <typename U>
	friend Vector2 operator+(Vector2 left, const Vector2<U>& right)
	{
		left += right;
		return left;
	}
	template <typename U>
	friend Vector2 operator-(Vector2 left, const Vector2<U>& right)
	{
		left -= right;
		return left;
	}
	template <typename U>
	friend Vector2 operator*(Vector2 left, const Vector2<U>& right)
	{
		left *= right;
		return left;
	}
	template <typename U>
	friend Vector2 operator/(Vector2 left, const Vector2<U>& right)
	{
		left /= right;
		return left;
	}

	// Static declarations
	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
};
}

template <typename T>
struct YAML::convert<oter::Vector2<T>>
{
public:
	static Node encode(const oter::Vector2<T>& right)
	{
		Node node;
		node["x"] = right.X;
		node["y"] = right.Y;
		return node;
	}

	static bool decode(const Node& node, oter::Vector2<T>& right)
	{
		if (node.IsSequence())
			return decode_sequence(node, right);
		if (node.IsMap())
			return decode_map(node, right);

		return false;
	}

private:
	static bool decode_sequence(const Node& node, oter::Vector2<T>& right)
	{
		if (!node.IsSequence() || node.size() != 2)
			return false;

		right.X = node[0].as<T>();
		right.Y = node[1].as<T>();
		return true;
	}
	static bool decode_map(const Node& node, oter::Vector2<T>& right)
	{
		if (!node.IsMap() || node.size() != 2)
			return false;

		right.X = node["x"].as<T>();
		right.Y = node["y"].as<T>();
		return true;
	}
};

#endif
