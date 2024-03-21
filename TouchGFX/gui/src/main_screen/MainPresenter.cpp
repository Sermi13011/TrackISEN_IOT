#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{

}

void MainPresenter::activate()
{

}

void MainPresenter::deactivate()
{

}
void MainPresenter::screenUpdate(char temp[10],char hum[10])
{
view.screenUpdate(temp,hum);
}

