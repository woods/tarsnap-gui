#ifndef ELIDEDLABEL_H
#define ELIDEDLABEL_H

#include <QLabel>

/*!
 * \ingroup widgets-general
 * \brief The ElidedLabel widget is a QLabel which automatically elides
 * (`...`) long text, and adds the \ref clicked signal.
 */
class ElidedLabel : public QLabel
{
    Q_OBJECT

    //! Indicates how the text should be elided.
    Q_PROPERTY(Qt::TextElideMode elide READ elide WRITE setElide NOTIFY
                   elideChanged DESIGNABLE true)

public:
    //! Constructor.
    explicit ElidedLabel(QWidget *parent = nullptr);
    ~ElidedLabel();

    //! Returns the elided mode.
    Qt::TextElideMode elide() const;
    //! Sets the elided mode.
    void setElide(const Qt::TextElideMode &elide);

    //! Returns the full text.
    QString text();

    //! Returns the recommended size for the widget based on the full text.
    QSize sizeHint() const;

public slots:
    //! Sets the full text for this ElidedLabel to display (may be elided).
    void setText(const QString &text);
    //! Clears all contents, including the full text.
    void clear();

signals:
    //! Emitted when the elide mode was changed.
    void elideChanged(Qt::TextElideMode elide);
    //! Emitted when this widget was clicked.
    void clicked();

protected:
    //! Recalculates the amount of elided text to display.
    void resizeEvent(QResizeEvent *event);
    //! Used for detecting whether to emit \ref clicked.
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Qt::TextElideMode _elide;
    QString           _fullText;

    // Returns an elided version of the string (if necessary), or the original
    // string (if not).
    QString elideText(const QString &text);
};

#endif // ELIDEDLABEL_H
