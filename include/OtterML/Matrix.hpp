#ifndef OTER_MATRIX_HPP
#define OTER_MATRIX_HPP

//#include <spdlog/spdlog.h>
//#include <spdlog/fmt/ostr.h>
//#include <spdlog/sinks/stdout_sinks.h>

#include <OtterML/Common.hpp>

namespace oter
{

template <typename T, unsigned Ts>
class Vector;

template <typename T, unsigned Tx, unsigned Ty>
class Matrix
{
public:
	Matrix();
	explicit Matrix(bool identity);
	explicit Matrix(const std::array<T, Tx * Ty>& data);
	explicit Matrix(const std::array<std::array<T, Tx>, Ty>& rows);
	explicit Matrix(T scalar);

	[[nodiscard]] const std::array<std::array<T, Tx>, Ty>& GetData() const;
	[[nodiscard]] const std::array<T, Tx>& GetRow(u32 row) const;
	[[nodiscard]] T GetValue(u32 row, u32 column) const;

	void SetData(const std::array<std::array<T, Tx>, Ty>& data);
	void SetRow(u32 row, const std::array<T, Tx>& data);
	void SetValue(u32 row, u32 column, T data);

	[[nodiscard]] Matrix GetInverse() const;

	[[nodiscard]] bool operator==(const Matrix& right) const;

	// Member operators
	// Unary operators
	Matrix operator-(const Matrix& right);

	// Binary scalar operators
	Matrix& operator+=(const T& right);
	Matrix& operator-=(const T& right);
	Matrix& operator*=(const T& right);
	Matrix& operator/=(const T& right);

	// Binary vector operators
	Matrix& operator*=(const Vector<T, Tx>& right);

	// Binary matrix operators
	Matrix& operator+=(const Matrix& right);
	Matrix& operator-=(const Matrix& right);
	Matrix& operator*=(const Matrix& right);
	Matrix& operator/=(const Matrix& right);

	// Friend operators
	// Binary scalar operators
	friend Matrix operator+(const Matrix& left, const T& right)
	{
		throw;
	}
	friend Matrix operator-(const Matrix& left, const T& right)
	{
		throw;
	}
	friend Matrix operator*(const Matrix& left, const T& right)
	{
		throw;
	}
	friend Matrix operator/(const Matrix& left, const T& right)
	{
		throw;
	}

	// Binary vector operators
	friend Matrix operator*(const Matrix& left, const Vector<T, Tx>& right)
	{
		throw;
	}

	// Binary matrix operators
	friend Matrix operator+(const Matrix& left, const Matrix& right)
	{
		throw;
	}
	friend Matrix operator-(const Matrix& left, const Matrix& right)
	{
		throw;
	}
	friend Matrix operator*(const Matrix& left, const Matrix& right)
	{
		throw;
	}
	friend Matrix operator/(const Matrix& left, const Matrix& right)
	{
		throw;
	}

	// Static declarations
	static const Matrix Zero;
	static const Matrix IdentityMatrix;
private:
	std::array<std::array<T, Tx>, Ty> _data;

	// Function to get cofactor of A[p][q] in temp[][]. n is
	// current dimension of A[][]
	static void GetCofactor(const std::array<std::array<T, Tx>, Ty>& A, std::array<std::array<T, Tx>, Ty>& temp, i32 p, i32 q, i32 n)
	{
		i32 i = 0;
		i32 j = 0;

		// Looping for each element of the matrix
		for (i32 row = 0; row < n; row++)
			for (i32 col = 0; col < n; col++)
			{
				//  Copying into temporary matrix only those
				//  element which are not in given row and
				//  column
				if (row == p || col == q) continue;

				temp[i][j] = A[row][col];
				j++;

				// Row is filled, so increase row index and
				// reset col index
				if (j != n - 1) continue;

				j = 0;
				i++;
			}
	}

	// Recursive function for finding determinant of matrix
	// n is current dimension of A[][].
	static T GetDeterminant(std::array<std::array<T, Tx>, Ty> A, i32 n)
	{
		T D = 0; // Initialize result

		//  Base case : if matrix contains single element
		if (n == 1)
			return A[0][0];

		std::array<std::array<T, Tx>, Ty> temp; // To store cofactors

		i32 sign = 1; // To store sign multiplier

		// Iterate for each element of first row
		for (i32 f = 0; f < n; f++)
		{
			// Getting Cofactor of A[0][f]
			GetCofactor(A, temp, 0, f, n);
			D += sign * A[0][f] * GetDeterminant(temp, n - 1);

			// terms are to be added with alternate sign
			sign = -sign;
		}

		return D;
	}

	// Function to get adjoint of A[N][N] in adj[N][N].
	std::array<std::array<T, Tx>, Ty> GetAdjoint() const
	{
		std::array<std::array<T, Tx>, Ty> adj;
		if constexpr (Tx == 1)
		{
			adj[0][0] = 1;
			return adj;
		}

		// temp is used to store cofactors of A[][]
		i32 sign = 1;
		std::array<std::array<T, Tx>, Ty> temp;

		for (i32 i = 0; i < Ty; i++)
		{
			for (i32 j = 0; j < Tx; j++) {
				// Get cofactor of A[i][j]
				GetCofactor(this->_data, temp, i, j, Tx);

				// sign of adj[j][i] positive if sum of row
				// and column indexes is even.
				sign = ((i + j) % 2 == 0) ? 1 : -1;

				// Interchanging rows and columns to get the
				// transpose of the cofactor matrix
				adj[j][i] = (sign) * (GetDeterminant(temp, Tx - 1));
			}
		}
		return adj;
	}
};

template <typename T, unsigned Tx, unsigned Ty>
Matrix<T, Tx, Ty>::Matrix() : Matrix(static_cast<T>(0)) {}

template <typename T, unsigned Tx, unsigned Ty>
Matrix<T, Tx, Ty>::Matrix(bool identity) : Matrix(static_cast<T>(0))
{
	if (!identity)
		return;

	#if Tx != Ty
	{
		spdlog::error("Cannot create identity matrix for non-square matrix");
		return;
	}
	#endif

	for (u32 i = 0; i < Tx; i++)
	{
		this->_data[i][i] = static_cast<T>(1);
	}
}

template <typename T, unsigned Tx, unsigned Ty>
Matrix<T, Tx, Ty>::Matrix(const std::array<T, Tx * Ty>& data) : _data()
{
	for (u32 y = 0; y < Ty; y++)
	{
		for (u32 x = 0; x < Tx; x++)
		{
			this->_data[y][x] = data[y * Tx + x];
		}
	}
}

template <typename T, unsigned Tx, unsigned Ty>
Matrix<T, Tx, Ty>::Matrix(const std::array<std::array<T, Tx>, Ty>& rows) : _data(rows) {}

template <typename T, unsigned Tx, unsigned Ty>
Matrix<T, Tx, Ty>::Matrix(const T scalar)
{
	for (u32 y = 0; y < Ty; y++)
	{
		for (u32 x = 0; x < Tx; x++)
		{
			this->_data[y][x] = scalar;
		}
	}
}

template <typename T, unsigned Tx, unsigned Ty>
const std::array<std::array<T, Tx>, Ty>& Matrix<T, Tx, Ty>::GetData() const
{
	return this->_data;
}
template <typename T, unsigned Tx, unsigned Ty>
const std::array<T, Tx>& Matrix<T, Tx, Ty>::GetRow(u32 row) const
{
	return this->_data[row];
}
template <typename T, unsigned Tx, unsigned Ty>
T Matrix<T, Tx, Ty>::GetValue(u32 row, u32 column) const
{
	return this->_data[row][column];
}

template <typename T, unsigned Tx, unsigned Ty>
void Matrix<T, Tx, Ty>::SetData(const std::array<std::array<T, Tx>, Ty>& data)
{
	this->_data = data;
}

template <typename T, unsigned Tx, unsigned Ty>
void Matrix<T, Tx, Ty>::SetRow(u32 row, const std::array<T, Tx>& data)
{
	this->_data[row] = data;
}

template <typename T, unsigned Tx, unsigned Ty>
void Matrix<T, Tx, Ty>::SetValue(u32 row, u32 column, T data)
{
	this->_data[row][column] = data;
}

template<typename T, unsigned Tx, unsigned Ty>
Matrix<T, Tx, Ty> Matrix<T, Tx, Ty>::GetInverse() const
{
	static_assert(Tx == Ty);

	// Find determinant of A[][]
	T det = GetDeterminant(this->_data, Tx);
	if (det == 0)
		return Matrix::Zero;

	// Find adjoint
	std::array<std::array<T, Tx>, Ty> adj = this->GetAdjoint();

	// Find Inverse using formula "inverse(A) =
	// adj(A)/det(A)"
	Matrix<T, Tx, Ty> inverse;
	for (i32 i = 0; i < Ty; i++)
	{
		for (i32 j = 0; j < Tx; j++)
		{
			inverse.SetValue(i, j, adj[i][j] / f32(det));
		}
	}

	return inverse;
}

template <typename T, unsigned Tx, unsigned Ty>
const Matrix<T, Tx, Ty> Matrix<T, Tx, Ty>::Zero(static_cast<T>(0));
template <typename T, unsigned Tx, unsigned Ty>
const Matrix<T, Tx, Ty> Matrix<T, Tx, Ty>::IdentityMatrix(true);

}

/*
template <typename T, unsigned Tx, unsigned Ty>
inline std::ostream& operator <<(std::ostream& os, const oter::Matrix<T, Tx, Ty>& mat)
{
	std::ostringstream str;
	for (oter::u32 y = 0; y < Ty; y++)
	{
		os << "\n\t";
		for (oter::u32 x = 0; x < Tx; x++)
		{
			os << mat.GetValue(y, x) << " ";
		}
	}
	return os;
}
*/

#endif
