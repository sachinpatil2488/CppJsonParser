#ifdef _CPP_EXPORT_
#define _EXPORT_ __declspec(dllexport)
#else
#define _EXPORT_ __declspec(dllimport)
#endif