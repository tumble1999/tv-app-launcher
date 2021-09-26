#include <tal/xdg.hpp>

#include <basedir_fs.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Parse DEsktop File
#include <fstream>
#include <string>
#include <algorithm>

// Debug
#include <iostream>

#define STARTS_WITH(A, B) strncmp(B, A, strlen(B)) == 0
#define GET_VALUE(A, K) A + strlen(K)

xdgHandle *xdg = NULL;

xdgHandle *tal_xdg_get_handle()
{
	if (!xdg)
		//Cache the handle incase it already exists
		xdg = xdgInitHandle(NULL);
	return xdg;
}

tal::XDGConfigInfo tal::xdg_config_info()
{
	xdgHandle *xdg = tal_xdg_get_handle();
	tal::XDGConfigInfo info = {
		// Folders that have an applications folder containing '.desktop' files like /usr/share
		xdgDataDirectories(xdg),
		// Gets the folder in the users home directory that has the applications folder containing '.desktop' files
		xdgDataHome(xdg)};
	return info;
}

void tal::xdg_clean()
{
	if (xdg)
		xdgWipeHandle(xdg);
}

tal::DesktopFile tal::xdg_parse_desktop_file(const char *path)
{
	tal::DesktopFile desktopFile;
	bool reading;

	char *line = NULL;
	char *value;

	size_t length = 0;
	size_t size = 0;
	size_t new_size = 0;
	size_t new_length = 0;

	FILE *file = fopen(path, "r");
	if (file)
	{
		while (getline(&line, &length, file) != -1)
		{
			if (reading == true)
			{
				//Stop reading when a new section is releached
				if (line[0] == '[')
				{
					reading = false;
					break;
				}
				// Ignore lines that start with '#' because they could be commenst but I'm not sure
				if (line[0] == '#')
					continue;
				//The -1 is to remove the '\n'
				length = strlen(line) - 1;
				if (STARTS_WITH(line, "Name="))
				{
					new_length = length - strlen("Name=");
					value = (char *)malloc(new_length);
					strncpy(value, GET_VALUE(line, "Name="), new_length);
					desktopFile.Name = value;
					std::cout << "Name: " << desktopFile.Name << "\n";
				}
				if (STARTS_WITH(line, "Exec="))
				{
					new_length = length - strlen("Exec=");
					value = (char *)malloc(new_length);
					strncpy(value, GET_VALUE(line, "Exec="), new_length);
					desktopFile.Exec = value;
					std::cout << "Exec: " << desktopFile.Exec << "\n";
				}
			}
			// Only start reading when the line containing "[Desktop Entry]" is reached
			else if (STARTS_WITH(line, "[Desktop Entry]"))
			{
				printf("File: %s\n", path);
				reading = true;
			}
		}

		fclose(file);
	}
	return desktopFile;
}
