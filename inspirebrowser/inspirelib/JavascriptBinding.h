#ifndef JAVASCRIPTBINDING_H
#define JAVASCRIPTBINDING_H

class MainWindow;

class JavascriptBinding
{
private:
    MainWindow* _mainWindow;

public:
    virtual ~JavascriptBinding() {}

	MainWindow* mainWindow() const { return this->_mainWindow; }
    void setMainWindow(MainWindow* mainWindow) { this->_mainWindow = mainWindow; }
};

#endif // JAVASCRIPTBINDING_H
