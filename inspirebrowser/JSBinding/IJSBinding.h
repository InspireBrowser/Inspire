#ifndef IJSBINDING_H
#define IJSBINDING_H

#include <QObject>
#include <QVariant>

class QWebView;
class MainWindow;

/*! @brief  Parent class of all JavaScript binding classes in Inspire
 *          Class that is the parent class for all JavaScript bindings in Inspire, provides
 *          functions for easily getting the different UI elements of the browser and utility function.
 */
class IJSBinding : public QObject
{
    Q_OBJECT

protected:
    /*! @brief Constructor for creating a JSBinding
     *  @param parent The parent object
     */
    explicit IJSBinding(QObject *parent = 0);

    /*! @brief Return the parent WebView widget
     *  @return The WebView component that this is a child of
     */
    QWebView* GetParentWebView() const;

    /*! @brief Returns the MainWindow of the application
     *  @return The MainWindow of the application
     */
    MainWindow* GetMainWindow() const;

    /*! @brief Converts a QVariant object into a JSON formatted string for debug purposed
     *  @param var The QVariant cariable to convert into a JSON string
     *  @param newLineString The string to use as a new line character
     *  @param spacesInTab The number of spaces to have in a tab
     *  @param indent The number of spaces the output is currently indented. Used internally for recursive printing
     *  @return The JSON formatted string representing the QVariant
     */
    QString DumpVariable(QVariant var, QString newLineString, int spacesInTab, int indent = 0) const;

signals:

public slots:

};

#endif // IJSBINDING_H
