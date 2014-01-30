#include "DebugStreamManager.hpp"
#include "DebugStream.hpp"

DebugStreamManager &DebugStreamManager::instance()
{
  static DebugStreamManager dsm;
  return dsm;
}

DebugStreamManager::DebugStreamManager()
{
}

void DebugStreamManager::add(DebugStream *ds)
{
  _map.insert(std::make_pair(ds->getTag(), ds));
}

void DebugStreamManager::remove(DebugStream *ds)
{
  const std::string &tag = ds->getTag();
  Map::iterator begin = _map.lower_bound(tag);
  Map::iterator end = _map.upper_bound(tag);
  for (Map::iterator itr = begin;itr != end;++itr) {
    if (ds == itr->second) {
      _map.erase(itr);
      return;
    }
  }
}

void DebugStreamManager::set(const std::string &tag, int level)
{
  Map::iterator begin = _map.lower_bound(tag);
  Map::iterator end = _map.upper_bound(tag);
  for (Map::iterator itr = begin;itr != end;++itr) {
    DebugStream *ds = itr->second;
    ds->setLevel(level);
  }
}
