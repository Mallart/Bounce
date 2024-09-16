#pragma once
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>

#pragma warning(disable : 4996)

namespace Bounce
{
	namespace IO
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
		typedef char ResourceFlag;
		// All resources flags
		enum Resource
		{
			// Cannot access resource.
			AVAILABLE		= 0b001,
			UNAVAILABLE		= 0b000,
			FILE			= 0b010,
			DIRECTORY		= 0b000,
			// Not supported at the moment
			DISTANT			= 0b100,
			LOCAL			= 0b000,
		};

		// Returns the resource flags for this resource path.
		// If null (0), resource is either unavailable or nonexistent.
		static ResourceFlag LookUpResource(::std::string Uri)
		{
			ResourceFlag _rf = 0;
			_iobuf* file = fopen(Uri.c_str(), "r");
			struct stat info;
			// Unavailable resource.
			if (!stat(Uri.c_str(), &info))
				return _rf;
			_rf = AVAILABLE;
			// Uri is a directory
			if (info.st_mode & S_IFDIR)
				return _rf | DIRECTORY;
			return _rf | FILE;
		}
	}
}