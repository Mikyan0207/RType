#pragma once
#include <exception>
#include <string>
#include <utility>
#include <ostream>

#include <RType.Common.hpp>

class RTYPECOMMON_API RTypeException final : public std::exception
{
public:
	RTypeException(std::string source, std::string message) : m_Source(std::move(source)), m_Message(std::move(message))
	{}

public:
	[[nodiscard]] const std::string& GetSource() const { return m_Source; }
	[[nodiscard]] const std::string& GetMessage() const { return m_Message; }

private:
	const std::string m_Source;
	const std::string m_Message;
};

inline std::ostream& operator<<(std::ostream& os, const RTypeException& ex)
{
    os << ex.GetSource() << ": " << ex.GetMessage();

    return os;
}

inline std::ostream& operator<<(std::ostream& os, RTypeException& ex)
{
	os << ex.GetSource() << ": " << ex.GetMessage();

	return os;
}