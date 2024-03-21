#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void buttonUpClicked();
    virtual void buttonDownClicked();
    virtual void screenUpdate(char temp[10],char hum[10]);

protected:
  int counter;
};

#endif // MAINVIEW_HPP
