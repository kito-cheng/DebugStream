#ifndef __DEBUGSTREAM_MANAGER_HPP__
#define __DEBUGSTREAM_MANAGER_HPP__

#include <map>
#include <string>

class DebugStream;

class DebugStreamManager {
public:
  typedef std::multimap<std::string, DebugStream*> Map;
  static DebugStreamManager &instance();
  void add(DebugStream *ds);
  void remove(DebugStream *ds);
  void set(const std::string &tag, int level);
private:
  DebugStreamManager();
  Map _map;
};

#endif
