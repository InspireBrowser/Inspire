#include "IJSBinding.h"
#include <QWebView>
#include "MainWindow.h"

/*! @brief Constructor for creating a JSBinding
 *  @param parent The parent object
 */
IJSBinding::IJSBinding(QObject *parent) :
        QObject(parent)
{
}

/*! @brief Return the parent WebView widget
 *  @return The WebView component that this is a child of
 */
QWebView* IJSBinding::GetParentWebView() const
{
    return this->GetMainWindow()->webView();
}

/*! @brief Returns the MainWindow of the application
 *  @return The MainWindow of the application
 */
MainWindow* IJSBinding::GetMainWindow() const
{
    MainWindow *window;
    QObject* item = (QObject*)this;
    do
    {
        item = item->parent();
        window = qobject_cast<MainWindow*>(item);
        if(window)
            return window;
    }
    while(item->parent() != 0);

    return 0;
}

/*! @brief Converts a QVariant object into a JSON formatted string for debug purposed
 *  @param var The QVariant cariable to convert into a JSON string
 *  @param newLineString The string to use as a new line character
 *  @param spacesInTab The number of spaces to have in a tab
 *  @param indent The number of spaces the output is currently indented. Used internally for recursive printing
 *  @return The JSON formatted string representing the QVariant
 */
QString IJSBinding::DumpVariable(QVariant var, QString newLineString, int spacesInTab, int indent) const
{
    QString output = "";
    QString tabString = "";
    QString outerTabString = "";

    tabString.fill(' ', (indent+1) * spacesInTab);
    outerTabString.fill(' ', indent * spacesInTab);

    if(var.type() == QVariant::Map)
    {
        QMap<QString, QVariant> map = var.toMap();

        output += "{";
        if(map.count() > 0)
            output += newLineString + tabString;

        QMapIterator<QString, QVariant> i(map);
        while(i.hasNext())
        {
            i.next();
            output += "'" + i.key() + "'" + ":" + DumpVariable(i.value(), newLineString, spacesInTab, indent + 1);

            if(i.hasNext())
                output += "," + newLineString + tabString;
            else
                output += newLineString;
        }
        if(map.count() > 0)
            output += outerTabString + "}";
        else
            output += "}";
    }
    else if(var.type() == QVariant::List)
    {
        output += "[" + newLineString + tabString;
        QListIterator<QVariant> i(var.toList());
        while(i.hasNext()){
            output += DumpVariable(i.next(), newLineString, spacesInTab, indent + 1);

            if(i.hasNext())
                output += "," + newLineString + tabString;
            else
                output += newLineString;
        }
        output += outerTabString + "]";
    }
    else if(var.type() == QVariant::String)
    {
        output += "'" + var.toString() + "'";
    }
    else if(var.type() == QVariant::Double)
    {
        output += var.toString();
    }

    return output;
}
