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
        DSAgent(bool out, std::ostream &os): _out(out), _os(os){};
        template<class T>
        const DSAgent& operator<<(const T &o) const{
          if(_out) _os << o;
          return *this;
        }
        const DSAgent& operator<< (std::ostream& ( *pf )(std::ostream&)) const{
          if(_out) _os << pf;
          return *this;
        };
        const DSAgent& operator<< (std::ios& ( *pf )(std::ios&)) const{
          if(_out) _os << pf;
          return *this;
        };
        const DSAgent& operator<< (std::ios_base& ( *pf )(std::ios_base&)) const{
          if(_out) _os << pf;
          return *this;
        };
        int printf(const char *fmt, ...) const
#ifdef __GNUC__
          __attribute__((format(printf, 2, 3)))
             /* 1 -> this pointer
              * 2 -> format string ,
              * 3 -> args
              */
#endif
        {
          if(!_out) return 0;
          char buf[MAX_BUFFER_SIZE];
          va_list args;
          va_start (args, fmt);
          int ret = std::vsprintf (buf, fmt, args);
          if (ret>MAX_BUFFER_SIZE) {
            char *long_buf = new char[ret];
            ret = std::vsprintf (long_buf, fmt, args);
            _os << long_buf;
            delete long_buf;
          } else {
            _os << buf;
          }
          va_end (args);
          return ret;
        }
      private:
        bool _out;
        std::ostream &_os;
    };
    DebugStream(int debugLevel=0,
                std::ostream &os = std::cerr)
      :_os(os)
      ,_debugLevel(debugLevel){};
    const DSAgent operator [](int msgLevel) {
      return DSAgent(msgLevel <= _debugLevel, _os);
    }
    void setLevel(int l){_debugLevel = l;}
    int getLevel(){return _debugLevel;}
    bool verbose(int v){return v<=_debugLevel;}
    std::streamsize precision ( std::streamsize prec ) {
      return _os.precision(prec);
    }
    std::streamsize precision ( ) const{return _os.precision();}
    std::streamsize width ( ) const{return _os.width();}
    std::streamsize width ( std::streamsize wide ){return _os.width(wide);}
    std::ios_base::fmtflags setf ( std::ios_base::fmtflags fmtfl ) {
      return _os.setf(fmtfl);
    }
    std::ios_base::fmtflags setf ( std::ios_base::fmtflags fmtfl,
                                   std::ios_base::fmtflags mask ){
      return _os.setf(fmtfl, mask);
    }
  private:
    std::ostream &_os;
    int _debugLevel;
};

#endif

