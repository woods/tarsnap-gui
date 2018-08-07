#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <QObject>
#include <QWidget>

/*!
 * \ingroup Misc
 * \brief The Scheduling QObject handles scheduling tasks.
 */
class Scheduling : public QObject
{
    Q_OBJECT

public:
    //! Constructor.
    Scheduling(QWidget *parent = nullptr);
    ~Scheduling();

public slots:
    //! Set up launchd or cron jobs
    void enableJobScheduling();
    //! Disable launchd or cron jobs
    void disableJobScheduling();

    //! Check and update (if necessary) the path to the Tarsnap-GUI binary
    void ensureCorrectSchedulingPath();

private:
    QWidget *parent;
};

#endif
