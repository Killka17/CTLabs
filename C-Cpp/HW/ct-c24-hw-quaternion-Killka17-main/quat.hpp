#pragma once
#include <cmath>
#include <iostream>
template< typename T >
struct matrix_t
{
	T data[16];
};

template< typename T >
struct vector3_t
{
	T x, y, z;
};

template< typename T >
class Quat
{
  public:
	const T* data() const { return m_value; };

	matrix_t< T > rotation_matrix() const
	{
		vector3_t< T > v1 = apply({ 1, 0, 0 });
		vector3_t< T > v2 = apply({ 0, 1, 0 });
		vector3_t< T > v3 = apply({ 0, 0, 1 });
		return matrix_t< T >{ v1.x, v1.y, v1.z, 0, v2.x, v2.y, v2.z, 0, v3.x, v3.y, v3.z, 0, 0, 0, 0, 1 };
	};

	matrix_t< T > matrix() const
	{
		return matrix_t< T >{
			m_value[3], -m_value[0], -m_value[1], -m_value[2], m_value[0], m_value[3],	-m_value[2], m_value[1],
			m_value[1], m_value[2],	 m_value[3],  -m_value[0], m_value[2], -m_value[1], m_value[0],	 m_value[3]
		};
	};

	T angle(bool degrees = true) const
	{
		T radianAngle = 2 * std::acos(m_value[3]);
		if (!degrees)
			return radianAngle * (180.0 / M_PI);

		return radianAngle;
	}

	vector3_t< T > apply(const vector3_t< T >& vec) const
	{
		T n = static_cast< T >(*this);
		if (n == T(0.0))
			throw std::runtime_error("division by zero");
		Quat< T > norm_res(m_value[3] / n, m_value[0] / n, m_value[1] / n, m_value[2] / n);
		Quat< T > a(0, vec.x, vec.y, vec.z);
		Quat< T > b = ~(norm_res);
		Quat< T > res = norm_res * a * b;

		return { res.m_value[0], res.m_value[1], res.m_value[2] };
	}

	Quat(T x = 0, T y = 0, T z = 0, T w = 0) : m_value{ y, z, w, x } {};
	Quat(T angle, bool rad, vector3_t< T > vect)
	{
		if (!rad)
			angle = angle * T(M_PI) / T(180.0);
		T half_angle = angle / 2;
		T s = std::sin(half_angle);
		T n = std::sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
		m_value[0] = s * vect.x / n;
		m_value[1] = s * vect.y / n;
		m_value[2] = s * vect.z / n;
		m_value[3] = std::cos(half_angle);
	};

	Quat operator+(const Quat& second) const
	{
		Quat result = *this;
		result += second;
		return result;
	}

	Quat& operator+=(const Quat& second)
	{
		for (int i = 0; i < 4; i++)
			m_value[i] += second.m_value[i];
		return *this;
	}

	Quat operator-(const Quat& second) const
	{
		Quat result = *this;
		result -= second;
		return result;
	}

	Quat& operator-=(const Quat& second)
	{
		for (int i = 0; i < 4; i++)
			m_value[i] -= second.m_value[i];
		return *this;
	}

	Quat operator*(const Quat& second) const
	{
		return Quat(
			m_value[3] * second.m_value[3] - m_value[0] * second.m_value[0] - m_value[1] * second.m_value[1] -
				m_value[2] * second.m_value[2],
			m_value[3] * second.m_value[0] + m_value[0] * second.m_value[3] + m_value[1] * second.m_value[2] -
				m_value[2] * second.m_value[1],
			m_value[3] * second.m_value[1] - m_value[0] * second.m_value[2] + m_value[1] * second.m_value[3] +
				m_value[2] * second.m_value[0],
			m_value[3] * second.m_value[2] + m_value[0] * second.m_value[1] - m_value[1] * second.m_value[0] +
				m_value[2] * second.m_value[3]);
	}

	Quat operator*(T scalar) const
	{
		return Quat(m_value[3] * scalar, m_value[0] * scalar, m_value[1] * scalar, m_value[2] * scalar);
	}

	Quat operator*(const vector3_t< T >& vec) const
	{
		Quat v(0, vec.x, vec.y, vec.z);
		return *this * v;
	}

	bool operator==(const Quat& second) const
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_value[i] != second.m_value[i])
				return false;
		}
		return true;
	}

	bool operator!=(const Quat& second) const { return !(*this == second); }

	Quat operator~() const { return Quat(m_value[3], -m_value[0], -m_value[1], -m_value[2]); }
	explicit operator T() const
	{
		return std::sqrt(m_value[0] * m_value[0] + m_value[1] * m_value[1] + m_value[2] * m_value[2] + m_value[3] * m_value[3]);
	}

  private:
	T m_value[4];
};
