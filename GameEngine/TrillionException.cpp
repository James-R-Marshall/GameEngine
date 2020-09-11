#include "TrillionException.h"
#include <sstream>

TrillionException::TrillionException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* TrillionException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl <<
		GetOrginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* TrillionException::GetType() const noexcept
{
	return "Trillion Exception";
}

int TrillionException::Getline() const noexcept
{
	return line;
}

const std::string& TrillionException::GetFile() const noexcept
{
	return file;
}

std::string TrillionException::GetOrginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
