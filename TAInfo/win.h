#ifndef TA_WIN_H
#define TA_WIN_H

#ifdef WIN32
#define read _read
#define open _open
#define close _close
#define lseek _lseek
#elif __linux__
#define O_BINARY 0
#endif

#endif /* TA_WIN_H */
