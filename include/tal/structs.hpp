#pragma once

namespace tal
{
	typedef struct
	{
		const char *const *dataDirs;
		const char *dataHome;
	} XDGConfigInfo;

	typedef struct
	{
		const char *Name, *Exec;
	} DesktopFile;
}
