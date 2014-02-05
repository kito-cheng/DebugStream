#ifndef __DEBUGSTREAM_HPP__
#define __DEBUGSTREAM_HPP__

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdarg>

class DebugStream {
  public:
    enum {
      MAX_BUFFER_SIZE = 1024,
      VERBOSE = 4,
      DEBUG = 3,
      INFO = 2,
      WARNING = 1,
      ERROR = 0
    };
    class DSAgent{
      public:
        DSAgent(bool out, const std::string &tag, std::ostream *os)
          : _out(out)
          , _tag(tag)
          , _os(os){};
        template<class T>
        DSAgent& operator<<(const T &o) {
          if(_out) *_os << _tag << o;
          _tag = "";
          return *this;
        }
        DSAgent& operator<< (std::ostream& ( *pf )(std::ostream&)) {
          if(_out) *_os << pf;
          return *this;
        };
        DSAgent& operator<< (std::ios& ( *pf )(std::ios&)) {
          if(_out) *_os << pf;
          return *this;
        };
        DSAgent& operator<< (std::ios_base& ( *pf )(std::ios_base&)) {
          if(_out) *_os << pf;
          return *this;
        };
        int printf(const char *fmt, ...)
#ifdef __GNUC__
          __attribute__((format(printf, 2, 3)))
             /* 1 -> this pointer
              * 2 -> format string ,
              * 3 -> args
              */
#endif
        {
          if(!_out) return 0;
          *_os << _tag;
          _tag = "";
          char buf[MAX_BUFFER_SIZE];
          va_list args;
          va_start (args, fmt);
          int ret = std::vsprintf (buf, fmt, args);
          if (ret>MAX_BUFFER_SIZE) {
            char *long_buf = new char[ret];
            ret = std::vsprintf (long_buf, fmt, args);
            *_os << long_buf;
            delete long_buf;
          } else {
            *_os << buf;
          }
          va_end (args);
          return ret;
        }
      private:
        bool _out;
        std::string _tag;
        std::ostream *_os;
    };
    DebugStream(const std::string &tag = "",
                int debugLevel=0,
                std::ostream *os = &std::cerr);
    ~DebugStream();
    DSAgent debug() {
      return DSAgent(DEBUG <= _debugLevel, _ptag, _os);
    }
    DSAgent verbose() {
      return DSAgent(VERBOSE <= _debugLevel, _ptag, _os);
    }
    DSAgent info() {
      return DSAgent(INFO <= _debugLevel, _ptag, _os);
    }
    DSAgent warning() {
      return DSAgent(WARNING <= _debugLevel, _ptag, _os);
    }
    DSAgent error() {
      return DSAgent(ERROR <= _debugLevel, _ptag, _os);
    }
    DSAgent operator [](int msgLevel) {
      return DSAgent(msgLevel <= _debugLevel, _ptag, _os);
    }
    void setLevel(int l){_debugLevel = l;}
    int getLevel(){return _debugLevel;}
    bool verbose(int v){return v<=_debugLevel;}
    std::streamsize precision ( std::streamsize prec ) {
      return _os->precision(prec);
    }
    std::streamsize precision ( ) const{return _os->precision();}
    std::streamsize width ( ) const{return _os->width();}
    std::streamsize width ( std::streamsize wide ){return _os->width(wide);}
    std::ios_base::fmtflags setf ( std::ios_base::fmtflags fmtfl ) {
      return _os->setf(fmtfl);
    }
    std::ios_base::fmtflags setf ( std::ios_base::fmtflags fmtfl,
                                   std::ios_base::fmtflags mask ){
      return _os->setf(fmtfl, mask);
    }

    const std::string &getTag() const {return _tag;}
  private:
    std::ostream *_os;
    std::string _tag;
    std::string _ptag;
    int _debugLevel;
};

#endif

