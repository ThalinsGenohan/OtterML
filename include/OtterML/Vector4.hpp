#ifndef OTER_VECTOR4_HPP
#define OTER_VECTOR4_HPP

//#include <glm/vec4.hpp>

namespace oter
{
template <typename T, unsigned Tx, unsigned Ty>
class Matrix;

template <typename T>
struct Vector4
{
public:
	T X = static_cast<T>(0);
	T Y = static_cast<T>(0);
	T Z = static_cast<T>(0);
	T W = static_cast<T>(0);

	// Constructors

	/**
	 * @brief Default constructor
	 *
	 * Creates a Vector4(0, 0, 0, 0)
	 */
	Vector4();

	/**
	 * @brief Construct a new Vector4 object from coordinates
	 *
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param z Z coordinate
	 * @param w W coordinate
	 */
	Vector4(T x, T y, T z, T w);

	/**
	 * @brief Construct a new Vector4 object
	 *
	 * @param scalar Scalar value for all coordinates
	 */
	explicit Vector4(T scalar);

	/**
	 * @brief Construct a new Vector4 object from a different Vector4
	 *
	 * Does not replace copy constructor
	 * @param other Vector4 to convert
	 */
	template <typename U>
	explicit Vector4(const Vector4<U>& other);

	/**
	 * @brief Construct a new Vector4 object from a 1x4 Matrix
	 *
	 * @param matrix Matrix to convert
	 */
	explicit Vector4(const Matrix<T, 1, 4> matrix);

	/**
	 * @brief Copy constructor
	 */
	Vector4(const Vector4& other);

	[[nodiscard]] constexpr bool operator==(const Vector4& right) const;
};

}

#endif
