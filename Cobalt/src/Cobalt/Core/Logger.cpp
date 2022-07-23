#include "cbpch.h"
#include "Logger.h"

// If on windows, enable console colors
#ifdef CB_PLATFORM_WINDOWS
	#define SET_CONSOLE_COLOR(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
#else
	#define SET_CONSOLE_COLOR(x)
#endif

namespace Cobalt {

	namespace Logger {

		// Window console colors
		enum WIN_FG_COLORS
		{
			FG_BLACK = 0,
			FG_BLUE = 1,
			FG_GREEN = 2,
			FG_CYAN = 3,
			FG_RED = 4,
			FG_MAGENTA = 5,
			FG_BROWN = 6,
			FG_WHITE = 7,
			FG_GRAY = 8,
			FG_LIGHTBLUE = 9,
			FG_LIGHTGREEN = 10,
			FG_LIGHTCYAN = 11,
			FG_LIGHTRED = 12,
			FG_PINK = 13,
			FG_YELLOW = 14,
			FG_LIGHTWHITE = 15
		};

		// Map containing all console color codes
		std::unordered_map<unsigned int, unsigned int> log_colors = { {Core + Trace, FG_GREEN},
																		{Core + Info, FG_WHITE},
																		{Core + Warn, FG_YELLOW},
																		{Core + Error, FG_LIGHTRED},
																		{Core + Fatal, FG_RED},
																		{App + Trace, FG_GREEN},
																		{App + Info, FG_WHITE},
																		{App + Warn, FG_YELLOW},
																		{App + Error, FG_LIGHTRED},
																		{App + Fatal, FG_RED} };

		// Prints out log message
		void printMessage(unsigned int type, std::string m)
		{
			// Set the text color
			SET_CONSOLE_COLOR(log_colors[type]);

			// Get the current time
			time_t now = time(0);
			struct tm time_info;
			localtime_s(&time_info, &now);

			// Print the time
			if (time_info.tm_hour < 10)
				std::cout << "[0" << time_info.tm_hour << ":";
			else
				std::cout << "[" << time_info.tm_hour << ":";
			if (time_info.tm_min < 10)
				std::cout << "0" << time_info.tm_min << ":";
			else
				std::cout << time_info.tm_min << ":";
			if (time_info.tm_sec < 10)
				std::cout << "0" << time_info.tm_sec << "] ";
			else
				std::cout << time_info.tm_sec << "] ";

			// Print the source
			if ((type & 0xf0) == Core)
				std::cout << "CORE: ";
			else if ((type & 0xf0) == App)
				std::cout << "APP: ";

			// Print the message
			std::cout << m << std::endl;

			// Reset the text color
			SET_CONSOLE_COLOR(FG_WHITE);
		}

		// Final format loop, move to printing
		void formatMessage(int count, unsigned int type, std::string m)
		{
			printMessage(type, m);
		}

	}

}