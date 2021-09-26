#pragma once
#include <tal/structs.hpp>

namespace tal
{
	XDGConfigInfo xdg_config_info();
	void xdg_clean();

	DesktopFile xdg_parse_desktop_file(const char *path);
}