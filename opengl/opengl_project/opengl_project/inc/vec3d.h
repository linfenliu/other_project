#ifndef FLEW_VEC3d_H
#define FLEW_VEC3d_H

#include <string>

template<typename T>
struct InitValue
{
	T value = T();
};

template<>
struct InitValue<double>
{
	double value = 0.0;
};

template<>
struct InitValue<float>
{
	float value = 0.0;
};

template<typename Type, size_t N>
class vec
{
public:

	vec()
	{
		for (size_t i = 0; i < N; ++i)
		{
			data[i] = 0;
		}
	}

	vec(Type d)
	{
		data[0] = d;
	}

	vec(Type d0, Type d1)
	{
		data[0] = d0;
		data[1] = d1;
	}

	vec(Type d0, Type d1, Type d2)
	{
		data[0] = d0;
		data[1] = d1;
		data[2] = d2;
	}

	vec(Type d0, Type d1, Type d2, Type d3)
	{
		data[0] = d0;
		data[1] = d1;
		data[2] = d2;
		data[3] = d3;
	}

	template<typename OtherType>
	vec(const vec<OtherType, N>& rhs)
	{
		for (size_t i = 0; i < N; ++i)
		{
			data[i] = float(rhs.data[i]);
		}
	}


	Type& operator[](size_t n)
	{
		return data[n];
	}

	const Type& operator[](size_t n) const
	{
		return data[n];
	}

	Type data[N];
};

typedef vec<float, 2> vec2f;
typedef vec<float, 3> vec3f;

typedef vec<double, 2> vec2d;
typedef vec<double, 3> vec3d;

typedef vec<std::string, 2> vec2s;
typedef vec<std::string, 3> vec3s;





#endif