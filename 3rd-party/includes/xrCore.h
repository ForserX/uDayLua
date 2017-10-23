void __cdecl Log(const char*);
#ifdef XRAY15
typedef void	( * LogCallback)	(const char* string);
LogCallback	__cdecl	SetLogCB(LogCallback cb);
#else
void __cdecl SetLogCB(void (__cdecl *)(const char *));
#endif