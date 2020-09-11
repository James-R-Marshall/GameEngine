#pragma once
#include <exception>
#include <string>
class TrillionException :
    public std::exception
{
public:
    TrillionException(int line, const char* file) noexcept;
    const char* what() const noexcept override;
    virtual const char* GetType() const noexcept;
    int Getline() const noexcept;
    const std::string& GetFile() const noexcept;
    std::string GetOrginString() const noexcept;
private:
    int line;
    std::string file;
protected:
    mutable std::string whatBuffer;
};

