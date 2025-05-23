#ifdef COMMONLIB_USE_DLL
#ifdef COMMONLIB_BUILDING_PROJECT
#define COMMONLIB_API __declspec(dllexport)
#else
#define COMMONLIB_API __declspec(dllimport)
#endif
#else
#define COMMONLIB_API
#endif
