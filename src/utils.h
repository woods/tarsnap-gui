#ifndef UTILS_H
#define UTILS_H

#include <QRunnable>
#include <QDir>

#define CMD_TARSNAP         "tarsnap"
#define CMD_TARSNAPKEYGEN   "tarsnap-keygen"

#define DEFAULT_SKIP_FILES_OSX     ".DS_Store:.fseventsd:.Spotlight-V100:._.Trashes:.Trashes"
#define DEFAULT_SKIP_FILES_WINDOWS "$RECYCLE.BIN:System Volume Information:Thumbs.db"
#define DEFAULT_SKIP_FILES_LINUX   ".lost+found"

#ifdef Q_OS_OSX
#define DEFAULT_SKIP_FILES DEFAULT_SKIP_FILES_OSX
#elif Q_OS_WIN
#define DEFAULT_SKIP_FILES DEFAULT_SKIP_FILES_WINDOWS
#elif Q_OS_LINUX
#define DEFAULT_SKIP_FILES DEFAULT_SKIP_FILES_LINUX
#else
#define DEFAULT_SKIP_FILES ""
#endif


namespace Utils
{

class GetDirInfoTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    GetDirInfoTask(QDir dir);
    void run();

signals:
    void result(quint64 size, quint64 count);

private:
    QDir _dir;

    quint64 getDirSize(QDir dir);
    quint64 getDirCount(QDir dir);
};

// Convert an int64 size of bytes to a human readable string using either
// SI(1000) or binary(1024) units (default is binary)
QString humanBytes(quint64 bytes, bool si = false);

// if path.isEmpty it will search in $PATH
// if keygenToo it will search for tarsnap-keygen too
// returns the directory where tarsnap resides if found, otherwise empty string
QString findTarsnapClientInPath(QString path, bool keygenToo = false);

// Returns canonical path if verified, otherwise empty string
QString validateTarsnapCache(QString path);

} // namespace Utils

#endif // UTILS_H
