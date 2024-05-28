#define ITERATION 10
#define MATRIX_SIZE 4

#ifdef u8
  typedef uint8_t type;
#elif u16
  typedef uint16_t type;
#elif u32
  typedef uint32_t type;
#elif u64
  typedef uint64_t type;
#elif i8
  typedef int8_t type;
#elif i16
  typedef int16_t type;
#elif i32
  typedef int32_t type;
#else
  typedef int64_t type;
#endif
