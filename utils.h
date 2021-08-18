//  2006-2008 (c) Viva64.com Team
//  2008-2020 (c) OOO "Program Verification Systems"
//  2020-2021 (c) PVS-Studio LLC

#ifndef UTILS_H
#define UTILS_H
#include <utility>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

namespace PlogConverter
{

class FilesystemException : public std::runtime_error
{
public:
  explicit FilesystemException(const std::string& msg) : std::runtime_error(msg) {}
};

std::pair<std::string, std::string> SplitKeyValue(const std::string& srcRaw);
std::string Trim(const std::string& src);
void Replace(std::string& src, const std::string& toReplace, const std::string& replacer);
void ReplaceAll(std::string& src, const std::string& toReplace, const std::string& replacer);
std::string EscapeHtml(const std::string& src);
std::string ToLower(const std::string& src);

std::string LeftPad(const std::string &str, size_t size, char ch = ' ');

void UTF8toANSI(std::string& source);
void ANSItoUTF8(std::string& source);

bool StartsWith(const std::string& src, const std::string& prefix);
bool EndsWith(const std::string& src, const std::string& suffix);

template <typename OutIt, typename Fn>
void Split(const std::string& src, const std::string& delim, OutIt it, Fn fn)
{
  if (src.empty() || delim.empty())
  {
    return;
  }

  std::string::size_type pos = 0;
  std::string::size_type next_pos;
  do
  {
    next_pos = src.find(delim, pos);
    std::string::size_type pieceLength = next_pos - pos;
    *it = fn(src.substr(pos, pieceLength));
    ++it;
    pos = next_pos + delim.size();
  } while (next_pos != std::string::npos);
}

template <typename OutIt>
void Split(const std::string& src, const std::string& delim, OutIt it)
{
  Split(src, delim, it, [](std::string &&s)->std::string&& { return std::move(s); });
}

inline std::vector<std::string> Split(std::string text, std::string separator)
{
  size_t pos = 0;
  std::vector<std::string> tokens;
  while ((pos = text.find(separator)) != std::string::npos)
  {
    tokens.push_back(Trim(text.substr(0, pos)));
    text.erase(0, pos + separator.length());
  }
  tokens.push_back(Trim(text));
  return tokens;
}

template <typename Range, typename Map>
std::string Join(Range &&range, Map fn, std::string delimiter)
{
  std::string res;
  auto it = std::begin(range);
  auto end = std::end(range);

  if (it == end)
  {
    return res;
  }

  res = fn(*it);

  for (++it; it != end; ++it)
  {
    res.append(delimiter.begin(), delimiter.end());
    res += fn(*it);
  }

  return res;
}

template <typename Range>
std::string Join(Range &&range, std::string delimiter = " ")
{
  return Join(range, [](auto v) { return v; }, delimiter);
}

unsigned ParseUint(const std::string &str);

std::ifstream OpenFile(const std::string &path);
std::string Expand(const std::string &path);
std::string FileBaseName(const std::string &filePath);
std::string FileStem(const std::string &path);
std::string FileExtension(const std::string &path);

bool IsDirectory(const std::string &path);
bool MakeDirectory(const std::string &path);
bool Exists(const std::string &path);

template <typename To, typename From, typename Deleter>
std::unique_ptr<To, Deleter> dynamic_unique_cast(std::unique_ptr<From, Deleter> &&p) noexcept
{
  if (auto cast = dynamic_cast<To *>(p.get()))
  {
    std::unique_ptr<To, Deleter> result { cast, std::move(p.get_deleter()) };
    p.release();
    return result;
  }

  return {};
}

}

#endif // UTILS_H
