#include "slogger.h"

SLogger::SLogger() { openLogFile("logs.txt"); }

SLogger::~SLogger() { closeLogFile(); }

SLogger &SLogger::shared() {
  static SLogger instance;
  return instance;
}

void SLogger::logMsg(std::string_view message, const char *file, int line,
                    const char *function) {
  std::string timestamp = getTimestamp();

#if defined(DEBUG) || defined(_DEBUG)
  std::cout << "[" << timestamp << "] " << message << std::endl;
#endif

  if (!fileStream.is_open())
    return;

  fileStream << "[" << timestamp << "] | "
             << "File: " << file << "(" << line << ") `" << function
             << "`: " << message << std::endl;
  fileStream.flush();
}

void SLogger::openLogFile(const std::string &filename) {
  if (fileStream.is_open())
    return;
  fileStream.open(filename, std::ios::out | std::ios::app);
}

void SLogger::closeLogFile() {
  if (fileStream.is_open())
    fileStream.close();
}

std::string SLogger::getTimestamp() {
  auto now = std::chrono::system_clock::now();
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
  std::string timestamp = std::ctime(&currentTime);

  timestamp.pop_back();

  return timestamp;
}