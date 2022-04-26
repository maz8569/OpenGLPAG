#pragma once

#include <cstdint>
#include <cstddef>
#include <cinttypes>
#include <cstdlib>
#include <vector>
#include <glm/glm.hpp>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t usize;
typedef intmax_t ssize;

typedef float f32;
typedef double f64;

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 1
#define CHUNK_SIZE_Z 16


struct i8Vec3
{
	uint8_t x;
	uint8_t y;
	uint8_t z;

	i8Vec3 operator=(const glm::vec3& vec)
	{
		x = floor(vec.x);
		y = floor(vec.y);
		z = floor(vec.z);

		return *this;
	}
};

struct i16Vec2
{
	uint16_t x;
	uint16_t y;
};


struct Vertex
{
	i8Vec3 position;
	uint8_t lighting_level;
	i16Vec2 texture_coords;
	uint8_t block_face_lighting;
};