#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <string_view>

#define log(message)                                                           \
  SLogger::shared().logMsg(message, __FILE__, __LINE__, __func__)

class SLogger {
public:
  static SLogger &shared();

  void logMsg(std::string_view message, const char *file, int line,
              const char *function);

private:
  SLogger();
  ~SLogger();
  SLogger(const SLogger &) = delete;

  SLogger &operator=(const SLogger &) = delete;

  void openLogFile(const std::string &filename);
  void closeLogFile();
  std::string getTimestamp();

  std::ofstream fileStream;
};