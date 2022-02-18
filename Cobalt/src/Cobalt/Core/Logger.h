#pragma once

#include <iostream>

// Core log macros
#define CB_CORE_TRACE(s, ...)	::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::Core + Cobalt::LogCategory::Trace, s, __VA_ARGS__)
#define CB_CORE_INFO(s, ...)	::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::Core + Cobalt::LogCategory::Info, s, __VA_ARGS__)
#define CB_CORE_WARN(s, ...)	::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::Core + Cobalt::LogCategory::Warn, s, __VA_ARGS__)
#define CB_CORE_ERROR(s, ...)	::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::Core + Cobalt::LogCategory::Error, s, __VA_ARGS__)
#define CB_CORE_FATAL(s, ...)	::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::Core + Cobalt::LogCategory::Fatal, s, __VA_ARGS__)

// Client log macros
#define CB_TRACE(s, ...)		::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::App + Cobalt::LogCategory::Trace, s, __VA_ARGS__)
#define CB_INFO(s, ...)			::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::App + Cobalt::LogCategory::Info, s, __VA_ARGS__)
#define CB_WARN(s, ...)			::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::App + Cobalt::LogCategory::Warn, s, __VA_ARGS__)
#define CB_ERROR(s, ...)		::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::App + Cobalt::LogCategory::Error, s, __VA_ARGS__)
#define CB_FATAL(s, ...)		::Cobalt::Logger::formatMessage(0, Cobalt::LogSource::App + Cobalt::LogCategory::Fatal, s, __VA_ARGS__)

namespace Cobalt {

	// Log categories
	enum LogCategory
	{
		Trace = 0x1,
		Info = 0x2,
		Warn = 0x3,
		Error = 0x4,
		Fatal = 0x5
	};

	// Log sources
	enum LogSource
	{
		Core = 0x1 << 4,
		App = 0x2 << 4
	};

	namespace Logger {
		// Add variables into string.
		template <typename T, typename... Types>
		void formatMessage(int count, unsigned int type, std::string m, const T& arg1, const Types&... arg2)
		{
			// Go through and find all input spots
			std::stringstream ss;
			ss << "{" << count << "}";
			size_t index = m.find(ss.str());
			// Print error if more argument exist then message slots available
			if (index == std::string::npos)
			{
				int prev_count = count + 1;
				count = 0;
				CB_CORE_ERROR("Logger missing argument {0} in string '{1}'!", prev_count, m);
				return;
			}

			// Insert variable into message
			std::stringstream ss2;
			ss2 << arg1;
			m.replace(index, ss.str().length(), ss2.str());

			// Move on to next value
			formatMessage(count + 1, type, m, arg2...);
		}

		// Final format loop, move to printing
		void formatMessage(int count, unsigned int type, std::string m);

	}

}
