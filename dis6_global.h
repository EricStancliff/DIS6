#ifdef DIS6_LIBRARY
#ifdef __GNUC__
#define DIS6_EXPORT __attribute__ ((visibility ("default")))
#elif MSVC
#define DIS6_EXPORT __declspec(dllexport)
#endif
#else
#ifdef __GNUC__
#define DIS6_EXPORT __attribute__ ((visibility ("default")))
#elif MSVC
#define DIS6_EXPORT __declspec(dllimport)
#endif
#endif
