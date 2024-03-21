#include <gui/main_screen/MainView.hpp>
#include <touchgfx/utils.hpp>
#include <stdlib.h>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
MainView::MainView()
{

}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}
void MainView::buttonUpClicked()
{
  touchgfx_printf("buttonUpClicked\n");

  counter++;
  Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
  // Invalidate text area, which will result in it being redrawn in next tick.
  textCounter.invalidate();
}

void MainView::buttonDownClicked()
{
  touchgfx_printf("buttonDownClicked\n");

  counter--;
  Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
  // Invalidate text area, which will result in it being redrawn in next tick.
  textCounter.invalidate();
}
void MainView::screenUpdate(char temp[10],char hum[10])
{
	float TempFloat = atof(temp);
	float HumFloat = atof(hum);
	if(TempFloat>28.0)
	{
		textCounter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}else textCounter.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
	if(HumFloat>65.0)
	{
		textCounter_1.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	}else textCounter_1.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));

	Unicode::snprintfFloat(textCounterBuffer, TEXTCOUNTER_SIZE, "%3.2f", TempFloat);
	textCounter.invalidate();
	Unicode::snprintfFloat(textCounter_1Buffer, TEXTCOUNTER_SIZE, "%3.2f", HumFloat);
	textCounter_1.invalidate();

}
