#include "DebugStream.hpp"
#include "DebugStreamManager.hpp"
DebugStream::DebugStream(const std::string &tag,
                         int debugLevel,
                         std::ostream *os)
  :_os(os)
  ,_tag(tag)
  ,_ptag("["+tag+"] ")
  ,_debugLevel(debugLevel)
{
  DebugStreamManager::instance().add(this);
}

DebugStream::~DebugStream()
{
  DebugStreamManager::instance().remove(this);
}
