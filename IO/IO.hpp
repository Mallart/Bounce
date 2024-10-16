#pragma once
#include <iostream>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>

#pragma warning(disable : 4996)

namespace Bounce::IO
{
	/*
		
		For instance, an available local file would look like:

		0000 0011

		A distant directory would look like:

		0000 0101

		And an unavailable resource isn't characterized by anything but its availability. Meaning any resource that's unavilable will be:

		0000 0000

	*/

	// first bit is 1 if resource is available, 2nd bit is 1 if resource is a file (0 if directory), and 3rd bit is proximity (0 if local, 1 if resource is distant).
	typedef uint8_t ResourceFlag;
	// All resources flags
	enum Resource
	{
		// Cannot access resource.
		R_AVAILABLE		= 0b001,
		R_UNAVAILABLE		= 0b000,
		R_FILE			= 0b010,
		R_DIRECTORY		= 0b000,
		// Not supported at the moment
		R_DISTANT			= 0b100,
		R_LOCAL			= 0b000,
	};

	// Returns the resource flags for this resource path.
	// If null (0), resource is either unavailable or nonexistent.
	static ResourceFlag LookUpResource(::std::string Uri)
	{
		ResourceFlag _rf = 0;
		FILE* file = fopen(Uri.c_str(), "r");
		struct stat info;
		// Unavailable resource.
		if (!stat(Uri.c_str(), &info))
			return _rf;
		_rf = R_AVAILABLE;
		// Uri is a directory
		if (info.st_mode & S_IFDIR)
			return _rf | R_DIRECTORY;
		return _rf | R_FILE;
	}

	static void Log(::std::string _uri, ::std::string _message)
	{
		FILE* f;
		if (f = fopen(_uri.c_str(), "a"))
		{
			fwrite(_message.c_str(), sizeof(char), _message.size(), f);
			fclose(f);
		}
	}
}